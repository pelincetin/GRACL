(* Code generation: translate takes a semantically checked AST and
produces LLVM IR

LLVM tutorial: Make sure to read the OCaml version of the tutorial

http://llvm.org/docs/tutorial/index.html

Detailed documentation on the OCaml LLVM library:

http://llvm.moe/
http://llvm.moe/ocaml/

*)

module L = Llvm
module A = Ast
module F = Functions
open Sast 

module StringMap = Map.Make(String)


(* translate : Sast.program -> Llvm.module *)
let translate (globals, functions) =
  let context    = L.global_context () in
  
  (* Create the LLVM compilation module into which
     we will generate code *)
  let the_module = L.create_module context "GRACL" in (* TODO: Dispose of module? *)

  (* Get types from the context *)
  let i32_t      = L.i32_type    context
  and i8_t       = L.i8_type     context
  and i1_t       = L.i1_type     context
  and double_t   = L.double_type context
  and void_t     = L.void_type   context
  and i64_t      = L.i64_type    context in
  let mutex_t    = L.struct_type context [| i64_t; L.array_type i8_t 56 |] in
  let edgelistitem_t = L.named_struct_type context "EdgeListItem" in
  let nodelistitem_t = L.named_struct_type context "NodeListItem" in
  let node_t     = L.named_struct_type context "Node" in
  let node_pointer = L.pointer_type node_t in
  let edge_t     = L.struct_type context [|mutex_t; double_t; node_pointer; node_pointer|] in
  let edge_pointer = L.pointer_type edge_t in
  let edgelistitem_pointer = L.pointer_type edgelistitem_t in
  let nodelistitem_pointer = L.pointer_type nodelistitem_t in
  let edgelist_t = L.struct_type context [| edgelistitem_pointer; edgelistitem_pointer|] in
  let nodelist_t = L.struct_type context [| nodelistitem_pointer; nodelistitem_pointer|] in
  let edgelist_pointer = L.pointer_type edgelist_t in 
  let nodelist_pointer = L.pointer_type nodelist_t in 
  let _ = L.struct_set_body edgelistitem_t [|edge_pointer; edgelistitem_pointer; edgelistitem_pointer|] false in
  let _ = L.struct_set_body nodelistitem_t [|node_pointer; nodelistitem_pointer; nodelistitem_pointer|] false in
  let _ = L.struct_set_body node_t [|mutex_t; i32_t; L.pointer_type i8_t; i8_t; edgelist_pointer; node_pointer; i32_t; i32_t |] false in
  let string_t   = L.pointer_type i8_t in
  let dataitem_t = L.struct_type context [|node_pointer; edgelist_pointer|] in
  let dataitem_pointer = L.pointer_type dataitem_t in
  let graph_t = L.struct_type context [|dataitem_pointer; nodelist_pointer; i32_t; i32_t; i32_t|] in
  let graph_pointer = L.pointer_type graph_t in
  let doubletablellitem_t = L.struct_type context [|node_pointer; double_t|] in
  let doubletablellitem_pointer = L.pointer_type doubletablellitem_t in
  let doubletableitem_t = L.named_struct_type context "DoubleTableItem" in
  let doubletableitem_pointer = L.pointer_type doubletableitem_t in
  let doubletable_t = L.struct_type context [|mutex_t; doubletableitem_pointer; nodelist_pointer; i32_t; i32_t; i32_t|] in
  let doubletable_pointer = L.pointer_type doubletable_t in
  let inttablellitem_t = L.struct_type context [|node_pointer; i32_t|] in
  let inttablellitem_pointer = L.pointer_type inttablellitem_t in
  let inttableitem_t = L.named_struct_type context "IntTableItem" in
  let inttableitem_pointer = L.pointer_type inttableitem_t in
  let inttable_t = L.struct_type context [|mutex_t; inttableitem_pointer; nodelist_pointer; i32_t; i32_t|] in
  let inttable_pointer = L.pointer_type inttable_t in
  let _ = L.struct_set_body doubletableitem_t [|doubletableitem_pointer; doubletablellitem_pointer|] false in
  let _ = L.struct_set_body inttableitem_t [|inttableitem_pointer; inttablellitem_pointer|] false in

  (* Return the LLVM type for a GRACL type *)
  let ltype_of_typ = function
      A.Int   -> i32_t
    | A.Bool  -> i1_t
    | A.Double -> double_t
    | A.Void  -> void_t
    | A.String -> string_t
    | A.Node -> node_pointer
    | A.Edge -> edge_pointer
    | A.Edgelist -> edgelist_pointer
    | A.Nodelist -> nodelist_pointer
    | A.Graph -> graph_pointer
    | A.Doubletable -> doubletable_pointer
    | A.Inttable -> inttable_pointer
  in

  let int_format_str = let str = L.define_global "fmt" (L.const_stringz context "%d\n") the_module in L.const_in_bounds_gep str [|L.const_int i32_t 0; L.const_int i32_t 0|]  
     and float_format_str = let str = L.define_global "cast" (L.const_stringz context "%f") the_module in L.const_in_bounds_gep str [|L.const_int i32_t 0; L.const_int i32_t 0|]  
     and string_format_str = let str = L.define_global "fmt" (L.const_stringz context "%s\n") the_module in L.const_in_bounds_gep str [|L.const_int i32_t 0; L.const_int i32_t 0|] in

  (* Create a map of global variables after creating each, initialize as needed *)                   (* TODO: Globals have default values? *)
  let global_vars : L.llvalue StringMap.t =
    let global_var m  = function
    | SDec(t, n) ->
      let defaultinit = match t with                                           (* TODO: ERROR CASE FOR NO MATCH *)
          A.Double -> L.const_float (ltype_of_typ t) 0.0
        | A.String -> let str = L.define_global "str" (L.const_stringz context "") the_module in L.const_in_bounds_gep str [|L.const_int i32_t 0; L.const_int i32_t 0|]                        (* TODO: HANDLE STRINGS *)
        | A.Int | A.Bool -> L.const_int (ltype_of_typ t) 0
        | _ -> L.const_pointer_null (ltype_of_typ t)
      in StringMap.add n (L.define_global n defaultinit the_module) m 
    | SDecinit(_, n, e) ->
      let rec constexpr ((_, e) : sexpr) = match e with
	    SLiteral i  -> L.const_int i32_t i
      | SSliteral s -> let str = L.define_global "str" (L.const_stringz context s) the_module in L.const_in_bounds_gep str [|L.const_int i32_t 0; L.const_int i32_t 0|]
      | SBoolLit b  -> L.const_int i1_t (if b then 1 else 0)     
      | SFliteral l -> if l = "infinity" then L.const_float double_t infinity else L.const_float_of_string double_t l
      | SBinop ((A.Double,_ ) as e1, op, e2) ->
	  let e1' = constexpr e1
	  and e2' = constexpr e2 in
	  (match op with 
	    A.Add     -> L.const_fadd
	  | A.Sub     -> L.const_fsub
	  | A.Mult    -> L.const_fmul                                           
	  | A.Div     -> L.const_fdiv 
	  | A.Equal   -> L.const_fcmp L.Fcmp.Oeq
    | A.Neq     -> L.const_fcmp L.Fcmp.One
	  | A.Less    -> L.const_fcmp L.Fcmp.Olt
	  | A.Great   -> L.const_fcmp L.Fcmp.Ogt
	  | A.Leq     -> L.const_fcmp L.Fcmp.Ole
    | A.Geq     -> L.const_fcmp L.Fcmp.Oge
	  | _ ->
	      raise (Failure "internal error: semant should have rejected illegal float operation")
	  ) e1' e2' 
      | SBinop (e1, op, e2) ->
	  let e1' = constexpr e1
	  and e2' = constexpr e2 in
	  (match op with
	    A.Add     -> L.const_add                                    (* TODO: MENTION OVERFLOW BEHAVIOR *)
	  | A.Sub     -> L.const_sub                                   (*TODO:ADD MODULO*)
	  | A.Mult    -> L.const_mul
    | A.Div     -> L.const_sdiv
    | A.Mod     -> L.const_srem
	  | A.And     -> L.const_and
	  | A.Or      -> L.const_or
	  | A.Equal   -> L.const_icmp L.Icmp.Eq
    | A.Neq     -> L.const_icmp L.Icmp.Ne
	  | A.Less    -> L.const_icmp L.Icmp.Slt
	  | A.Great   -> L.const_icmp L.Icmp.Sgt
	  | A.Leq     -> L.const_icmp L.Icmp.Sle
    | A.Geq     -> L.const_icmp L.Icmp.Sge
	  ) e1' e2' 
      | SUnop(op, ((t, _) as e)) ->
          let e' = constexpr e in
	  (match op with
	    A.Neg when t = A.Double -> L.const_fneg 
	  | A.Neg                  -> L.const_neg
    | A.Not                  -> L.const_not) e' 
    | _ -> raise (Failure "internal error: semant should have caught global nonconstant initialization")                     
      in StringMap.add n (L.define_global n (constexpr e) the_module) m 
    in
    List.fold_left global_var StringMap.empty globals in

  (* Standard C/LLVM Functions *)
  let printf_t : L.lltype = 
      L.var_arg_function_type i32_t [| string_t |] in
  let printf_func : L.llvalue = 
      L.declare_function "printf" printf_t the_module in

  let sprintf_t : L.lltype = 
      L.var_arg_function_type i32_t [| string_t; i32_t; (L.i64_type context); string_t |] in
  let sprintf_func : L.llvalue = 
      L.declare_function "__sprintf_chk" sprintf_t the_module in

  let strlen_t : L.lltype = 
      L.function_type i64_t [| string_t |] in
  let strlen_func : L.llvalue = 
      L.declare_function "strlen" strlen_t the_module in

  let strcmp_t : L.lltype = 
      L.function_type i32_t [| string_t; string_t |] in
  let strcmp_func : L.llvalue = 
      L.declare_function "strcmp" strcmp_t the_module in


  (* Define each function (arguments and return type) so we can 
     call it even before we've created its body *)
  let function_decls : (L.llvalue * sfunc_decl) StringMap.t =
    let function_decl m fdecl =
      let name = fdecl.sfname
      and formal_types = 
	Array.of_list (List.map (fun (t,_) -> ltype_of_typ t) fdecl.sformals)
      in let ftype = L.function_type (ltype_of_typ fdecl.styp) formal_types in
      StringMap.add name (L.define_function name ftype the_module, fdecl) m in
    List.fold_left function_decl StringMap.empty functions in
  
  (* Fill in the body of the given function *)
  let build_function_body fdecl =
    let (the_function, _) = StringMap.find fdecl.sfname function_decls in
    let builder = L.builder_at_end context (L.entry_block the_function) in

    

    (* Construct the function's "locals": formal arguments and locally
       declared variables.  Allocate each on the stack, initialize their
       value, if appropriate, and remember their values in the "locals" map *)
    let local_vars =
      let add_formal m (t, n) p = 
        L.set_value_name n p;
	  let local = L.build_alloca (ltype_of_typ t) n builder in
        ignore (L.build_store p local builder);
	      StringMap.add n local m 

      (* Allocate space for any locally declared variables and add the
       * resulting registers to our map *)
      and add_local m (t, n) =
	let local_var = L.build_alloca (ltype_of_typ t) n builder
	in StringMap.add n local_var m 
      in

      let formals = List.fold_left2 add_formal StringMap.empty fdecl.sformals
          (Array.to_list (L.params the_function)) in
      List.fold_left add_local formals ( List.map strip_sval fdecl.slocals )                           
    in

    (* Return the value for a variable or formal argument.
       Check local names first, then global names *)
    let lookup n = try StringMap.find n local_vars
                   with Not_found -> StringMap.find n global_vars
    in

    (* Construct code for an expression; return its value *)
    let rec expr builder ((_, e) : sexpr) = match e with
	      SLiteral i  -> L.const_int i32_t i
      | SSliteral s -> L.build_global_stringptr s "str" builder
      | SBoolLit b  -> L.const_int i1_t (if b then 1 else 0)     
      | SFliteral l -> if l = "infinity" then L.const_float double_t infinity else L.const_float_of_string double_t l
      | SNoexpr     -> L.const_int i32_t 0
      | SId s       -> L.build_load (lookup s) s builder 
      | SAssign (s, e) -> let e' = expr builder e in
                          ignore(L.build_store e' (lookup s) builder); e' 
      | SBinop ((A.Double,_ ) as e1, op, e2) ->
	  let e1' = expr builder e1
	  and e2' = expr builder e2 in
	  (match op with 
	    A.Add     -> L.build_fadd
	  | A.Sub     -> L.build_fsub
	  | A.Mult    -> L.build_fmul
	  | A.Div     -> L.build_fdiv 
	  | A.Equal   -> L.build_fcmp L.Fcmp.Oeq
    | A.Neq     -> L.build_fcmp L.Fcmp.One
	  | A.Less    -> L.build_fcmp L.Fcmp.Olt
	  | A.Great   -> L.build_fcmp L.Fcmp.Ogt    
	  | A.Leq     -> L.build_fcmp L.Fcmp.Ole
    | A.Geq     -> L.build_fcmp L.Fcmp.Oge
	  | _ ->
	      raise (Failure "internal error: semant should have rejected illegal float operation")
	  ) e1' e2' "tmp" builder
      | SBinop (e1, op, e2) ->
	  let e1' = expr builder e1
	  and e2' = expr builder e2 in
	  (match op with
	    A.Add     -> L.build_add
	  | A.Sub     -> L.build_sub
	  | A.Mult    -> L.build_mul
    | A.Div     -> L.build_sdiv
    | A.Mod     -> L.build_srem
	  | A.And     -> L.build_and
	  | A.Or      -> L.build_or
	  | A.Equal   -> L.build_icmp L.Icmp.Eq
    | A.Neq     -> L.build_icmp L.Icmp.Ne
	  | A.Less    -> L.build_icmp L.Icmp.Slt
	  | A.Great   -> L.build_icmp L.Icmp.Sgt
	  | A.Leq     -> L.build_icmp L.Icmp.Sle
    | A.Geq     -> L.build_icmp L.Icmp.Sge
	  ) e1' e2' "tmp" builder
      | SUnop(op, ((t, _) as e)) ->
          let e' = expr builder e in
	  (match op with
	    A.Neg when t = A.Double -> L.build_fneg 
	  | A.Neg                   -> L.build_neg
    | A.Not                   -> L.build_not) e' "tmp" builder

      
      (* Special built in functions *)
      | SCall("doubleToString", [e]) -> 
        let arr = (L.build_alloca (L.array_type i8_t 1000) "floatarr" builder) in
        let arrptr =  L.build_in_bounds_gep arr [|L.const_int i32_t 0; L.const_int i32_t 0|] "arrptr" builder in
        ignore(L.build_call sprintf_func [| arrptr; (L.const_int i32_t 0); (L.const_int (L.i64_type context) 1000); float_format_str; (expr builder e) |] 
          "doubleToString" builder); arrptr
      | SCall("intToDouble", [e]) -> L.build_sitofp (expr builder e) double_t "intToDouble" builder
      | SCall("print", [e]) ->  
        L.build_call printf_func [| string_format_str; (expr builder e) |] "print" builder
      | SCall("printi", [e]) ->  
        L.build_call printf_func [| int_format_str; (expr builder e) |] "printi" builder
      | SCall("stringLength", [e]) ->
        let len = L.build_call strlen_func [| (expr builder e) |] "stringLength" builder in
        L.build_trunc len i32_t "length" builder
      | SCall("stringEquals", [s1 ; s2]) -> 
        let compval = L.build_call strcmp_func [| (expr builder s1); (expr builder s2) |] "stringEquals" builder in
        L.build_icmp L.Icmp.Eq (L.const_int i32_t 0) compval "equals" builder 
      (* General built in function call *)
      | SCall(fname, args) when StringMap.mem fname F.function_decls -> 
        let fdecl = StringMap.find fname F.function_decls in 
        let rettype = function A.Void -> i32_t | _ as typ -> ltype_of_typ typ in  (* Deals with void function calls *)
        let func_t : L.lltype = L.function_type (rettype fdecl.A.typ) (Array.of_list (List.map ltype_of_typ (List.map fst fdecl.A.formals))) in
        let func_value : L.llvalue = L.declare_function fname func_t the_module 
        and llargs = List.rev (List.map (expr builder) (List.rev args)) in
        L.build_call func_value (Array.of_list llargs) (fname ^ "_result") builder
      (* User defined functions *)
      | SCall (f, args) ->
         let (fdef, fdecl) = StringMap.find f function_decls in
	 let llargs = List.rev (List.map (expr builder) (List.rev args)) in
	 let result = (match fdecl.styp with 
                        A.Void -> ""
                      | _ -> f ^ "_result") in
         L.build_call fdef (Array.of_list llargs) result builder
    in

    (* LLVM insists each basic block end with exactly one "terminator" 
       instruction that transfers control.  This function runs "instr builder"
       if the current block does not already have a terminator.  Used,
       e.g., to handle the "fall off the end of the function" case. *)
    let add_terminal builder instr =
      match L.block_terminator (L.insertion_block builder) with
	Some _ -> ()
      | None -> ignore (instr builder) in
	
    (* Build the code for the given statement; return the builder for
       the statement's successor (i.e., the next instruction will be built
       after the one generated by this call) *)

    let rec stmt builder = function
	      SBlock sl -> List.fold_left stmt builder sl
      | SBlockEnd -> builder
      | SExpr e -> ignore(expr builder e); builder 
      | SReturn e -> ignore(match fdecl.styp with
                              (* Special "return nothing" instr *)
                              A.Void -> L.build_ret_void builder 
                              (* Build return statement *)
                            | _ -> L.build_ret (expr builder e) builder );
                     builder
      | SIf (predicate, then_stmt, else_stmt) ->
         let bool_val = expr builder predicate in
	 let merge_bb = L.append_block context "merge" the_function in
         let build_br_merge = L.build_br merge_bb in (* partial function *)

	 let then_bb = L.append_block context "then" the_function in
	 add_terminal (stmt (L.builder_at_end context then_bb) then_stmt)
	   build_br_merge;

	 let else_bb = L.append_block context "else" the_function in
	 add_terminal (stmt (L.builder_at_end context else_bb) else_stmt)
	   build_br_merge;

	 ignore(L.build_cond_br bool_val then_bb else_bb builder);
	 L.builder_at_end context merge_bb

      | SWhile (predicate, body) ->
	  let pred_bb = L.append_block context "while" the_function in
	  ignore(L.build_br pred_bb builder);

	  let body_bb = L.append_block context "while_body" the_function in
	  add_terminal (stmt (L.builder_at_end context body_bb) body)
	    (L.build_br pred_bb);

	  let pred_builder = L.builder_at_end context pred_bb in
	  let bool_val = expr pred_builder predicate in

	  let merge_bb = L.append_block context "merge" the_function in
	  ignore(L.build_cond_br bool_val body_bb merge_bb pred_builder);
	  L.builder_at_end context merge_bb

    in

    (* Build the code for each statement in the function *)
    let builder = stmt builder (SBlock fdecl.sbody) in

    (* Add a return if the last block falls off the end *)
    add_terminal builder (match fdecl.styp with
        A.Void -> L.build_ret_void
      | A.Double -> L.build_ret (L.const_float double_t 0.0)
      | A.Int | A.Bool -> L.build_ret (L.const_int i32_t 0)
      | A.String -> L.build_ret (L.build_global_stringptr "" "str" builder)
      | _ as t -> L.build_ret (L.const_pointer_null (ltype_of_typ t)))
  in

  List.iter build_function_body functions; 
  the_module
