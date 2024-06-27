 /* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode (1).h"

//Write your code below this line

int geth(SymNode* node){
	if(node==NULL){
		return -1;
	}
	else{
		return node->height;
	}
}

SymNode::SymNode(){
	key = "";
	par = NULL;
	left = NULL;
	right = NULL;
	address = -1;
	height = 0;
}

SymNode::SymNode(string k){
	key = k;
	par = NULL;
	left = NULL;
	right = NULL;
	address = -1;
	height = 0;
}

SymNode* SymNode::LeftLeftRotation(){
    if(this->left->right!=NULL){                             
        this->left->right->par = this;
    }
    this->left->par = this->par;
    this->par = this->left;
    /*SymNode* temp = new SymNode;
    temp = this->left;*/
    this->left = this->left->right;
    this->par->right = this;
    this->height = max(geth(this->left), geth(this->right)) + 1;
    this->par->height = max(geth(this->par->left), geth(this->par->right)) + 1;
    return this->par;
}

SymNode* SymNode::RightRightRotation(){
	if(this->right->left!=NULL){                             
        this->right->left->par = this;
    }
    this->right->par = this->par;
    this->par = this->right;
    /*SymNode* temp = new SymNode;
    temp = this->right;*/
    this->right = this->right->left;
    this->par->left = this;
    this->height = max(geth(this->left), geth(this->right)) + 1;
    this->par->height = max(geth(this->par->left), geth(this->par->right)) + 1;
    return this->par;
}

SymNode* SymNode::LeftRightRotation(){
	this->left = this->left->RightRightRotation();
	return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
	this->right =this->right->LeftLeftRotation();
	return this->RightRightRotation();
}

SymNode::~SymNode(){
	key = "";
	SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;
}


