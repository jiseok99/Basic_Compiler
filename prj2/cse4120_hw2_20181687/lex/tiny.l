
%option noyywrap
%option noinput
%option nounput

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
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
{diginum1} {return ERROR;}
{diginum2} {return ERROR;}

%%

TokenType
getToken(void)
{
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
    {
      firstTime = FALSE;
      lineno++;
      yyin = source;
      yyout = listing;
    }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan)
    {
      fprintf(listing,"\t%d\t\t\t",lineno);
      printToken(currentToken,tokenString);
    }
  return currentToken;
}


