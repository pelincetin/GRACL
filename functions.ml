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
        (Nodelist, "createNodeList", []);
        (Edgelist, "createEdgeList", []);

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

        (* Edge Functions *)                  (* TODO: TEST ALL OF THIS *)
        (Void, "updateEdge", [(Edge, "e"); (Double, "d")]);
        (Node, "start", [Edge, "e"]);
        (Node, "end", [Edge, "e"]);
        (Double, "weight", [Edge, "e"]);
        (Bool, "edgeEquals", [(Edge, "e1"); (Edge, "e2")]);

        (* Graph Functions *)                  (* TODO: TEST ALL OF THIS *)
        (Nodelist, "nodes", [Graph, "g"]);    
        (Node, "createNode", [(Graph, "g"); (String, "s")]);
        (Int, "removeNodeGraph", [(Graph, "g"); (Node, "n")]);
        (Edge, "addEdge", [(Graph, "g"); (Node, "start"); (Node, "end"); (Double, "weight")]);
        (Int,  "removeEdgeGraph", [(Graph, "g"); (Edge, "e")]);

        (* Nodelist Functions *)             (* TODO: TEST ALL OF THIS *)
        (Int, "length_NL", [Nodelist, "n"]);
        (Bool, "empty_NL", [Nodelist, "n"]);
        (Int, "removeNode", [(Nodelist, "nl"); (Node, "n")]);
        (Node, "removeFirst_NL", [Nodelist, "n"]);
        (Node, "removeLast_NL", [Nodelist, "n"]);
        (Void, "appendNode", [(Nodelist, "nl"); (Node, "n")]);
        (Void, "prependNode", [(Nodelist, "nl"); (Node, "n")]);

        (* Edgelist Functions *)                  (* TODO: TEST ALL OF THIS *)
        (Int, "length_EL", [Edgelist, "e"]);
        (Bool, "empty_EL", [Edgelist, "e"]);
        (Int, "removeEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Node, "removeFirst_EL", [Edgelist, "e"]);
        (Node, "removeLast_EL", [Edgelist, "e"]);
        (Void, "appendEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Void, "prependEdge", [(Edgelist, "el"); (Edge, "e")]);

        (* IntTable Functions *)

        (* DoubleTable Functions *)
    ]
    
