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
        (Graph, "createGraph", []);

        (* Casting Functions *)
        (String, "doubleToString", [Double, "d"]);    
        
        (* Node Functions *)
        (String, "data", [Node, "n"]);   
        (Nodelist, "neighbors", [Node, "n"]); (* TODO: NEEDS TESTING *)  
        (Edgelist, "edges", [Node, "n"]);
        (Bool, "visited", [Node, "n"]);    
        (Node, "updateData", [(Node, "n"); (String, "s")]); 
        (Node, "updateVisited", [(Node, "n"); (Bool, "b")]);
        (Bool, "nodeEquals", [(Node, "n1"); (Node, "n2")]);

        (* Graph Functions *)
        (Nodelist, "nodes", [Graph, "g"]);
        (Node, "createNode", [(Graph, "g"); (String, "s")]);
        (Int, "removeNodeGraph", [(Graph, "g"); (Node, "n")]);
        (Edge, "addEdge", [(Graph, "g"); (Node, "start"); (Node, "end"); (Double, "weight")]);
        (Int,  "removeEdgeGraph", [(Graph, "g"); (Edge, "e")])
    ]
    
