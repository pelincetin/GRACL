(* Semantic checking for the GRACL compiler *)

open Ast
open Sast
module F = Functions
module StringMap = Map.Make(String)
module StringHash = Hashtbl.Make(struct  (* Consider changing? *)
  type t = string
  let equal x y = x = y
  let hash = Hashtbl.hash
end) 

type symtable = (typ * string) list
let check (program) = 
 
  (* Verify a symbol table has no void types or duplicate names *)
  let check_symbol_table (kind : string) (table : symtable) = 
  List.iter 
  (function (Void, b) -> raise (Failure ("illegal void " ^ kind ^ " " ^ b))
      | _ -> ()) table;
    let rec dups = function
        [] -> ()
      |	((_,n1) :: (_,n2) :: _) when n1 = n2 ->
	  raise (Failure ("duplicate " ^ kind ^ " " ^ n1))
      | _ :: t -> dups t
    in dups (List.sort (fun (_,a) (_,b) -> compare a b) table)
  in

  (* Add function to the function map *)
  let update_function_table ft fd  = 
    let built_in_err = "function " ^ fd.fname ^ " may not be redefined"
    and dup_err = "duplicate function " ^ fd.fname
    and make_err er = raise (Failure er)
    and n = fd.fname (* Name of the function *)
    in match fd with (* No duplicate functions or redefinitions of built-ins *)
         _ when StringMap.mem n F.function_decls -> make_err built_in_err
       | _ when StringMap.mem n ft -> make_err dup_err  
       | _ ->  StringMap.add n fd ft
  in

  (* Add declaration to the global symbol list *)
  let update_global_table gt b = List.rev ((strip_val b):: List.rev gt)
   
  in

  let find_func s ft = 
    try StringMap.find s ft
    with Not_found -> raise (Failure ("unrecognized function " ^ s))
  in

  let checkFunction func ft sl = 
    let _ = check_symbol_table "global" sl; check_symbol_table "formal" func.formals in (* Checks globals and formals when function is entered *)
    (* globals and formals, local / formal / global order of prio *)
    let top_level_symbols = List.fold_left (fun m (ty, name) -> StringMap.add name (ty, name) m) StringMap.empty ( sl @ func.formals ) in 
       
    let locals = StringHash.create 25 in
    
    let count = [|0|] in

    let symbol_table =  top_level_symbols :: [] in 

    (* Raise an exception if the given rvalue type cannot be assigned to
       the given lvalue type *)
    let check_assign lvaluet rvaluet err =
       if lvaluet = rvaluet then lvaluet else raise (Failure err)
    in  

    (* Return a variable from our local symbol table *)
    let rec type_of_identifier s = function
      | ht::st ->
        (try StringMap.find s ht
        with Not_found -> type_of_identifier s st)
      | [] -> raise (Failure ("undeclared identifier " ^ s))
    in

    (* Return a semantically-checked expression, i.e., with a type *)
    let rec expr st = function
        Literal  l -> (Int, SLiteral l)
      | Fliteral l -> (Double, SFliteral l)
      | Sliteral l -> (String, SSliteral l)
      | BoolLit l  -> (Bool, SBoolLit l)
      | Noexpr     -> (Void, SNoexpr)
      | Id s       -> let (typ, name) = type_of_identifier s st in (typ , SId name) (* TODO: TEST ERROR HANDLING FOR ACCESS/INSERT *)
      | Access(table, node) -> let (tabletyp, tablename) = type_of_identifier table st and (nodetyp, nodename) = type_of_identifier node st in
        (match nodetyp with 
        Node -> 
          (match tabletyp with
          | Inttable -> (Int, SCall("_getInt", [(Inttable, SId tablename); (Node, SId nodename)]))
          | Doubletable -> (Double, SCall("_getDouble", [(Doubletable, SId tablename); (Node, SId nodename)]))
          | _ -> raise(Failure ("Cannot treat " ^ string_of_typ tabletyp ^ " as an IntTable/DoubleTable"))
        | _ -> raise(Failure ("Cannot use " ^ string_of_typ nodetyp ^ " as keys in an IntTable/DoubleTable"))))
      | Insert(table, node, ex) -> let (tabletyp, tablename) = type_of_identifier table st and (nodetyp, nodename) = type_of_identifier node st in
        (match nodetyp with 
        Node -> (let (extyp, ex') = expr st ex in 
          let err = "illegal insertion, cannot put " ^ string_of_typ extyp ^ " " ^ string_of_expr ex ^ " in " ^ string_of_typ tabletyp  in
          match tabletyp with
          | Inttable -> (Void, SCall("_insertInt", [(Inttable, SId tablename); (Node, SId nodename); (check_assign Int extyp err, ex')]))
          | Doubletable -> (Void, SCall("_insertDouble", [(Doubletable, SId tablename); (Node, SId nodename); (check_assign Double extyp err, ex')]))
          | _ -> raise(Failure ("Cannot treat " ^ string_of_typ tabletyp ^ " as an IntTable/DoubleTable")))
        | _ -> raise(Failure ("Cannot use " ^ string_of_typ nodetyp ^ " as keys in an IntTable/DoubleTable")))
      | Assign(var, e) as ex -> 
          let (lt, name) = type_of_identifier var st
          and (rt, e') = expr st e in
          let err = "illegal assignment " ^ string_of_typ lt ^ " = " ^ 
            string_of_typ rt ^ " in " ^ string_of_expr ex
          in (check_assign lt rt err, SAssign(name, (rt, e')))
      | Unop(op, e) as ex -> 
          let (t, e') = expr st e in
          let ty = match op with
            Neg when t = Int || t = Double -> t
          | Not when t = Bool -> Bool
          | _ -> raise (Failure ("illegal unary operator " ^ 
                                 string_of_uop op ^ string_of_typ t ^
                                 " in " ^ string_of_expr ex))
          in (ty, SUnop(op, (t, e')))
      | Binop(e1, op, e2) as e -> 
          let (t1, e1') = expr st e1 
          and (t2, e2') = expr st e2 in
          (* All binary operators require operands of the same type *)
          let same = t1 = t2 in
          (* Determine expression type based on operator and operand types *)
          let ty = match op with
            Add | Sub | Mult | Div | Mod when same && t1 = Int   -> Int
          | Add | Sub | Mult | Div when same && t1 = Double -> Double
          | Equal | Neq          when same && (t1 = Int || t1 = Double || t1 = Bool) -> Bool
          | Less | Leq | Great | Geq
                     when same && (t1 = Int || t1 = Double) -> Bool
          | And | Or when same && t1 = Bool -> Bool
          | _ -> raise (
	      Failure ("illegal binary operator " ^
                       string_of_typ t1 ^ " " ^ string_of_op op ^ " " ^
                       string_of_typ t2 ^ " in " ^ string_of_expr e))
          in (ty, SBinop((t1, e1'), op, (t2, e2')))
      | Call(fname, args) as call -> 
          let fd = find_func fname ft in
          let param_length = List.length fd.formals in
          if List.length args != param_length then
            raise (Failure ("expecting " ^ string_of_int param_length ^ 
                            " arguments in " ^ string_of_expr call))
          else let check_call (ft, _) e = 
            let (et, e') = expr st e in 
            let err = "illegal argument found " ^ string_of_typ et ^
              " expected " ^ string_of_typ ft ^ " in " ^ string_of_expr e
            in (check_assign ft et err, e')
          in 
          let args' = List.map2 check_call fd.formals args
          in (fd.typ, SCall(fname, args'))
     (* TODO: | Access(table, key)
      | Insert(table, key, ex)*)
    in

    let check_bool_expr st e = 
      let (t', e') = expr st e
      and err = "expected Boolean expression in " ^ string_of_expr e
      in if t' != Bool then raise (Failure err) else (t', e') 
    in

    (* Return a semantically-checked statement i.e. containing sexprs *)
    let rec check_stmt (st : (Ast.typ*string) StringMap.t list)  = function
        Expr e -> SExpr (expr st e)
      | If(p, b1, b2) -> SIf(check_bool_expr st p, check_stmt st b1, check_stmt st b2)
      | While(p, s) -> SWhile(check_bool_expr st p, check_stmt st s)
      | Return e -> let (t, e') = expr st e in     (* TODO: DO WE REQUIRE RETURN STATEMENTS? SHOULD WE CHECK? *)
        if t = func.typ then SReturn (t, e') 
        else raise (
	  Failure ("return gives " ^ string_of_typ t ^ " expected " ^
		   string_of_typ func.typ ^ " in " ^ string_of_expr e))
	    
	    (* A block is correct if each statement is correct and nothing
	       follows any Return statement.  Nested blocks are flattened. *)   
      | Block sl -> let st = StringMap.empty::st in
          let rec check_stmt_list st = function
              [Return _ as s] -> [check_stmt st s]
            | Return _ :: _   -> raise (Failure "nothing may follow a return")
            | Block sl :: ss  -> check_stmt_list (StringMap.empty::st) (sl @ ss) (* Flatten blocks *)
            | LoclBind(b) as lb :: ss -> let add_local typ name = if StringMap.mem name (List.hd st) then raise (Failure ("Cannot redeclare " ^ name)) 
              else StringMap.add name (typ, "var" ^ string_of_int (count.(0)) ^ "_" ^ name) (List.hd st) and (t,n) = strip_val b and _ = count.(0) <- 1 + count.(0) in 
              let updated_table = (add_local t n)::(List.tl st) in
              let stm = check_stmt updated_table lb in stm :: check_stmt_list updated_table ss
            | BlockEnd :: ss -> SBlockEnd::check_stmt_list (List.tl st) ss
            | s :: ss         -> let stm = check_stmt st s in stm :: check_stmt_list st ss (* stm is VERY important here *)
            | []              -> []  
          in SBlock(check_stmt_list st sl)
      
      | LoclBind(b) -> 
      begin match b with
        | Dec(t,n) -> if t = Void then raise (Failure ("illegal void local " ^ n)) else 
          let (_, newname) = type_of_identifier n st in StringHash.replace locals n (SDec(t,newname)); SExpr(Void, SNoexpr)
        | Decinit(t,n,e) as di -> 
        if t = Void then raise (Failure ("illegal void local " ^ n)) else 
        let (rt, ex) = expr st e in
          let err = "illegal assignment " ^ string_of_typ t ^ " = " ^ 
            string_of_typ rt ^ " in " ^ string_of_vdecl di
          in let _ = check_assign t rt err and (_, newname) = type_of_identifier n st 
            in StringHash.replace locals newname (SDecinit(t, newname, (rt, ex))); SExpr(t, SAssign(newname, (rt, ex))) end
      
      | BlockEnd -> (* Should have been handled by Block *)
        raise (Failure ("internal error: block end mishandled?"))

      (* TODO:
      | NodeFor 
      | EdgeFor
        *)

    in (* body of check_function *)
    { styp = func.typ;
      sfname = func.fname;
      sformals = func.formals; 
      slocals  = begin let locallist = (StringHash.fold (fun _ b lt -> b::lt) locals []) in 
      let _ = check_symbol_table "local" (List.map strip_sval locallist) 
        in locallist end;
      sbody = match check_stmt symbol_table (Block func.body) with
	SBlock(sl) -> sl
      | _ -> raise (Failure ("internal error: block didn't become a block?"))
    }
in

let checkGlobal =  (* TODO: ADD TO LRM HOW GLOBALS CAN BE INITIALIZED/ARE DEFAULT *)
    let rec constexpr = function
        Literal  l -> (Int, SLiteral l)
      | Fliteral l -> (Double, SFliteral l)
      | Sliteral l -> (String, SSliteral l)
      | BoolLit l  -> (Bool, SBoolLit l)
      | Unop(op, e) as ex -> 
          let (t, e') = constexpr e in
          let ty = match op with
            Neg when t = Int || t = Double -> t
          | Not when t = Bool -> Bool
          | _ -> raise (Failure ("illegal unary operator " ^ 
                                 string_of_uop op ^ string_of_typ t ^
                                 " in " ^ string_of_expr ex))
          in (ty, SUnop(op, (t, e')))
      | Binop(e1, op, e2) as e -> 
          let (t1, e1') = constexpr e1 
          and (t2, e2') = constexpr e2 in
          (* All binary operators require operands of the same type *)
          let same = t1 = t2 in
          (* Determine expression type based on operator and operand types *)
          let ty = match op with
            Add | Sub | Mult | Div | Mod when same && t1 = Int   -> Int
          | Add | Sub | Mult | Div when same && t1 = Double -> Double
          | Equal | Neq          when same && (t1 = Int || t1 = Double || t1 = Bool) -> Bool
          | Less | Leq | Great | Geq
                     when same && (t1 = Int || t1 = Double) -> Bool
          | And | Or when same && t1 = Bool -> Bool
          | _ -> raise (
	      Failure ("illegal binary operator " ^
                       string_of_typ t1 ^ " " ^ string_of_op op ^ " " ^
                       string_of_typ t2 ^ " in " ^ string_of_expr e))
          in (ty, SBinop((t1, e1'), op, (t2, e2')))
      | _ as ex -> raise (Failure ("initializer element " ^ string_of_expr ex ^ " is not a compile time constant"))
    in function
  | Decinit(t, n, e) as di -> 
        let (rt, ex) = constexpr e 
        and check_assign lvaluet rvaluet err =
       if lvaluet = rvaluet then lvaluet else raise (Failure err)
        in 
          let err = "illegal assignment " ^ string_of_typ t ^ " = " ^ 
            string_of_typ rt ^ " in " ^ string_of_vdecl di
            in let _ = check_assign t rt err
          in SDecinit(t, n, (rt, ex))
  | Dec(t,n) -> SDec(t,n)  
  in

  let rec semant_check progparts ft (sl : symtable) (globs, funcs) = 
    match progparts with
    | [] -> ignore(find_func "main" ft); let _ = check_symbol_table "global" sl in (globs, funcs)
    | FuncDecl(f)::ps -> let new_funcs = (update_function_table ft f) in semant_check ps new_funcs sl (globs, List.rev (checkFunction f new_funcs sl :: List.rev funcs))
    | GlobBind(b)::ps -> semant_check ps ft (update_global_table sl b) (List.rev (checkGlobal b :: List.rev globs), funcs)

in semant_check program F.function_decls [] ([], [])