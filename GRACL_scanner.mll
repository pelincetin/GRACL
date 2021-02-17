{ open GRACL_Parser }

rule tokenize = parse
  [' ' '\t' '\r' '\n'] { tokenize lexbuf }
| '+' { PLUS }
| '-' { MINUS }
| '*' { TIMES }
| '/' { DIVIDE }
| '=' { ASSIGN }
| ';' { SEMICOLON }
| ['0'-'9']+ as lit { LITERAL(int_of_string lit) }
| ['a'-'z']+ as lit  { ID(lit) }
| eof { EOF }