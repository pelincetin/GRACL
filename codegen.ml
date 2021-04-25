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
  and i16_t      = L.i16_type    context 
  and i8_t       = L.i8_type     context
  and i1_t       = L.i1_type     context
  and double_t   = L.double_type context
  and void_t     = L.void_type   context
  and i64_t      = L.i64_type    context in
  let pthread_attr = L.struct_type context [| i64_t; (L.array_type i8_t 48) |] in 
  let pthread_list = L.named_struct_type context "pthread_list" in
  let pthread_list_pointer = L.pointer_type pthread_list in
  let _          = L.struct_set_body pthread_list [|pthread_list_pointer; pthread_list_pointer|] false in 
  let mutex_s    = L.struct_type context [|i32_t; i32_t; i32_t; i32_t; i32_t; i16_t; i16_t; pthread_list|] in
  let mutex_t    = L.named_struct_type context "Mutex" in
  let _ = L.struct_set_body mutex_t [| mutex_s |] false in
  let edgelistitem_t = L.named_struct_type context "EdgeListItem" in
  let nodelistitem_t = L.named_struct_type context "NodeListItem" in
  let node_t     = L.named_struct_type context "Node" in
  let node_pointer = L.pointer_type node_t in
  let edge_t     = L.struct_type context [|mutex_t; double_t; node_pointer; node_pointer|] in
  let edge_pointer = L.pointer_type edge_t in
  let edgelistitem_pointer = L.pointer_type edgelistitem_t in
  let nodelistitem_pointer = L.pointer_type nodelistitem_t in
  let edgelist_t = L.struct_type context [| mutex_t; edgelistitem_pointer; edgelistitem_pointer|] in
  let nodelist_t = L.struct_type context [| mutex_t; nodelistitem_pointer; nodelistitem_pointer|] in
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

  let size_of_typ = function
      A.Int   -> 4
    | A.Bool  -> 1
    | A.Double -> 8
    | A.Void  -> 0
    | _ -> 8
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

  let synch_start_t : L.lltype = 
      L.function_type i32_t [| string_t |] in
  let synch_start_func : L.llvalue = 
      L.declare_function "_synch_start" synch_start_t the_module in 

  let synch_end_t : L.lltype = 
      L.function_type i32_t [| string_t |] in
  let synch_end_func : L.llvalue = 
      L.declare_function "_synch_end" synch_end_t the_module in 


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
      | SCall("_synch_start", [e]) -> 
        let void = L.build_bitcast (expr builder e) string_t "void_ptr" builder in
        L.build_call synch_start_func [| void |] "synch_start" builder
      | SCall("_synch_end", [e]) -> 
        let void = L.build_bitcast (expr builder e) string_t "void_ptr" builder in
        L.build_call synch_end_func [| void |] "synch_end" builder      
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
      | SFor(t, n, e, body) -> 
        let list_alloca = L.build_alloca (if t = A.Node then nodelist_pointer else edgelist_pointer) "list" builder in
        let item_alloca = L.build_alloca (if t = A.Node then nodelistitem_pointer else edgelistitem_pointer) "item" builder and
        _ = L.build_store (expr builder e) list_alloca builder in
        let list_load = L.build_load list_alloca "list" builder in
        let list_gep = L.build_in_bounds_gep list_load [|L.const_int i32_t 0; L.const_int i32_t 1|] "list_gep" builder in
        let list_pointer = L.build_load list_gep "item_ptr" builder in
        let _ = L.build_store list_pointer item_alloca builder in
        


        let pred_bb = L.append_block context "for" the_function in 
        ignore(L.build_br pred_bb builder);

        let body_bb = L.append_block context "for_body" the_function in
        let endfor_bb = L.append_block context "end_for" the_function in
        let body_builder = L.builder_at_end context body_bb in 
        let item_load = L.build_load item_alloca "item" body_builder in
        let item_gep = L.build_in_bounds_gep item_load [|L.const_int i32_t 0; L.const_int i32_t 0|] "item_gep" body_builder in
        let _ = L.build_store (L.build_load item_gep "element" body_builder) (lookup n) body_builder in
        add_terminal (stmt (body_builder) body) (L.build_br endfor_bb);
        
        
        let end_builder = L.builder_at_end context endfor_bb in 
        let item_load = L.build_load item_alloca "item" end_builder in
        let item_gep = L.build_in_bounds_gep item_load [|L.const_int i32_t 0; L.const_int i32_t 1|] "item_gep" end_builder in
        let next_item_load = L.build_load item_gep "next" end_builder in
        let _ = L.build_store next_item_load item_alloca end_builder in
        add_terminal end_builder (L.build_br pred_bb);

        let pred_builder = L.builder_at_end context pred_bb in
        let bool_val = let item_load = L.build_load item_alloca "item" pred_builder in 
          L.build_is_not_null item_load "bool" pred_builder in                

        let merge_bb = L.append_block context "formerge" the_function in
        ignore(L.build_cond_br bool_val body_bb merge_bb pred_builder);
        L.builder_at_end context merge_bb 

      | SIf (predicate, then_stmt, else_stmt) ->
         let bool_val = expr builder predicate in
	 let merge_bb = L.append_block context "ifmerge" the_function in
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

      | SHatch(nl, func, args, stmts) -> let argtypes = A.Node::(List.map (fun (t, _) -> t) args) in
      (* Wrapper Struct *)
      let hatch_t = L.named_struct_type context "hatch_args" in
      let _       = L.struct_set_body hatch_t (Array.of_list (List.map ltype_of_typ argtypes)) false in 

      (* Unwrapper Function *)
      let unwrapper_func_t = L.function_type string_t [| string_t |] in
      let unwrapper_func = L.define_function ("hatch_unwrapper_" ^ func) unwrapper_func_t the_module in
      let unwrap_builder = L.builder_at_end context (L.entry_block unwrapper_func) in
      let (fdef, _) = StringMap.find func function_decls in let hatching_func_t = L.type_of fdef in

      let void_alloca = L.build_alloca string_t "void_ptr" unwrap_builder in
      let struct_alloca = L.build_alloca (L.pointer_type hatch_t) "wrapper" unwrap_builder in
      let _ = L.build_store (L.param unwrapper_func 0) void_alloca unwrap_builder in
      
      let load_ptr = L.build_load void_alloca "void_ptr" unwrap_builder in
      let ptr_cast = L.build_bitcast load_ptr (L.pointer_type hatch_t) "cast_ptr" unwrap_builder in
      let _ = L.build_store ptr_cast struct_alloca unwrap_builder in
      
      let init_arg i = 
        let struct_load = L.build_load struct_alloca "struct_ptr" unwrap_builder in
        let arg_gep = L.build_in_bounds_gep struct_load [|L.const_int i32_t 0; L.const_int i32_t i|] "arg_gep" unwrap_builder in
        let arg_load = L.build_load arg_gep "arg" unwrap_builder in arg_load
      in 
      let func_args = Array.init (Array.length (L.params fdef)) (init_arg) in
      let _ = L.build_call fdef func_args (if L.return_type (L.return_type hatching_func_t) = void_t then "" else "result") unwrap_builder in

      let _ = L.build_ret (L.const_null string_t) unwrap_builder in

      (* Hatch Threads *)
      let length_alloca = L.build_alloca i32_t "nl_length" builder in
      let list_length = expr builder (A.Int, SCall("length_NL", [nl])) in
      let _ = L.build_store list_length length_alloca builder in
      
      let pthreads_alloca = L.build_alloca (L.pointer_type i64_t) "pthread_array" builder in
      let args_alloca = L.build_alloca (L.pointer_type hatch_t) "args_array" builder in
      let malloc_func_t = L.function_type string_t [| i64_t |] in
      let malloc_func = L.declare_function "malloc" malloc_func_t the_module in

      let build_malloc numval typ =  
        let length_load = L.build_load length_alloca "length" builder in
        let sext = L.build_sext length_load i64_t "sext_length" builder in
        let mul = L.build_mul numval sext "bytes" builder in
        let malloc = L.build_call malloc_func [| mul |] "malloc" builder (*L.build_array_malloc string_t mul "malloc" builder*) in 
        let bitcast = L.build_bitcast malloc typ "cast_mem" builder in
      bitcast in
      let _ = L.build_store (build_malloc (L.const_int i64_t 8) (L.pointer_type i64_t)) pthreads_alloca builder in
      let _ = L.build_store (build_malloc (L.const_int i64_t (List.fold_left (fun i t -> i + size_of_typ t) 0 argtypes)) (L.pointer_type hatch_t)) args_alloca builder in
      
      let i_alloca = L.build_alloca i32_t "i" builder in
      let _ = L.build_store (L.const_int i32_t 0) i_alloca builder in
       
      (* For Loop *) 
      let list_alloca = L.build_alloca nodelist_pointer "list" builder in
        let item_alloca = L.build_alloca nodelistitem_pointer "item" builder and
        _ = L.build_store (expr builder nl) list_alloca builder in
        let list_load = L.build_load list_alloca "list" builder in
        let list_gep = L.build_in_bounds_gep list_load [|L.const_int i32_t 0; L.const_int i32_t 1|] "list_gep" builder in
        let list_pointer = L.build_load list_gep "item_ptr" builder in
        let _ = L.build_store list_pointer item_alloca builder in
        

        let pred_bb = L.append_block context "hatch_for" the_function in 
        ignore(L.build_br pred_bb builder);


        let body_bb = L.append_block context "hatch_for_body" the_function in
        let endfor_bb = L.append_block context "hatch_end_for" the_function in
        let body_builder = L.builder_at_end context body_bb in 
        let item_load = L.build_load item_alloca "item" body_builder in
        let item_gep = L.build_in_bounds_gep item_load [|L.const_int i32_t 0; L.const_int i32_t 0|] "item_gep" body_builder in
        let set_up_struct ld num = 
          let load_struct = L.build_load args_alloca "arg" body_builder in
          let load_i = L.build_load i_alloca "i" body_builder in
          let sext = L.build_sext load_i i64_t "i" body_builder in
          let gep1 = L.build_in_bounds_gep load_struct [| sext |] "gep1" body_builder in
          let field_gep = L.build_in_bounds_gep gep1 [| L.const_int i32_t 0; L.const_int i32_t num |] "field_gep" body_builder in
          let _ = L.build_store ld field_gep body_builder in () 
        in 
        let _ = set_up_struct (L.build_load item_gep "val" body_builder) 0 in
        let _ = Array.init (Array.length (L.params fdef) - 1) (fun x -> set_up_struct (expr body_builder (List.nth args x)) (x + 1)) in

        let load_pthreads = L.build_load pthreads_alloca "pthreads" body_builder in
        let load_i = L.build_load i_alloca "i" body_builder in
        let sext = L.build_sext load_i i64_t "i" body_builder in
        let pthread_gep = L.build_in_bounds_gep load_pthreads [| sext |] "pthread_gep" body_builder in
        let load_args = L.build_load args_alloca "args" body_builder in
        let load_i = L.build_load i_alloca "i" body_builder in
        let sext = L.build_sext load_i i64_t "i" body_builder in
        let args_gep = L.build_in_bounds_gep load_args [| sext |] "args_gep" body_builder in
        let void_cast = L.build_bitcast args_gep string_t "cast_ptr" body_builder in

        let pthread_func_t = L.function_type i32_t [| (L.pointer_type i64_t); (L.pointer_type pthread_attr); (L.pointer_type (L.function_type string_t [| string_t |])); string_t |] in
        let pthread_func = L.declare_function "pthread_create" pthread_func_t the_module in
        let _ = L.build_call pthread_func [| pthread_gep; (L.const_pointer_null (L.pointer_type pthread_attr)); unwrapper_func; void_cast |] "pthread_create" body_builder in
        add_terminal body_builder (L.build_br endfor_bb);
        
        
        let end_builder = L.builder_at_end context endfor_bb in 
        let item_load = L.build_load item_alloca "item" end_builder in
        let item_gep = L.build_in_bounds_gep item_load [|L.const_int i32_t 0; L.const_int i32_t 1|] "item_gep" end_builder in
        let next_item_load = L.build_load item_gep "next" end_builder in
        let _ = L.build_store next_item_load item_alloca end_builder in
        let load_i = L.build_load i_alloca "i" end_builder in
        let add_i = L.build_nsw_add load_i (L.const_int i32_t 1) "add_one" end_builder in
        let _ = L.build_store add_i i_alloca end_builder in
        add_terminal end_builder (L.build_br pred_bb);

        let pred_builder = L.builder_at_end context pred_bb in
        let bool_val = let item_load = L.build_load item_alloca "item" pred_builder in 
          L.build_is_not_null item_load "bool" pred_builder in                

        let parent_bb = L.append_block context "parent_actions" the_function in
        let merge_bb = L.append_block context "hatch_formerge" the_function in
        let parent_builder = L.builder_at_end context parent_bb in 
        add_terminal (stmt (parent_builder) stmts) (L.build_br merge_bb);
        ignore(L.build_cond_br bool_val body_bb parent_bb pred_builder);
        let merge_builder = L.builder_at_end context merge_bb in

        let load_threads = L.build_load pthreads_alloca "threads" merge_builder in
        let load_length = L.build_load length_alloca "length" merge_builder in
        let hatch_end_func_t = L.function_type i32_t [| (L.pointer_type i64_t); i32_t |] in
        let hatch_end_func = L.declare_function "hatch_end" hatch_end_func_t the_module in
        let _ = L.build_call hatch_end_func [| load_threads; load_length |] "hatch_end" merge_builder in
        merge_builder
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
