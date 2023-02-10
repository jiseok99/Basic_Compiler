
%{
#define YYPARSER 

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *

static TreeNode * savedTree;

static int yylex(void);
int yyerror(char*);
%}

%token ID NUM ELSE IF INT RETURN VOID WHILE
%token PLUS MINUS TIMES OVER LT LTE GT GTE EQ NEQ
%token ASSIGN SEMI COMMA LPAREN RPAREN LBRAC RBRAC LCURLY RCURLY
%token ENDFILE ERROR COMMENT_ERROR

%start program

%%
id : ID { $$ = Variable_Node(tokenString); };
num : NUM { $$ = Constant_Node(tokenString); };

program : declaration-list { savedTree = $1; };

declaration-list
        : declaration-list declaration
          { $$ = Add_Sibling($1, $2); }
        | declaration
          { $$ = $1; };

declaration : var-declaration { $$ = $1; }
        | fun-declaration { $$ = $1; };

var-declaration : type-specifier id SEMI { $$ = Variable_Declaration_Node($1, $2); }
        | type-specifier id LBRAC num RBRAC SEMI { $$ = Array_Declaration_Node($1, $2, $4); };

type-specifier : INT { $$ = Token_Type_Node(INT); }
        | VOID { $$ = Token_Type_Node(VOID); };

fun-declaration : type-specifier id LPAREN params RPAREN compound-stmt { $$ = Function_Declaration_Node($1, $2, $4, $6); };

params : param-list { $$ = $1; }
        | VOID { $$ = NULL; };

param-list : param-list COMMA param { $$ = Add_Sibling($1, $3); }
        | param { $$ = $1; };

param : type-specifier id { $$ = Variable_Parameter_Node($1, $2); }
        | type-specifier id LBRAC RBRAC { $$ = Array_Parameter_Node($1, $2); };

compound-stmt : LCURLY local-declarations statement-list RCURLY { $$ = Compound_Statement_Node($2, $3); };

local-declarations : local-declarations var-declaration { $$ = Add_Sibling($1, $2); }
        |    { $$ = NULL; };

statement-list : statement-list statement { $$ = Add_Sibling($1, $2); }
        |    { $$ = NULL; };

statement : expression-stmt { $$ = $1; }
        | compound-stmt { $$ = $1; }
        | selection-stmt { $$ = $1; }
        | iteration-stmt { $$ = $1; }
        | return-stmt { $$ = $1; };

expression-stmt : expression SEMI { $$ = Expression_Statement_Node($1); }
        | SEMI { $$ = NULL; };

selection-stmt : IF LPAREN expression RPAREN statement { $$ = Selection_Statement_Node($3, $5, NULL); }
        | IF LPAREN expression RPAREN statement ELSE statement { $$ = Selection_Statement_Node($3, $5, $7); };

iteration-stmt : WHILE LPAREN expression RPAREN statement { $$ = Iteration_Statement_Node($3, $5); };

return-stmt : RETURN SEMI { $$ = Return_Statement_Node(NULL); }
        | RETURN expression SEMI { $$ = Return_Statement_Node($2); };

expression : var ASSIGN expression { $$ = Assign_Expression_Node($1, $3); }
        | simple_expression { $$ = $1; };

var : id { $$ = $1; }
        | id LBRAC expression RBRAC { $$ = Array_Node($1, $3); };

simple_expression : additive_expression relop additive_expression { $$ = Comparison_Expression_Node($1, $2, $3); }
        | additive_expression { $$ = $1; };

relop : LT { $$ = Token_Type_Node(LT); }
        | LTE { $$ = Token_Type_Node(LTE); }
        | GT { $$ = Token_Type_Node(GT); }
        | GTE { $$ = Token_Type_Node(GTE); }
        | EQ { $$ = Token_Type_Node(EQ); }
        | NEQ { $$ = Token_Type_Node(NEQ); };

additive_expression : additive_expression addop term { $$ = Additive_Expression_Node($1, $2, $3); }
        | term { $$ = $1; };

addop : PLUS { $$ = Token_Type_Node(PLUS); }
        | MINUS { $$ = Token_Type_Node(MINUS); };

term : term mulop factor { $$ = Multiplicative_Expression_Node($1, $2, $3); }
        | factor { $$ = $1; };

mulop : TIMES { $$ = Token_Type_Node(TIMES); }
        | OVER { $$ = Token_Type_Node(OVER); };

factor : LPAREN expression RPAREN { $$ = $2; }
        | var { $$ = $1; }
        | call { $$ = $1; }
        | num { $$ = $1; };

call : id LPAREN args RPAREN { $$ = Function_Call_Node($1, $3); };

args : arg-list { $$ = $1; }
        | { $$ = NULL; };

arg-list : arg-list COMMA expression { $$ = Add_Sibling($1, $3); }
        | expression { $$ = $1; };
%%

int yyerror(char * message){ 
  fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");

  printToken(yychar,tokenString);
  Error = TRUE;
  fclose(listing);

  return 0;
}

static int yylex(void){ 
  listing = fopen(file_name, "a");
  TokenType tk = getToken();

  if (tk == ENDFILE) return 0;

  if (tk == ERROR){
      fprintf(listing,"Lexical analyze error at line %d\n",lineno);
      fprintf(listing,"Current token: %s",tokenString);

      Error = TRUE;
      return 0;
  }

  return tk;
}

TreeNode * parse(void){ 
  yyparse();
  return savedTree;
}