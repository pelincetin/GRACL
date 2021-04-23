(* Abstract Syntax Tree and functions for printing it *)

type op = Add | Sub | Mult | Div | Mod | Equal | Neq | Less | Great | Leq | Geq |
          And | Or

type uop = Neg | Not

type typ = Int | Bool | Void | Double | String | Graph | Node | Edge |
           Inttable | Doubletable | Nodelist | Edgelist 

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
     
type bind =  
    Dec of typ * string
  | Decinit of typ * string * expr

type formal = typ * string

type stmt =
    Block of stmt list
  | BlockEnd 
  | Expr of expr
  | Return of expr
  | If of expr * stmt * stmt
  | For of typ * string * expr * stmt 
  | While of expr * stmt
  | LoclBind of bind

type func_decl = {
    typ : typ;
    fname : string;
    formals : formal list;
    body : stmt list;
  }

type progpart =
    FuncDecl of func_decl
  | GlobBind of bind
  

type program = progpart list

(* Pretty-printing functions *)

let string_of_op = function
    Add -> "+"
  | Sub -> "-"
  | Mult -> "*"
  | Div -> "/"
  | Mod -> "%"
  | Equal -> "=="
  | Neq -> "!="
  | Less -> "<"
  | Great -> ">"
  | Leq -> "<="
  | Geq -> ">="
  | And -> "&&"
  | Or -> "||"

let string_of_uop = function
    Neg -> "-"
  | Not -> "!"

let name_of_bind = function
    Dec(_, n) -> n
  | Decinit(_, n, _) -> n
let strip_val = function
    Dec(a, b) -> (a, b)
  | Decinit(a, b, _) -> (a, b)
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

let string_of_vdecl = function
| Dec(t, id) -> string_of_typ t ^ " " ^ id ^ ";\n"
| Decinit(t, id, e) -> string_of_typ t ^ " " ^ id ^ " = " ^ string_of_expr e ^ ";\n"
let rec string_of_stmt = function
    Block(stmts) ->
      "{\n" ^ String.concat "" (List.map string_of_stmt stmts) ^ "}\n"
  | Expr(expr) -> string_of_expr expr ^ ";\n";
  | Return(expr) -> "return " ^ string_of_expr expr ^ ";\n";
  | If(e, s, Block([])) -> "if (" ^ string_of_expr e ^ ")\n" ^ string_of_stmt s
  | If(e, s1, s2) ->  "if (" ^ string_of_expr e ^ ")\n" ^
      string_of_stmt s1 ^ "else\n" ^ string_of_stmt s2
  | For(t, n, e, s) -> "for (" ^ string_of_typ t ^ " " ^ n ^ " in " ^ string_of_expr e ^ ") " ^ string_of_stmt s
  | While(e, s) -> "while (" ^ string_of_expr e ^ ") " ^ string_of_stmt s
  | LoclBind(b) -> string_of_vdecl b
  | BlockEnd -> "BlockEnd\n"



let string_of_fdecl fdecl =
  string_of_typ fdecl.typ ^ " " ^
  fdecl.fname ^ "(" ^ String.concat ", " (List.map snd fdecl.formals) ^
  ")\n{\n" ^
  String.concat "" (List.map string_of_stmt fdecl.body) ^
  "}\n"

let string_of_progpart = function
| FuncDecl(f) -> string_of_fdecl f
| GlobBind(b) -> string_of_vdecl b
let string_of_program (progparts) =
  String.concat "" (List.map string_of_progpart progparts) 