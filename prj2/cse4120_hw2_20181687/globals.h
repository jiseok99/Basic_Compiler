
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
#include "tiny.tab.h"
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */
char file_name[128];

extern int lineno; /* source line number for listing */

typedef enum {
    Error_k,

    Variable_Declaration,
    Array_Declaration,
    Function_Declaration,

    Compound_Statement,
    Expression_Statement,
    Selection_Statement,
    Iteration_Statement,
    Return_Statement,

    Assign_Expression,
    Comparison_Expression,
    Additive_Expression,
    Multiplicative_Expression,

    Variable,
    Array,
    Variable_Parameter,
    Array_Parameter,
    Constant,
    Type,

    Call_Function
} Node_Type;

typedef struct treeNode{
  struct treeNode* sibl;
  int lineno;
  Node_Type node_type;

  union {
      struct { char *ID; };
      struct { int NUM; };
      struct { TokenType token_type; };

      struct {
          struct treeNode *type_specifier;
          struct treeNode *id;
          union {
              struct treeNode *num; 
              struct treeNode *expression_list; 
              struct treeNode *array; 
              struct { 
                  struct treeNode *params;
                  struct treeNode *compound_stmt;
              };
          };
      };

      struct {
          struct treeNode *expression;
          union {
              struct { 
                  struct treeNode *if_stmt;
                  struct treeNode *else_stmt;
              };
              struct treeNode *iteration_stmt; 
              struct treeNode *var; 
          };
      };

      struct {
          struct treeNode *left;
          struct treeNode *operator;
          struct treeNode *right;
      };

      struct {
          struct treeNode *local_declarations;
          struct treeNode *statement_list;
      };
  } tr_node;
} TreeNode;

extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;

extern int Error; 
#endif
