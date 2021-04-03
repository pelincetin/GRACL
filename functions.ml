(* Built in function library helpers *)

open Ast
module StringMap = Map.Make(String)
let function_decls = 
    let add_func map (typ, name, (formallist : formal list)) = StringMap.add name {
      typ = typ; 
      fname = name; 
      formals = formallist;
      locals = []; body = [] } map in List.fold_left add_func StringMap.empty [ 
        (* General Functions *)
        (Void, "print", [String, "s"]);
        (Void, "printi", [Int, "i"]);

        (* Casting Functions *)
        (String, "doubleToString", [Double, "d"]);    
        
        (* Node Functions *)
        (Node, "createNode", [String, "s"]);  (* Should be moved to graph functions *)
        (Void, "printNode", [Node, "n"]);     (* Should be removed *)
        (String, "data", [Node, "n"]);     
        (Edgelist, "edges", [Node, "n"]);
        (Bool, "visited", [Node, "n"]);    
        (Node, "updateData", [(Node, "n"); (String, "s")]); 
        (Node, "updateVisited", [(Node, "n"); (Bool, "b")]);
        (Bool, "nodeEquals", [(Node, "n1"); (Node, "n2")])
		]
