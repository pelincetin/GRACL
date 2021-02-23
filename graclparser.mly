/* Ocamlyacc parser for GRACL */

%{
open Ast
%}

%token SEMI LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK COMMA DOT PLUS MINUS TIMES DIVIDE MODULO ASSIGN
%token NOT EQ LT LEQ AND OR
%token RETURN IF ELSE FOR WHILE IN HATCH SYNCH 
%token INT BOOL DOUBLE VOID STRING NODE EDGE GRAPH LOCK EDGELIST NODELIST INTTABLE DOUBLETABLE 
%token <int> LITERAL
%token <bool> BLIT
%token <string> ID FLIT SLIT
%token EOF

%start program
%type <Ast.program> program


%right ASSIGN
%left OR
%left AND
%left EQ 
%left LT LEQ
%nonassoc HATCH SYNCH
%left PLUS MINUS
%left TIMES DIVIDE MODULO
%right NOT
%left DOT

%%     /* Javalike function calls (chainable), dec + init, fdecl vdecl b4 statements */

program:
  decls EOF { $1 }

decls:
   /* nothing */ { ([], [])               }
 | decls vdecl { (($2 :: fst $1), snd $1) }
 | decls fdecl { (fst $1, ($2 :: snd $1)) }

fdecl:
   typ ID LPAREN formals_opt RPAREN LBRACE vdecl_list stmt_list RBRACE
     { { typ = $1;
	 fname = $2;
	 formals = List.rev $4;
	 locals = List.rev $7;
	 body = List.rev $8 } }

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
  | LOCK { Lock }


vdecl_list:
    /* nothing */    { [] }
  | vdecl_list vdecl { $2 :: $1 }

vdecl:
   typ ID SEMI { ($1, $2) }

stmt_list:
    /* nothing */  { [] }
  | stmt_list stmt { $2 :: $1 }

stmt:
    expr SEMI                                             { Expr $1                }
  | RETURN expr_opt SEMI                                  { Return $2              }
  | LBRACE stmt_list RBRACE                               { Block(List.rev $2)     }
  | IF LPAREN expr RPAREN stmt ELSE stmt                  { If($3, $5, $7)         }
  | FOR LPAREN NODE ID IN ID RPAREN stmt                  { NodeFor($4, $6, $8)    }
  | FOR LPAREN EDGE ID IN ID RPAREN stmt                  { EdgeFor($4, $6, $8)    }                                 
  | WHILE LPAREN expr RPAREN stmt                         { While($3, $5)          }
  | HATCH expr ID LPAREN args_opt RPAREN stmt %prec HATCH { Hatch($2, $3, $5, $7)  }
  | SYNCH expr LBRACE stmt_list RBRACE                    { Synch($2, List.rev $4) } /* SYNCH ID ... ? */

expr_opt:
    /* nothing */ { Noexpr }
  | expr          { $1 }

expr:
    LITERAL          { Literal($1)                       }
  | FLIT	         { Fliteral($1)                      }
  | BLIT             { BoolLit($1)                       }
  | ID               { Id($1)                            }
  | expr PLUS   expr { Binop($1, Add,   $3)              }
  | expr MINUS  expr { Binop($1, Sub,   $3)              }
  | expr TIMES  expr { Binop($1, Mult,  $3)              }
  | expr DIVIDE expr { Binop($1, Div,   $3)              }
  | expr MODULO expr { Binop($1, Mod,   $3)              }
  | expr EQ     expr { Binop($1, Equal, $3)              }
  | expr LT     expr { Binop($1, Less,  $3)              }
  | expr LEQ    expr { Binop($1, Leq,   $3)              }
  | expr AND    expr { Binop($1, And,   $3)              }
  | expr OR     expr { Binop($1, Or,    $3)              }
  | MINUS expr %prec NOT { Unop(Neg, $2)                 }
  | NOT expr         { Unop(Not, $2)                     }
  | ID ASSIGN expr   { Assign($1, $3)                    }
  | ID LPAREN args_opt RPAREN { Call($1, $3)             }
  | ID LBRACK ID RBRACK { Access($1, $3)                 }
  | ID LBRACK ID RBRACK ASSIGN expr { Insert($1, $3, $6) }
  | LPAREN expr RPAREN { $2                              }

args_opt:
    /* nothing */ { [] }
  | args_list  { List.rev $1 }

args_list:
    expr                    { [$1] }
  | args_list COMMA expr { $3 :: $1 }
