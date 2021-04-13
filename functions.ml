(* Built in function library helpers *)

open Ast
module StringMap = Map.Make(String)
let function_decls = 
    let add_func map (typ, name, (formallist : formal list)) = StringMap.add name {
      typ = typ; 
      fname = name; 
      formals = formallist;
      body = [] } map in List.fold_left add_func StringMap.empty [ 
        (* General Functions *)
        (Void, "print", [String, "s"]);
        (Void, "printi", [Int, "i"]);
        (Graph, "createGraph", []);
        (Nodelist, "createNodeList", []);
        (Edgelist, "createEdgeList", []);

        (* Casting Functions *)
        (String, "doubleToString", [Double, "d"]);
        (Double, "intToDouble", [Int, "i"]);

        (* String Functions *)
        (Int, "stringLength", [String, "s"]);
        (Bool, "stringEquals", [(String, "s1"); (String, "s2")]);    
        
        (* Node Functions *)
        (String, "data", [Node, "n"]);   
        (Nodelist, "neighbors", [Node, "n"]); (* TODO: NEEDS TESTING *)  
        (Edgelist, "edges", [Node, "n"]);     (* TODO: NEEDS TESTING *)  
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
        (Node, "head_NL", [Nodelist, "nl"]);
        (Node, "tail_NL", [Nodelist, "nl"]);
        (Int, "length_NL", [Nodelist, "nl"]);
        (Bool, "empty_NL", [Nodelist, "nl"]);
        (Int, "removeNode", [(Nodelist, "nl"); (Node, "n")]);
        (Node, "removeFirst_NL", [Nodelist, "nl"]);
        (Node, "removeLast_NL", [Nodelist, "nl"]);
        (Void, "appendNode", [(Nodelist, "nl"); (Node, "n")]);
        (Void, "prependNode", [(Nodelist, "nl"); (Node, "n")]);

        (* Edgelist Functions *)                  (* TODO: TEST ALL OF THIS *)
        (Edge, "head_EL", [Edgelist, "el"]);
        (Edge, "tail_EL", [Edgelist, "el"]);
        (Int, "length_EL", [Edgelist, "el"]);
        (Bool, "empty_EL", [Edgelist, "el"]);
        (Int, "removeEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Edge, "removeFirst_EL", [Edgelist, "el"]);
        (Edge, "removeLast_EL", [Edgelist, "el"]);
        (Void, "appendEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Void, "prependEdge", [(Edgelist, "el"); (Edge, "e")]);

        (* IntTable Functions *)

        (* DoubleTable Functions *)
    ]
    
