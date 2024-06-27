/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode (1).h"



//Write your code below this line

ExprTreeNode::ExprTreeNode(){


}

ExprTreeNode::ExprTreeNode(string t,int v){
	type = t;
	num = v;
	right = NULL;
	left = NULL;
	

  
}

ExprTreeNode::~ExprTreeNode(){
	type = "";
	left = NULL;
	right = NULL;
	


}

