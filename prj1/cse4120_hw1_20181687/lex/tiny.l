/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "stdio.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
%}

%x COM

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+
diginum1 [a-zA-Z]*[0-9]*[a-zA-Z]*
diginum2 [0-9]*[a-zA-Z]*[0-9]*
%%

"/*"            { BEGIN(COM); }
<COM>"*/"       { BEGIN(INITIAL); }
<COM>.          { /* skip comments */ }
<COM>{newline}  { lineno++; }
<COM><<EOF>>    { BEGIN(INITIAL); return COMMENT_ERROR; }
"*/"            { return COMMENT_ERROR; }
<<EOF>>         { return ENDFILE; }

"if"            { return IF; }
"else"          { return ELSE; }
"int"           { return INT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }
"=="            { return EQ; }
"="             { return ASSIGN; }
"!="            { return NEQ; }
"<"             { return LT; }
"<="            { return LTE; }
">"             { return GT; }
">="            { return GTE; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return OVER; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRAC; }
"]"             { return RBRAC; }
"{"             { return LCURLY; }
"}"             { return RCURLY; }
","             { return COMMA; }
";"             { return SEMI; }

{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
.               { return ERROR; }
{diginum1} {return ERROR;}
{diginum2} {return ERROR;}
%%

TokenType tokenize(void)
{ 
  char Tokens[MAXTOKENLEN+1];
  static int first = TRUE;

  if (first){ 
    first = FALSE;
    lineno+=1;
    yyin = source;
    yyout = listing;
  }

  TokenType current = yylex();
  strncpy(Tokens,yytext,MAXTOKENLEN+1);

  if (TraceScan) {
    fprintf(listing,"\t%d",lineno);
    printToken(current,Tokens);
  }

  return current;
}

int yywrap()
{
      
}
