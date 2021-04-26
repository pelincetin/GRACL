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
        (Graph, "createGraph", [Int, "i"]);
        (Nodelist, "createNodeList", []);
        (Edgelist, "createEdgeList", []);
        (Doubletable, "createDoubleTable", [Int, "i"]);
        (Inttable, "createIntTable", [Int, "i"]);

        (* Casting Functions *)
        (String, "doubleToString", [Double, "d"]);
        (Double, "intToDouble", [Int, "i"]);

        (* String Functions *)
        (Int, "stringLength", [String, "s"]);
        (Bool, "stringEquals", [(String, "s1"); (String, "s2")]);    
        
        (* Node Functions *)
        (String, "data", [Node, "n"]);   
        (Nodelist, "neighbors", [Node, "n"]);  
        (Edgelist, "edges", [Node, "n"]);     
        (Bool, "visited", [Node, "n"]);    
        (Node, "updateData", [(Node, "n"); (String, "s")]); 
        (Node, "updateVisited", [(Node, "n"); (Bool, "b")]);
        (Double, "cost", [Node, "n"]);
        (Double, "incrementCost", [Node, "n"]);
        (Double, "decrementCost", [Node, "n"]);   
        (Double, "updateCost", [(Node, "n1"); (Double, "i")]); 
        (Node, "prec", [Node, "n"]);  
        (Node, "setPrec", [(Node, "n1"); (Node, "n2")]);    
        (Bool, "nodeEquals", [(Node, "n1"); (Node, "n2")]);
        (Edge, "getEdge", [(Node, "n1"); (Node, "n2")]);

        (* Edge Functions *)                  
        (Void, "updateEdge", [(Edge, "e"); (Double, "d")]);
        (Node, "start", [Edge, "e"]);
        (Node, "end", [Edge, "e"]);
        (Double, "weight", [Edge, "e"]);
        (Bool, "edgeEquals", [(Edge, "e1"); (Edge, "e2")]);

        (* Graph Functions *)
        (Nodelist, "nodes", [Graph, "g"]);    
        (Node, "createNode", [(Graph, "g"); (String, "s")]);
        (Int, "removeNodeGraph", [(Graph, "g"); (Node, "n")]);
        (Edge, "addEdge", [(Graph, "g"); (Node, "start"); (Node, "end"); (Double, "weight")]);
        (Int,  "removeEdgeGraph", [(Graph, "g"); (Edge, "e")]);

        (* Nodelist Functions *)
        (Node, "head_NL", [Nodelist, "nl"]);
        (Node, "tail_NL", [Nodelist, "nl"]);
        (Int, "length_NL", [Nodelist, "nl"]);
        (Bool, "empty_NL", [Nodelist, "nl"]);
        (Int, "removeNode", [(Nodelist, "nl"); (Node, "n")]);
        (Node, "removeFirst_NL", [Nodelist, "nl"]);
        (Node, "removeLast_NL", [Nodelist, "nl"]);
        (Void, "appendNode", [(Nodelist, "nl"); (Node, "n")]);
        (Void, "prependNode", [(Nodelist, "nl"); (Node, "n")]);
        (Bool, "includesNode", [(Nodelist, "nl"); (Node, "n")]);
        (Nodelist, "neighbors", [(Node, "node")]);

        (* Edgelist Functions *)
        (Edge, "head_EL", [Edgelist, "el"]);
        (Edge, "tail_EL", [Edgelist, "el"]);
        (Int, "length_EL", [Edgelist, "el"]);
        (Bool, "empty_EL", [Edgelist, "el"]);
        (Int, "removeEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Edge, "removeFirst_EL", [Edgelist, "el"]);
        (Edge, "removeLast_EL", [Edgelist, "el"]);
        (Void, "appendEdge", [(Edgelist, "el"); (Edge, "e")]);
        (Void, "prependEdge", [(Edgelist, "el"); (Edge, "e")]);

        (* Inttable Functions *)
        (Int, "hashCode_it", [(Inttable, "it"); (Node, "n")]);
        (Int, "_getInt", [(Inttable, "it"); (Node, "n")]);
        (Void, "_insertInt", [(Inttable, "it"); (Node, "n"); (Int, "i")]);
        (Nodelist, "intKeys", [Inttable, "it"]);
        (Int, "deleteInt", [(Inttable, "it"); (Node, "n")]);
        (Bool, "inInt", [(Inttable, "it"); (Node, "n")]);

        (* Doubletable Functions *)
        (Int, "hashCode_it", [(Doubletable, "dt"); (Node, "n")]);
        (Double, "_getDouble", [(Doubletable, "dt"); (Node, "n")]);
        (Void, "_insertDouble", [(Doubletable, "dt"); (Node, "n"); (Double, "d")]);
        (Nodelist, "doubleKeys", [Doubletable, "dt"]);
        (Int, "deleteDouble", [(Doubletable, "dt"); (Node, "n")]);
        (Bool, "inDouble", [(Doubletable, "dt"); (Node, "n")]);
    ]
    
