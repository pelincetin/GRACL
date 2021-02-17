%{
 (* 
 program: program vardec | program fundec | program statement| ε
fundec: type id( params ) { statements }
params:  param | param ,  params | ε (* possibly change to params , param *)
param: type id
vardec: type id ; | type id = expression ;
args: expression | args , expression | ε
statements: statement statements | ε
statement: expression ; | return expression ; 
| if ( expression ) { statements } else { statements } | while ( expression ) { statements } 
| for ( type id in id ) { statements } | vardec
expression: lit | id | ( expression ) | expression + expression | expression - expression | expression * expression | expression / expression | expression % expression | expression == expression | id = expression | expression || expression | 
expression && expression | expression < expression | expression <= expression | expression + expression | - expression | ! expression | 
id.id( something )
*)
%}

%token PLUS MINUS TIMES DIVIDE ASSIGN EOF LPAREN RPAREN LBRACE RBRACE SEMICOLON RETURN IF ELSE WHILE FOR IN 
%token MOD EQUALS OR AND LESS LTEQ NOT NEG DOT COMMA
%token <int> LITERAL
%token <string> ID
%token <string> TYPE

%right ASSIGN
%left OR
%left AND 
%left EQUALS
%left LESS LTEQ
%left PLUS MINUS
%left TIMES DIVIDE MOD
%right NOT NEG
%left DOT LPAREN RPAREN LBRACE RBRACE (* Is this right for parens and braces? *)

%start program
%type <unit> program

%%
program: 
  program vardec 
| program fundec
| program statement
| 

params: 
  param
| params COMMA param
|

param:
  TYPE ID

fundec: 
  TYPE ID LPAREN params RPAREN LBRACE statements RBRACE

vardec: 
  TYPE ID SEMICOLON
| TYPE ID ASSIGN expression SEMICOLON

statements:
  statement statements
|

statement:
  expression SEMICOLON
| RETURN expression SEMICOLON
| IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
| WHILE LPAREN expression RPAREN LBRACE statements RBRACE
| FOR LPAREN TYPE ID IN ID RPAREN LBRACE statements RBRACE
| vardec

args:
  expression
| args COMMA expression
| 

expression:
  expression PLUS   expression 		{ Binop($1, Add, $3) }
| expression MINUS  expression 		{ Binop($1, Sub, $3) }
| expression TIMES  expression 		{ Binop($1, Mul, $3) }
| expression DIVIDE expression 		{ Binop($1, Div, $3) }
| LITERAL          		{ Lit($1) }
| ID         		{ Var($1) }
| ID ASSIGN expression 	{ Assgn($1, $3) }
| LPAREN expression RPAREN
| expression MOD expression
| expression EQUALS expression
| expression OR expression
| expression AND expression
| expression LESS expression
| expression LTEQ expression
| MINUS expression %prec NEG 
| NOT expression
| ID DOT ID LPAREN params RPAREN