
#include "globals.h"
#include "util.h"

void printToken( TokenType token, const char* tokenString ){ 
  switch (token){ 
    case IF:
      fprintf(listing, "\t\tIF\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case ELSE:
      fprintf(listing, "\t\tELSE\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case INT:
      fprintf(listing, "\t\tINT\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case RETURN:    
      fprintf(listing, "\t\tRETURN\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case VOID:
      fprintf(listing, "\t\tVOID\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case WHILE:   
      fprintf(listing, "\t\tWHILE\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case ASSIGN: 
      fprintf(listing, "\t\t=\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case LT: 
      fprintf(listing, "\t\t<\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case LTE:
      fprintf(listing, "\t\t<=\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case GT:
      fprintf(listing, "\t\t>\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case GTE:
      fprintf(listing, "\t\t>=\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case EQ: 
      fprintf(listing, "\t\t==\t\t");
      fprintf(listing, "\t%s\n", tokenString); 
      break;  
    case NEQ:
      fprintf(listing, "\t\t!=\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case LPAREN: 
      fprintf(listing, "\t\t(\t\t");
      fprintf(listing, "\t%s\n", tokenString); 
      break;  
    case RPAREN: 
      fprintf(listing, "\t\t)\t\t");
      fprintf(listing, "\t%s\n", tokenString); 
      break;  
    case SEMI:
      fprintf(listing, "\t\t;\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case LBRAC: 
      fprintf(listing, "\t\t[\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case RBRAC:
      fprintf(listing, "\t\t]\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case LCURLY:
      fprintf(listing, "\t\t{\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case RCURLY:
      fprintf(listing, "\t\t}\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case COMMA:
      fprintf(listing, "\t\t,\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case PLUS: 
      fprintf(listing, "\t\t+\t\t");
      fprintf(listing, "\t%s\n", tokenString); 
      break; 
    case MINUS:
      fprintf(listing, "\t\t-\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;   
    case TIMES:
      fprintf(listing, "\t\t*\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case OVER:
      fprintf(listing, "\t\t/\t\t");
      fprintf(listing, "\t%s\n", tokenString);  
      break; 
    case ENDFILE:
      fprintf(listing, "\t\tEOF\t\t");
      fprintf(listing, "\t%s\n", tokenString); 
      break;    
    case NUM:
      fprintf(listing, "\t\tNUM\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break; 
    case ID:
      fprintf(listing, "\t\tID\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break; 
    case ERROR:
      fprintf(listing, "\t\tERROR\t\t");
      fprintf(listing, "\t%s\n", tokenString);
      break;
    case COMMENT_ERROR:
      fprintf(listing, "\t\tERROR\t\tComment Error\n");
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

TreeNode* Add_Sibling(TreeNode *first, TreeNode *next){
  if (first == NULL) 
    first = next;
  
  else{
    TreeNode *t = first;
    
    while (t->sibl != NULL) 
      t = t->sibl;

    t->sibl = next;
  }
    
  return first;
}

TreeNode* Variable_Declaration_Node(TreeNode *type_specifier, TreeNode *id){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Variable_Declaration;
      tree->tr_node.type_specifier = type_specifier;
      tree->tr_node.id = id;
    }

  return tree;
}

TreeNode* Array_Declaration_Node(TreeNode *type_specifier, TreeNode *id, TreeNode *num){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Array_Declaration;
      tree->tr_node.type_specifier = type_specifier;
      tree->tr_node.id = id;
      tree->tr_node.num = num;
    }

  return tree;
}

TreeNode* Function_Declaration_Node(TreeNode *type_specifier, TreeNode *id, TreeNode *params, TreeNode *compound_stmt){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Function_Declaration;
      tree->tr_node.type_specifier = type_specifier;
      tree->tr_node.id = id;
      tree->tr_node.params = params;
      tree->tr_node.compound_stmt = compound_stmt;
    }

  return tree;
}

TreeNode* Compound_Statement_Node(TreeNode *local_declarations, TreeNode *statement_list){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Compound_Statement;
      tree->tr_node.local_declarations = local_declarations;
      tree->tr_node.statement_list = statement_list;
    }

  return tree;
}

TreeNode* Expression_Statement_Node(TreeNode *expression) {
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Expression_Statement;
      tree->tr_node.expression = expression;
    }

  return tree;
}

TreeNode* Selection_Statement_Node(TreeNode *expression, TreeNode *if_stmt, TreeNode *else_stmt) {
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Selection_Statement;
      tree->tr_node.expression = expression;
      tree->tr_node.if_stmt = if_stmt;
      tree->tr_node.else_stmt = else_stmt;
    }

  return tree;
}

TreeNode* Iteration_Statement_Node(TreeNode *expression, TreeNode *statement) {
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Iteration_Statement;
      tree->tr_node.expression = expression;
      tree->tr_node.iteration_stmt = statement;
    }

  return tree;
}

TreeNode* Return_Statement_Node(TreeNode *expression) {
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Return_Statement;
      tree->tr_node.expression = expression;
    }

  return tree;
}

TreeNode* Assign_Expression_Node(TreeNode *var, TreeNode *expression){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Assign_Expression;
      tree->tr_node.var = var;
      tree->tr_node.expression = expression;
    }

  return tree;
}

TreeNode* Comparison_Expression_Node(TreeNode *left, TreeNode *relop, TreeNode *right){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Comparison_Expression;
      tree->tr_node.left = left;
      tree->tr_node.operator = relop;
      tree->tr_node.right = right;
    }

  return tree;
}

TreeNode* Additive_Expression_Node(TreeNode *left, TreeNode *addop, TreeNode *right){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Additive_Expression;
      tree->tr_node.left = left;
      tree->tr_node.operator = addop;
      tree->tr_node.right = right;
    }

  return tree;
}

TreeNode* Multiplicative_Expression_Node(TreeNode *left, TreeNode *mulop, TreeNode *right){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Multiplicative_Expression;
      tree->tr_node.left = left;
      tree->tr_node.operator = mulop;
      tree->tr_node.right = right;
    }

  return tree;
}

TreeNode * Variable_Node(char *ID){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Variable;
      tree->tr_node.ID = copyString(ID);
    }
  return tree;
}

TreeNode * Array_Node(TreeNode *id, TreeNode *expression){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Array;
      tree->tr_node.id = id;
      tree->tr_node.array = expression;
    }

  return tree;
}

TreeNode* Variable_Parameter_Node(TreeNode *type_specifier, TreeNode *id){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Variable_Parameter;
      tree->tr_node.type_specifier = type_specifier;
      tree->tr_node.id = id;
    }

  return tree;
}

TreeNode* Array_Parameter_Node(TreeNode *type_specifier, TreeNode *id){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Array_Parameter;
      tree->tr_node.type_specifier = type_specifier;
      tree->tr_node.id = id;
    }

  return tree;
}

TreeNode * Constant_Node(char *NUM){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Constant;
      int n = atoi(NUM);
      tree->tr_node.NUM = n;
    }

  return tree;
}

TreeNode * Token_Type_Node(TokenType token){
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Type;
      tree->tr_node.token_type = token;
    }

  return tree;
}

TreeNode* Function_Call_Node(TreeNode *id, TreeNode *args) {
  TreeNode * tree = (TreeNode *) malloc(sizeof(TreeNode));

  if (tree == NULL)
      fprintf(listing,"Out of memory error at line %d\n",lineno);

  if (tree != NULL){
      tree->sibl = NULL;
      tree->lineno = lineno;
      tree->node_type = Call_Function;
      tree->tr_node.id = id;
      tree->tr_node.expression_list = args;
    }

  return tree;
}

char*
copyString(char * str){
  if (str == NULL) 
    return NULL;

  char * temp = malloc(strlen(str) + 1);

  if (temp == NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
    
  else 
    strcpy(temp, str);
    
  return temp;
}

static int space = 0;

static void printSpaces(void){
  int i;
  for (i=0; i<space; i++) 
    fprintf(listing," ");
}

static const char * Token_Type(TokenType operator){
  if(operator == INT) return "int";
  else if(operator == VOID) return "void";
  else if(operator == PLUS) return "+";
  else if(operator == MINUS) return "-";
  else if(operator == TIMES) return "*";
  else if(operator == OVER) return "/";
  else if(operator == LT) return "<";
  else if(operator == LTE) return "<=";
  else if(operator == GT) return ">";
  else if(operator == GTE) return ">=";
  else if(operator == EQ) return "==";
  else if(operator == NEQ) return "!=";

  return 0;
}

int v_c = 0;
int a_c = 0;
int f_c = 0;
int v_p = 0;
int a_p = 0;
int f_n = 0;

void printTree(TreeNode* tree){
  space+=2;
  while (tree != NULL){
      switch (tree->node_type){
        case Error_k:
          printSpaces();
          fprintf(listing, "There is an error in Tree\n");
          break;

        case Variable_Declaration:
          v_c = 1;
          printTree(tree->tr_node.id);
          printSpaces();
         fprintf(listing, "   ");
          fprintf(listing, "  Type : ");
          printTree(tree->tr_node.type_specifier);
          break;

        case Array_Declaration:
          a_c = 1;
          printTree(tree->tr_node.id);
          printSpaces();
          printSpaces();
          fprintf(listing, "  Type : ");
          printTree(tree->tr_node.type_specifier);
          printSpaces();
          printTree(tree->tr_node.num);
          break;

        case Function_Declaration:
          f_c = 1;
          printTree(tree->tr_node.id);
          printSpaces();
          printSpaces();
          fprintf(listing, "  Type : ");
          printTree(tree->tr_node.type_specifier);
          printTree(tree->tr_node.params);
          printTree(tree->tr_node.compound_stmt);
          break;

        case Compound_Statement:
          printSpaces();
          fprintf(listing, "  Compound Statement\n");
          printTree(tree->tr_node.local_declarations);
          printTree(tree->tr_node.statement_list);
          break;

        case Expression_Statement:
          printTree(tree->tr_node.expression);
          break;

        case Selection_Statement:
            printSpaces();
            fprintf(listing, "  If\n");
            printTree(tree->tr_node.expression);
            printTree(tree->tr_node.if_stmt);
            printTree(tree->tr_node.else_stmt);
          break;

        case Iteration_Statement:
          printSpaces();
          fprintf(listing, "  While\n");
          printTree(tree->tr_node.expression);
          printTree(tree->tr_node.iteration_stmt);
          break;

        case Return_Statement:
          printSpaces();
          fprintf(listing, "  Return Statement\n");
          fprintf(listing, "  ");
          printTree(tree->tr_node.expression);
          break;

        case Assign_Expression:
          printSpaces();
          fprintf(listing, "Assign : =\n");
          printTree(tree->tr_node.var);
          printTree(tree->tr_node.expression);
          break;

        case Comparison_Expression:
          printSpaces();
          fprintf(listing, "  Simple Expression\n");
          fprintf(listing, "  ");
          printTree(tree->tr_node.left);
          printSpaces();
          fprintf(listing, "  ");
          fprintf(listing, "  Operator : ");
          printTree(tree->tr_node.operator);
          fprintf(listing, "  ");
          printTree(tree->tr_node.right);
          break;

        case Additive_Expression:
          printSpaces();
          fprintf(listing, "Additive Expression\n");
          printTree(tree->tr_node.left);
          printSpaces();
          fprintf(listing, "  Operator : ");
          printTree(tree->tr_node.operator);
          printTree(tree->tr_node.right);
          break;

        case Multiplicative_Expression:
          printSpaces();
          fprintf(listing, "Multiplicative Expression\n");
          printTree(tree->tr_node.left);
          printSpaces();
          fprintf(listing, "  Operator : ");
          printTree(tree->tr_node.operator);
          printTree(tree->tr_node.right);
          break;

        case Variable:
          printSpaces();
          if(v_c == 1)
            fprintf(listing, "Variable Declare : %s\n", tree->tr_node.ID);
          else if(a_c == 1)
            fprintf(listing, "Array Declare : %s\n", tree->tr_node.ID);
          else if (f_c == 1)
            fprintf(listing, "Function Declare : %s\n", tree->tr_node.ID);
          else if (v_p == 1)
            fprintf(listing, "Parameter : %s\n", tree->tr_node.ID);
          else if (a_p == 1)
            fprintf(listing, "Parameter(Array) : %s\n", tree->tr_node.ID);
          else if(f_n == 1)
            fprintf(listing, "Function Name : %s\n", tree->tr_node.ID);
          else
            fprintf(listing, "Variable : %s\n", tree->tr_node.ID);

          v_c = 0;
          a_c = 0;
          f_c = 0;
          v_p = 0;
          a_p = 0;
          f_n = 0;
          break;

        case Array:
          printSpaces();
          fprintf(listing, "Array Variable\n");
          printTree(tree->tr_node.id);
          fprintf(listing, "  ");
          printTree(tree->tr_node.array);
          break;

        case Variable_Parameter:
          v_p = 1;
          printTree(tree->tr_node.id);
          printSpaces();
          printSpaces();
          fprintf(listing, "Type : ");
          printTree(tree->tr_node.type_specifier);
          break;

        case Array_Parameter:
          a_p = 1;
          printTree(tree->tr_node.id);
          printSpaces();
          printSpaces();
          fprintf(listing, "Type : ");
          printTree(tree->tr_node.type_specifier);
          break;

        case Constant:
          printSpaces();
          fprintf(listing, "Constant : %d\n", tree->tr_node.NUM);
          break;

        case Type:
          fprintf(listing, "%s\n", Token_Type(tree->tr_node.token_type));
          break;

        case Call_Function:
          f_n = 1;
          printSpaces();
          fprintf(listing, "Function Call\n");
          printTree(tree->tr_node.id);
          printTree(tree->tr_node.expression_list);
          break;

        default:
          printSpaces();
          fprintf(listing, "No such node\n");
        }
      tree = tree->sibl;
    }
  space-=2;
}