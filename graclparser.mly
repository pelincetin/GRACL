/* Ocamlyacc parser for GRACL */

%{
open Ast

(*
let parse_error s =
      begin
        try
          let start_pos = Parsing.symbol_start_pos ()
          and end_pos = Parsing.symbol_end_pos () in
          Printf.printf "File \"%s\", line %d, characters %d-%d: \n"
            start_pos.pos_fname
            start_pos.pos_lnum
            (start_pos.pos_cnum - start_pos.pos_bol)
            (end_pos.pos_cnum - start_pos.pos_bol)
        with Invalid_argument(_) -> ()
      end;
      Printf.printf "Syntax error: %s\n" s;
      raise Parsing.Parse_error *)

%}

%token SEMI LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK COMMA DOT PLUS MINUS TIMES DIVIDE MODULO ASSIGN
%token NOT EQ LT LEQ GT GEQ AND OR NEQ
%token RETURN IF ELSE FOR WHILE IN 
%token INT BOOL DOUBLE VOID STRING NODE EDGE GRAPH EDGELIST NODELIST INTTABLE DOUBLETABLE 
%token <int> LITERAL
%token <bool> BLIT
%token <string> ID FLIT SLIT
%token EOF

%start program
%type <Ast.program> program

%nonassoc NOELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left EQ NEQ
%left LT LEQ GT GEQ
%left PLUS MINUS
%left TIMES DIVIDE MODULO
%right NOT
%left DOT

%%     

program:
  progparts EOF { List.rev $1 }

progparts:
   /* nothing */ { ([])         }
 | progparts vdecl { (GlobBind($2) :: $1) }
 | progparts fdecl { (FuncDecl($2) :: $1) }

fdecl:
   typ ID LPAREN formals_opt RPAREN LBRACE func_body RBRACE
     { { typ = $1;
	 fname = $2;
	 formals = List.rev $4;
	 body = List.rev ( $7 ) } }

func_body:
    /* nothing */     { ([])                }
  | func_body stmt    { ($2 :: $1) }

formals_opt:
    /* nothing */ { [] }
  | formal_list   { $1 }

formal_list:
    typ ID                   { [($1,$2)]     }
  | formal_list COMMA typ ID { ($3,$4) :: $1 }

typ:
    INT   { Int   }
  | BOOL  { Bool  }
  | DOUBLE { Double }
  | VOID  { Void  }
  | STRING { String }
  | GRAPH { Graph }
  | NODE { Node }
  | EDGE { Edge }
  | INTTABLE { Inttable }
  | DOUBLETABLE { Doubletable }
  | NODELIST { Nodelist }
  | EDGELIST { Edgelist }

vdecl:
   typ ID SEMI { Dec($1, $2) }
   | typ ID ASSIGN expr SEMI { Decinit($1, $2, $4) }

stmt_list:
    /* nothing */  { [] }
  | stmt_list stmt { $2 :: $1 }

stmt:
    expr SEMI                                             { Expr $1                }
  | RETURN expr_opt SEMI                                  { Return $2              }
  | LBRACE stmt_list RBRACE                               { Block(List.rev (BlockEnd::$2))     }
  | IF LPAREN expr RPAREN stmt %prec NOELSE               { If($3, $5, Block([]))  }
  | IF LPAREN expr RPAREN stmt ELSE stmt                  { If($3, $5, $7)         }
  | FOR LPAREN typ ID IN expr RPAREN stmt                 { For($3, $4, $6, Block(LoclBind(Dec($3, $4))::$8::[BlockEnd]))    }                             
  | WHILE LPAREN expr RPAREN stmt                         { While($3, $5)          }
  | vdecl                                                 { LoclBind($1)           }

expr_opt:
    /* nothing */ { Noexpr }
  | expr          { $1 }

expr:
    LITERAL          { Literal($1)                       }
  | FLIT	           { Fliteral($1)                      }
  | BLIT             { BoolLit($1)                       }
  | SLIT             { Sliteral($1)                      }
  | ID               { Id($1)                            }
  | expr PLUS   expr { Binop($1, Add,   $3)              }
  | expr MINUS  expr { Binop($1, Sub,   $3)              }
  | expr TIMES  expr { Binop($1, Mult,  $3)              }
  | expr DIVIDE expr { Binop($1, Div,   $3)              }
  | expr MODULO expr { Binop($1, Mod,   $3)              }
  | expr EQ     expr { Binop($1, Equal, $3)              }
  | expr NEQ    expr { Binop($1, Neq,   $3)              }
  | expr LT     expr { Binop($1, Less,  $3)              }
  | expr GT     expr { Binop($1, Great, $3)              } 
  | expr LEQ    expr { Binop($1, Leq,   $3)              }
  | expr GEQ    expr { Binop($1, Geq,   $3)              }
  | expr AND    expr { Binop($1, And,   $3)              }
  | expr OR     expr { Binop($1, Or,    $3)              }
  | MINUS expr %prec NOT { Unop(Neg, $2)                 }
  | NOT expr         { Unop(Not, $2)                     }
  | ID ASSIGN expr   { Assign($1, $3)                    }
  | ID LPAREN args_opt RPAREN { Call($1, $3)             }
  | call_train ID LPAREN args_opt RPAREN { Call($2, $1 @ $4)}
  | ID LBRACK ID RBRACK { Access($1, $3)                 }
  | ID LBRACK ID RBRACK ASSIGN expr { Insert($1, $3, $6) }
  | LPAREN expr RPAREN { $2                              }

call_train:
    call_train ID LPAREN args_opt RPAREN DOT { [Call($2, $1 @ $4)] }
  | ID DOT { [Id($1)] }
  | ID LPAREN args_opt RPAREN DOT { [Call($1, $3)]}

args_opt:
    /* nothing */ { [] }
  | args_list  { List.rev $1 }

args_list:
    expr                    { [$1] }
  | args_list COMMA expr { $3 :: $1 }
