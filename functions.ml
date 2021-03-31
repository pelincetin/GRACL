(* Built in function library helpers *)

module L = Llvm
open Sast 
open Ast
module StringMap = Map.Make(String)
let function_decls = 
    let add_func map (typ, name, (formallist : formal list)) = StringMap.add name {
      typ = typ; 
      fname = name; 
      formals = formallist;
      locals = []; body = [] } map in List.fold_left add_func StringMap.empty [ 
        (Void, "print", [String, "s"]);
        (Void, "printi", [Int, "i"]);
        (String, "doubleToString", [Double, "d"]);    
        (Node, "createNode", [String, "s"]); 
        (Void, "printNode", [Node, "n"]);          
		(*("printbig", Int)*) ]
