(* Semantically-checked Abstract Syntax Tree and functions for printing it *)

open Ast

type sexpr = typ * sx
and sx =
    SLiteral of int
  | SFliteral of string
  | SBoolLit of bool
  | SSliteral of string
  | SId of string
  | SBinop of sexpr * op * sexpr
  | SUnop of uop * sexpr
  | SAssign of string * sexpr
  | SCall of string * sexpr list
  | SAccess of string * string
  | SInsert of string * string * sexpr
  | SMethod of string * (string * sexpr list) list
  | SNoexpr

type sstmt =
    SBlock of sstmt list
  | SExpr of sexpr
  | SReturn of sexpr
  | SIf of sexpr * sstmt * sstmt
  | SNodeFor of string * string * sstmt 
  | SEdgeFor of string * string * sstmt 
  | SWhile of sexpr * sstmt
  (*| Hatch of expr * string * expr list * stmt *)
  | SSynch of string * sstmt list


type sfunc_decl = {
    styp : typ;
    sfname : string;
    sformals : bind list;
    slocals : bind list;
    sbody : sstmt list;
  }

type sprogram = bind list * sfunc_decl list

(* Pretty-printing functions *)

let rec string_of_sexpr (t, e) =
  "(" ^ string_of_typ t ^ " : " ^ (match e with
    SLiteral(l) -> string_of_int l
  | SBoolLit(true) -> "true"
  | SBoolLit(false) -> "false"
  | SSliteral(l) -> l 
  | SFliteral(l) -> l
  | SId(s) -> s
  | SBinop(e1, o, e2) ->
      string_of_sexpr e1 ^ " " ^ string_of_op o ^ " " ^ string_of_sexpr e2
  | SUnop(o, e) -> string_of_uop o ^ string_of_sexpr e
  | SAssign(v, e) -> v ^ " = " ^ string_of_sexpr e
  | SCall(f, el) ->
      f ^ "(" ^ String.concat ", " (List.map string_of_sexpr el) ^ ")"
  | SAccess(t, n) -> t ^ "[" ^ n ^ "]"
  | SInsert(t, n, e) -> t ^ "[" ^ n ^ "] = " ^ string_of_sexpr e
  | SMethod(obj, calls) -> obj ^ "." ^ String.concat "." 
   (List.map  (fun (f, el) -> f ^ "(" ^ String.concat ", " (List.map string_of_sexpr el) ^ ")") calls)
  | SNoexpr -> ""
				  ) ^ ")"				     

let rec string_of_sstmt = function
    SBlock(stmts) ->
      "{\n" ^ String.concat "" (List.map string_of_sstmt stmts) ^ "}\n"
  | SExpr(expr) -> string_of_sexpr expr ^ ";\n";
  | SReturn(expr) -> "return " ^ string_of_sexpr expr ^ ";\n";
  | SIf(e, s, SBlock([])) ->
      "if (" ^ string_of_sexpr e ^ ")\n" ^ string_of_sstmt s
  | SIf(e, s1, s2) ->  "if (" ^ string_of_sexpr e ^ ")\n" ^
      string_of_sstmt s1 ^ "else\n" ^ string_of_sstmt s2
  | SWhile(e, s) -> "while (" ^ string_of_sexpr e ^ ") " ^ string_of_sstmt s
  | SNodeFor(n, l, s) -> "for (Node " ^ n ^ " in " ^ l ^ ") " ^ string_of_sstmt s
  | SEdgeFor(e, l, s) -> "for (Edge " ^ e ^ " in " ^ l ^ ") " ^ string_of_sstmt s
  (*| Hatch(e, f, el, s) -> "hatch " ^ string_of_expr e ^ 
      f ^ "(" ^ String.concat ", " (List.map string_of_expr el) ^ ") " ^ string_of_stmt s *)
  | SSynch(l, stmts) -> "synch " ^ l ^ 
      "{\n" ^ String.concat "" (List.map string_of_sstmt stmts) ^ "}\n"
let string_of_sfdecl fdecl =
  string_of_typ fdecl.styp ^ " " ^
  fdecl.sfname ^ "(" ^ String.concat ", " (List.map string_of_vdecl fdecl.sformals) ^
  ")\n{\n" ^
  String.concat "" (List.map string_of_vdecl fdecl.slocals) ^
  String.concat "" (List.map string_of_sstmt fdecl.sbody) ^
  "}\n"

let string_of_sprogram (vars, funcs) =
  String.concat "" (List.map string_of_vdecl vars) ^ "\n" ^
  String.concat "\n" (List.map string_of_sfdecl funcs)
