/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable (1).h"

/*void deb(SymNode* t){
	if(t==NULL){
        return;
    }
    else{
        cout<<"root "<<t->key;
        if(t->left!=NULL){
            cout<<" left child "<<t->left->key;
        }
        if(t->right!=NULL){
            cout<<" right child "<<t->right->key;
        }
        cout<<endl;
        deb(t->left);
        deb(t->right);

    }
}*/

/*void heightprint(SymNode* n){
	if(n==NULL){
		return;
	}
	else{
	cout<<"height of "<<n->key<<"is "<<n->height<<endl;
	heightprint(n->left);
	heightprint(n->right);

	
}
}*/

int getheight(SymNode* node){
	if(node==NULL){
		return -1;
	}
	else{
		return node->height;
	}
}

SymNode* succ(SymNode* node){
	SymNode* temp = node->right;
	
	while(temp->left!=NULL){
		
		temp = temp->left;
	}
	return temp;
}

void annihilator(SymNode* r){
	if(r==NULL){
		return;
	}
	else{
		annihilator(r->right);
		annihilator(r->left);
		delete r;
	}
}

SymbolTable::SymbolTable(){
}

void SymbolTable::insert(string k){
	/*cout<<"heights before insert of "<<k<<endl;
	heightprint(root);*/
	
	SymNode* r = root;
	SymNode* parent = r;
	//check if root is null
	if(root==NULL){
	   	
		root = new SymNode(k);
		root->height=0;
		size=1;
		return;
	}

	//find location
	else{
		while((r!=NULL)){
			
			
			if(r->key>k){
				
				parent = r;
				
				r = r->left;
			}
			else{
			
				parent = r;

				r = r->right;
				
			}
		
		}

	}

	
	r =  new SymNode(k);
	
	if(parent->key>r->key){
		parent->left = r;
		r->par = parent;
		
	}
	else{
		parent->right = r;
		r->par = parent;
	}

	size++;
	
	
	
	//height_update


	while(parent!=NULL){
		
		
		parent->height = max(getheight(parent->left),getheight(parent->right)) +1;
		
		
		parent = parent->par;
	}
	//cout<<"updated heights after INSERT of "<<k<<endl;
	//heightprint(root);
	//rotations
	SymNode* temp = r;



	//go up while tree is balanced
	while(  (temp->par->par!=NULL) && ( (  ( getheight(temp->par->par->left) )-(getheight(temp->par->par->right))<=1 )&& (  (getheight(temp->par->par->left))-(getheight(temp->par->par->right))>=-1 ) ) ){
		/*cout<<"balanced at "<<temp->par->par->key<<" for insert of "<<k<<endl;*/
		temp = temp->par;

	}
    

	//reached root and no imblancing present
	if(temp->par->par == NULL){
	   
	    
		return;
	}

	//balance tree at imbalance and then update height then done.
	else{

		
	   	//LEFTLEFT
		if((temp->par->par->left!=NULL)&&(temp->par->par->left->left == temp)){
			if(temp->par->par!=root){
				
				
				SymNode* p = temp->par->par->LeftLeftRotation();
				if(p->par->left==p->right){
					p->par->left=p;
				}
				else{
					p->par->right=p;
				}

				//height update
				while(p!=NULL){
					p->height = max(getheight(p->left),getheight(p->right))+1;
					p = p->par;
				}
			}
			else{

				/*temp->par->right=temp->par->par;
                temp->par->par=NULL;
                temp->par->right->par=temp->par;
                temp->par->right->left=NULL;
                root = temp->par;
                root->height = max(getheight(root->right),getheight(root->left))+1;*/

                if(temp->par->right!=NULL){
                	temp->par->right->par  = temp->par->par;
                }
                temp->par->par->left=temp->par->right;
                temp->par->right = temp->par->par;
                temp->par->right->par= temp->par;
                temp->par->par = NULL;
                root = temp->par;
                root->right->height = max(getheight(root->right->left),getheight(root->right->right))+1;
                root->height = max(getheight(root->right),getheight(root->left))+1;
                
				
			}
		       
		       	
				
		}

		//RIGHTRIGHT
		else if((temp->par->par->right!=NULL)&&(temp->par->par->right->right == temp)){
			if(temp->par->par==root){
				

				if(temp->par->left!=NULL){
                	temp->par->left->par  = temp->par->par;
                }
                temp->par->par->right=temp->par->left;
                temp->par->left = temp->par->par;
                temp->par->left->par= temp->par;
                temp->par->par = NULL;
                root = temp->par;
                root->left->height = max(getheight(root->left->right),getheight(root->left->left))+1;
                root->height = max(getheight(root->right),getheight(root->left))+1;
                
                
            }
            else{
                SymNode*p = temp->par->par->RightRightRotation();
                if(p->par->left==p->left){
                	p->par->left=p;
                }
                else{
                	p->par->right = p;
                }
                //height update
                while(p!=NULL){
					p->height = max(getheight(p->left),getheight(p->right))+1;
					p = p->par;
				}

                
            }


		}

		//LEFTRIGHT
		else if((temp->par->par->left!=NULL)&&(temp->par->par->left->right==temp)){
			
			if(temp->par->par!=root){
				
				SymNode* t = temp->par->par->LeftRightRotation();
				if(t->par->left==t->right){
					t->par->left = t;
				}
				else{
					t->par->right = t;
				}
				//height update
				while(t!=NULL){
					t->height = max(getheight(t->left),getheight(t->right))+1;
					t=t->par;
				}

			}
			else{
				root =temp->par->par->LeftRightRotation();
				root->height = max(getheight(root->right),getheight(root->left))+1;

			}
	
		}

		//RightLeft
		else{
			
			if(temp->par->par!=root){
				
				SymNode* t = temp->par->par->RightLeftRotation();
				if(t->par->left==t->left){
					t->par->left = t;
				}
				else{
					t->par->right = t;
				}
				//height update
				while(t!=NULL){
					t->height = max(getheight(t->left),getheight(t->right))+1;
					t=t->par;
				}

			}
			else{
				root = temp->par->par->RightLeftRotation();
				root->height = max(getheight(root->right),getheight(root->left))+1;

			}

			
		}


	}

	/* cout<<"updated height aft ins and rot"<<endl;
	heightprint(root); */


	
		
	
	
} 

void SymbolTable::remove(string k){
	/*cout<<" heights bef removal of "<<k<<endl;
	heightprint(root);*/
	
	SymNode* r = root;
	SymNode* parent=r->par;
	//find the node
	while((r!=NULL)&&(r->key!=k)){
		parent = r;
		if(r->key>k){
			r = r->left;
		}
		else{
			r= r->right;
		}
	}
	if(r==NULL){
		return;
	}


	//no child
	if((r->left==NULL)&&(r->right==NULL)){
		/*cout<<"no child case"<<endl;*/
		
		size--;
		parent = r->par;
		SymNode* b = r->par;
		if(r==root){
			
			root=NULL;
			return;
		}

		if(r->par->left==r){
			
			r->par->left = NULL;
			delete r;
		}
		else{
			r->par->right=NULL;
			delete r;
		}
		/*cout<<"root is "<<root->key<<endl;*/
	}

	//two child
	else if((r->left!=NULL)&&(r->right!=NULL)){
		/*cout<<"Two case wala remove"<<endl;*/
		
		parent = r->par;
		SymNode* s = succ(r);
		string x = s->key;
		int addr = s->address;
		/*cout<<"removing succ "<<s->key<<endl;*/
		remove(x);

		r->key = x;
		r->address=addr;
		/*cout<<"root is "<<root->key<<endl;*/
	}

	//one child
	else {
		
		size--;
		if(r==root){
		
			if(r->left!=NULL){
				SymNode* child= r->left;
				child->par = NULL;
				delete r;
				root = child;
			}
			else{
				SymNode* child = r->right;
				child->par = NULL;
				delete r;
				root = child;
			}

		}
		else{
			parent = r->par;

			if((r->par->left==r)&&(r->left!=NULL)){
				r->par->left =r->left;
				r->left->par = r->par;
				delete r;
			}
			else if((r->par->left==r)&&(r->right!=NULL)){
				r->par->left = r->right;
				r->right->par  = r->par;
				delete r;
			}
			else if((r->par->right==r)&&(r->left!=NULL)){
				r->par->right = r->left;
				r->left->par = r->par;
				delete r;
			}
			else{
				r->par->right = r->right;
				r->right->par = r->par;
				delete r;
			}

		}
		

	}

	//update height;

	SymNode* b = parent;
	while(parent!=NULL){
		parent->height= 1+ max(getheight(parent->left),getheight(parent->right));
		
		/*if((parent->left!=NULL)&&(parent->right!=NULL)){
			parent->height = 1 + max(getheight(parent->left), getheight(parent->right));

		}
		else if((parent->left==NULL)&&(parent->right!=NULL)){
			parent->height = 1 + getheight(parent->right);
		}
		else{
			parent->height = 1 + getheight(parent->left);
		}*/

		parent = parent->par;
	}
	/*cout<<"updated heights after removal of "<<k<<endl;
	heightprint(root);
	cout<<"new root after remove of key "<<k<<endl;
	cout<<root->key<<endl;*/
	//check imbalance

	while(b!=NULL){

		if((getheight(b->right)-getheight(b->left)>=-1)&&(getheight(b->right)-getheight(b->left)<=1)){
			
			b = b->par;

		}

		else{
			
			if(getheight(b->left)>getheight(b->right)){
				
				if(getheight(b->left->left)>getheight(b->left->right)){
			
					SymNode* t =b->LeftLeftRotation();
					if(t->par!=NULL){
						if(t->par->right ==b){
							t->par->right =t;
						}
						else{
							t->par->left= t;
						}
					}
					else{
						root = t;
					}

					SymNode* c = t->par;

					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}
					b=t->par;
					//tree may be unbalanced so go up



				}
				
				else if(getheight(b->left->left)<getheight(b->left->right)){
				
					SymNode* t = b->LeftRightRotation();
					if(t->par!=NULL){
						if(t->par->left==b){
							t->par->left =t;
						}
						else{
							t->par->right = t;
						}
					}
					else{
						root =t;
					}
					SymNode* c = t->par;
					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}
					b=t->par;
						//tree may be unbalanced so go up




				}

				else{
					SymNode* t=b->LeftLeftRotation();
					if(t->par!=NULL){
						if(t->par->right==b){
							t->par->right = t;
						}
						else{
							t->par->left = t;
						}
					}
					else{
						root = t;
					}
					SymNode* c= t->par;
					b=t->par;
					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}
					//after this tree will be balanced



				}
			}
			else{
				
				if(getheight(b->right->right)<getheight(b->right->left)){
					
					SymNode* t = b->RightLeftRotation();

					if(t->par!=NULL){
						if(t->par->left==b){
							t->par->left =t;
						}
						else{
							t->par->right = t;
						}
					}
					else{
						
						root = t;
					}
					SymNode* c = t->par;
					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}
					b = t->par;
					//tree may still be unbalanced so while loop will go up


				}
				
				else if(getheight(b->right->right)>getheight(b->right->left)){
					
					SymNode* t =b->RightRightRotation();
					if(t->par!=NULL){
						if(t->par->right ==b){
							t->par->right =t;
						}
						else{
							t->par->left= t;
						}
					}
					else{
						root = t;
					}
					SymNode* c = t->par;

					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}

					b = t->par;
					// after this the tree may be unbalanced so aage jana padega while loop will take care
				}

				else{
				
					SymNode* t = b->RightRightRotation();
					
					if(t->par!=NULL){
						if(t->par->right==b){
							t->par->right = t;
						}
						else{
							t->par->left = t;
						}
					}
					
					else if(t->par==NULL){
						root = t;
					}
					
					b= t->par;
					SymNode* c = t->par;
					while(c!=NULL){
						c->height = max(getheight(c->right),getheight(c->left)) +1;
						c = c->par;
					}
					
					//after this tree will be balanced

				}
			}
			/*cout<<"after rot : tree is "<<endl;
			deb(root);
			heightprint(root);
			cout<<"next step"<<endl;*/

		}
		
	}

	return;
}

int SymbolTable::search(string k){

	SymNode* r = root;

	while((r!=NULL)&&(r->key!=k)){
		if(r->key>k){
			r = r->left;
		}
		else{
			r= r->right;
		}
	}

	if(r==NULL){
		return -2;
	}

	else{
		
		return r->address;
	}
}

void SymbolTable::assign_address(string k,int idx){
	
	SymNode* r = root;
	
	while((r->key!=k)&&(r!=NULL)){
		if(r->key>k){
			r = r->left;
		}
		else{
			r= r->right;
		}
	}
	if(r==NULL){
		return;
	}
	
	r->address = idx;
	
	
		
}

int SymbolTable::get_size(){
	return size;
}

SymNode* SymbolTable::get_root(){
	return root;
}

SymbolTable::~SymbolTable(){
	annihilator(root);
}



 







