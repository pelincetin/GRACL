(* Abstract Syntax Tree and functions for printing it *)

type op = Add | Sub | Mult | Div | Mod | Equal | Less | Leq | 
          And | Or

type uop = Neg | Not

type typ = Int | Bool | Void | Double | String | Graph | Node | Edge |
           Inttable | Doubletable | Nodelist | Edgelist | Lock

type bind = typ * string

type expr =
    Literal of int
  | Fliteral of string
  | BoolLit of bool
  | Sliteral of string
  | Id of string
  | Binop of expr * op * expr
  | Unop of uop * expr
  | Assign of string * expr
  | Call of string * expr list
  | Access of string * string
  | Insert of string * string * expr
  | Noexpr

type stmt =
    Block of stmt list
  | Expr of expr
  | Return of expr
  | If of expr * stmt * stmt
  | NodeFor of string * string * stmt 
  | EdgeFor of string * string * stmt 
  | While of expr * stmt
  | Hatch of expr * string * expr list * stmt
  | Synch of expr * stmt list

type func_decl = {
    typ : typ;
    fname : string;
    formals : bind list;
    locals : bind list;
    body : stmt list;
  }

type program = bind list * func_decl list

(* Pretty-printing functions *)

let string_of_op = function
    Add -> "+"
  | Sub -> "-"
  | Mult -> "*"
  | Div -> "/"
  | Mod -> "%"
  | Equal -> "=="
  | Less -> "<"
  | Leq -> "<="
  | And -> "&&"
  | Or -> "||"

let string_of_uop = function
    Neg -> "-"
  | Not -> "!"

let rec string_of_expr = function
    Literal(l) -> string_of_int l
  | Fliteral(l) -> l
  | Sliteral(l) -> l
  | BoolLit(true) -> "true"
  | BoolLit(false) -> "false"
  | Id(s) -> s
  | Binop(e1, o, e2) ->
      string_of_expr e1 ^ " " ^ string_of_op o ^ " " ^ string_of_expr e2
  | Unop(o, e) -> string_of_uop o ^ string_of_expr e
  | Assign(v, e) -> v ^ " = " ^ string_of_expr e
  | Call(f, el) ->
      f ^ "(" ^ String.concat ", " (List.map string_of_expr el) ^ ")"
  | Access(t, n) -> t ^ "[" ^ n ^ "]"
  | Insert(t, n, e) -> t ^ "[" ^ n ^ "] = " ^ string_of_expr e
  | Noexpr -> ""

let rec string_of_stmt = function
    Block(stmts) ->
      "{\n" ^ String.concat "" (List.map string_of_stmt stmts) ^ "}\n"
  | Expr(expr) -> string_of_expr expr ^ ";\n";
  | Return(expr) -> "return " ^ string_of_expr expr ^ ";\n";
  | If(e, s1, s2) ->  "if (" ^ string_of_expr e ^ ")\n" ^
      string_of_stmt s1 ^ "else\n" ^ string_of_stmt s2
  | NodeFor(n, l, s) -> "for (Node " ^ n ^ " in " ^ l ^ ") " ^ string_of_stmt s
  | EdgeFor(e, l, s) -> "for (Edge " ^ e ^ " in " ^ l ^ ") " ^ string_of_stmt s
  | While(e, s) -> "while (" ^ string_of_expr e ^ ") " ^ string_of_stmt s
  | Hatch(e, f, el, s) -> "hatch " ^ string_of_expr e ^ 
      f ^ "(" ^ String.concat ", " (List.map string_of_expr el) ^ ") " ^ string_of_stmt s
  | Synch(l, stmts) -> "synch " ^ string_of_expr l ^ 
      "{\n" ^ String.concat "" (List.map string_of_stmt stmts) ^ "}\n"

let string_of_typ = function
    Int -> "int"
  | Bool -> "bool"
  | Void -> "void"
  | Double -> "double"
  | String -> "String"
  | Graph -> "Graph"
  | Node -> "Node"
  | Edge -> "Edge"
  | Inttable -> "IntTable"
  | Doubletable -> "DoubleTable"
  | Nodelist -> "NodeList"
  | Edgelist -> "EdgeList"
  | Lock -> "Lock"

let string_of_vdecl (t, id) = string_of_typ t ^ " " ^ id ^ ";\n"

let string_of_fdecl fdecl =
  string_of_typ fdecl.typ ^ " " ^
  fdecl.fname ^ "(" ^ String.concat ", " (List.map snd fdecl.formals) ^
  ")\n{\n" ^
  String.concat "" (List.map string_of_vdecl fdecl.locals) ^
  String.concat "" (List.map string_of_stmt fdecl.body) ^
  "}\n"

let string_of_program (vars, funcs) =
  String.concat "" (List.map string_of_vdecl vars) ^ "\n" ^
  String.concat "\n" (List.map string_of_fdecl funcs)
