/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"


/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

TokenType tokenize(void);

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".tny");
  source = fopen(pgm,"r");
  
  if (source==NULL){ 
    fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }

  char file_name[128];
  char* text;
  char* append = "_20181687.txt";
  strcpy(file_name, argv[1]);

  strtok(file_name, ".");
  strcat(file_name, append);

  listing = fopen(file_name, "w");

  if (TraceScan){
      fprintf(listing,"line number\t\ttoken\t\t\tlexeme\n");
      fprintf(listing,"-----------------------------------------------------\n");
    }
    
  while (tokenize() != ENDFILE){
    if(tokenize() == ENDFILE)
      break;
  }

  fclose(source);
  return 0;
}

