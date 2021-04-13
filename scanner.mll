(* Ocamllex scanner for MicroC *)

{ open Graclparser }

let digit = ['0' - '9']
let digits = digit+

rule token = parse
  [' ' '\t' '\r' '\n'] { token lexbuf } (* Whitespace *)
| "/*"     { comment lexbuf }           (* Comments *)
| "//"     { slcomment lexbuf }
| '('      { LPAREN }
| ')'      { RPAREN }
| '{'      { LBRACE }
| '}'      { RBRACE }
| '['      { LBRACK }
| ']'      { RBRACK }
| ';'      { SEMI }
| '.'      { DOT }
| ','      { COMMA }
| '+'      { PLUS }
| '-'      { MINUS }
| '*'      { TIMES }
| '/'      { DIVIDE }
| '%'      { MODULO }
| '='      { ASSIGN }
| "=="     { EQ }
| "!="     { NEQ }
| '<'      { LT }
| '>'      { GT }
| "<="     { LEQ }
| ">="     { GEQ }
| "&&"     { AND }
| "||"     { OR }
| "!"      { NOT }
| "if"     { IF }
| "else"   { ELSE }
| "for"    { FOR }
| "in"     { IN }
| "while"  { WHILE }
| "return" { RETURN }
| "int"    { INT }
| "bool"   { BOOL }
| "double" { DOUBLE }
| "void"   { VOID }
| "String" { STRING }
| "Node"   { NODE }
| "Edge"   { EDGE }
| "Graph"  { GRAPH }
| "EdgeList" { EDGELIST }
| "NodeList" { NODELIST }
| "IntTable" { INTTABLE }
| "DoubleTable" { DOUBLETABLE }   
| "True"   { BLIT(true)  }
| "False"  { BLIT(false) }
| "infinity" { FLIT("infinity") }
| '\"'[^'\"']*'\"' as str { SLIT(String.sub str 1 ((String.length str) - 2))} 
| digits as lxm { LITERAL(int_of_string lxm) }
| digits '.'  digit* ( ['e' 'E'] ['+' '-']? digits )? as lxm { FLIT(lxm) } 
| ['a'-'z' 'A'-'Z']['a'-'z' 'A'-'Z' '0'-'9' '_']*     as lxm { ID(lxm) }
| eof { EOF }
| _ as char { raise (Failure("illegal character " ^ Char.escaped char)) }

and comment = parse
  "*/" { token lexbuf }
| _    { comment lexbuf }

and slcomment = parse 
  '\n' { token lexbuf }
| _ { slcomment lexbuf }