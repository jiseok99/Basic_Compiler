
#ifndef _UTIL_H_
#define _UTIL_H_

TreeNode* Add_Sibling(TreeNode *, TreeNode *);

TreeNode *Variable_Declaration_Node(TreeNode *, TreeNode *);
TreeNode *Array_Declaration_Node(TreeNode *, TreeNode *, TreeNode *);
TreeNode *Function_Declaration_Node(TreeNode *, TreeNode *, TreeNode *, TreeNode *);

TreeNode *Compound_Statement_Node(TreeNode *, TreeNode *);
TreeNode *Expression_Statement_Node(TreeNode *);
TreeNode *Selection_Statement_Node(TreeNode *, TreeNode *, TreeNode *);
TreeNode *Iteration_Statement_Node(TreeNode *, TreeNode *);
TreeNode *Return_Statement_Node(TreeNode *);

TreeNode *Assign_Expression_Node(TreeNode *, TreeNode *);
TreeNode *Comparison_Expression_Node(TreeNode *, TreeNode *, TreeNode *);
TreeNode *Additive_Expression_Node(TreeNode *, TreeNode *, TreeNode *);
TreeNode *Multiplicative_Expression_Node(TreeNode *, TreeNode *, TreeNode *);

TreeNode *Variable_Node(char *);
TreeNode *Array_Node(TreeNode *, TreeNode *);
TreeNode *Variable_Parameter_Node(TreeNode *, TreeNode *);
TreeNode *Array_Parameter_Node(TreeNode *, TreeNode *);
TreeNode *Constant_Node(char *);
TreeNode *Token_Type_Node(TokenType);

TreeNode *Function_Call_Node(TreeNode *, TreeNode *);

void printToken(TokenType, const char*);

char * copyString(char*);

void printTree(TreeNode*);

#endif
