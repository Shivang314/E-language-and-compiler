/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser (1).h"
////#include <iostream>

int order(string ch){
	if (ch == "/" || ch == "*")
		return 2;
	else if (ch == "+" || ch == "-")
		return 1;
	else
		return -1;
}

vector<string> InfixToPost(vector<string> v){
	vector<string> stack;
	vector<string> ans;
	ans.push_back(v[0]);
	ans.push_back(v[1]);
	for(int i=2;i<v.size();i++){
		string ch = v[i];
		//cout<<ch<<" token"<<endl;
		if ((ch!="(")&&(ch!=")")&&(ch!="*")&&(ch!="/")&&(ch!="+")&&(ch!="-")){
			ans.push_back(ch);
			
		}
		else if(ch=="("){
			stack.push_back(ch);
		}
		else if (ch == ")"){
			
			while(stack[stack.size()-1]!="("){
				ans.push_back(stack[stack.size()-1]);
				stack.pop_back();
				

			}
			stack.pop_back();
		}
		else{
			while((stack.size()!=0)&&(order(ch)<=order(stack[stack.size()-1])   )   ){
				ans.push_back(stack[stack.size()-1]);
				stack.pop_back();
			}
			stack.push_back(ch);
		}
	}

	while(stack.size()!=0){
		ans.push_back(stack[stack.size()-1]);
		stack.pop_back();

	}


	return ans;
}




Parser::Parser(){
	//cout<<"created "<<endl;
	symtable = new SymbolTable();
	last_deleted=-1;
}

void Parser::parse(vector<string> expression){
	//cout<<"inside parse"<<endl;
	
	vector<ExprTreeNode* > st;
	ExprTreeNode* root = new ExprTreeNode(":=",-10);


	//delete statement
	if(expression[0]=="del"){
		ExprTreeNode* d = new ExprTreeNode("DEL",-100);
		root->left= d;
		ExprTreeNode* vari = new ExprTreeNode("VAR",-21);
		vari->id = expression[2];
		root->right =vari;
		expr_trees.push_back(root);
		last_deleted = symtable->search(root->right->id);
		symtable->remove(root->right->id);



		return;


	}

	//return statement
	else if(expression[0]=="ret"){
		ExprTreeNode* retu = new ExprTreeNode("RET",-100);
		root->left= retu;
		vector<string> post = InfixToPost(expression);

		string x ;
		for(int i=2;i<post.size();i++){
			x = post[i];
			if((x!="+")&&(x!="/")&&(x!="-")&&(x!="*")){
				if(x[0]=='-'){
					//means negative number
					int z = stoi(x);
					ExprTreeNode* q = new ExprTreeNode("VAL",z);
					st.push_back(q);


				}
				else{
					int u=0;
					for(auto q:x){
						if(!isdigit(q)){
							u=1;
							break;
						}

					}
					if(u==1){
						//means variable
						ExprTreeNode* q = new ExprTreeNode("VAR",-21);
						q->id = x;
						st.push_back(q);

					}
					else{
						int z = stoi(x);
						ExprTreeNode* q = new ExprTreeNode("VAL",z);
						st.push_back(q);



					}
				}


			}
			else{
				if(x=="+"){
					ExprTreeNode* op = new ExprTreeNode("ADD",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);

				}
				else if(x=="-"){
					ExprTreeNode* op = new ExprTreeNode("SUB",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else if(x=="*"){
					ExprTreeNode* op = new ExprTreeNode("MUL",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else if(x=="/"){
					ExprTreeNode* op = new ExprTreeNode("DIV",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else{

				}


			}

		}

		root->right = st[0];
		st.pop_back();
		expr_trees.push_back(root);
		return;


	}


	//normal assign statement
	else{
		
		vector<string> post = InfixToPost(expression);
		
		
		ExprTreeNode* v = new ExprTreeNode("VAR",-20);
		
		v->id = post[0];
		
		root->left = v;
		string x ;

		for(int i=2;i<post.size();i++){
			x = post[i];
			
			if((x!="+")&&(x!="/")&&(x!="-")&&(x!="*")){
				if(x[0]=='-'){
					//means negative number
					int z = stoi(x);
					ExprTreeNode* q = new ExprTreeNode("VAL",z);
					st.push_back(q);


				}
				else{
					int u=0;
					for(auto q:x){
						if(!isdigit(q)){
							u=1;
							break;
						}

					}
					if(u==1){
						//means variable
						ExprTreeNode* q = new ExprTreeNode("VAR",-21);
						q->id = x;
						st.push_back(q);

					}
					else{

						int z = stoi(x);
						ExprTreeNode* q = new ExprTreeNode("VAL",z);
						st.push_back(q);



					}
				}


			}
			else{
				if(x=="+"){

					ExprTreeNode* op = new ExprTreeNode("ADD",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);

				}
				else if(x=="-"){
					ExprTreeNode* op = new ExprTreeNode("SUB",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else if(x=="*"){
					ExprTreeNode* op = new ExprTreeNode("MUL",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else if(x=="/"){
					ExprTreeNode* op = new ExprTreeNode("DIV",-1);
					op->right = st[st.size()-1];
					op->left = st[st.size()-2];
					st.pop_back();
					st.pop_back();
					st.push_back(op);
				}
				else{

				}


			}

		}

		root->right = st[0];

		st.pop_back();

		expr_trees.push_back(root);


		if(symtable->search(root->left->id)==-2){
			symtable->insert(root->left->id);
		}
		//cout<<"now"<<endl;
		return;




	}
}

Parser::~Parser(){
	expr_trees.clear();
	delete symtable;
}

