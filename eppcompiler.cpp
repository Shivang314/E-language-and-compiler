/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler (1).h"
//using namespace std;
//include <iostream>
//Write your code below this line

EPPCompiler::EPPCompiler(){
	
    memory_size=100000;
    for(int i=1;i<100001;i++){
        mem_loc.push_back(i-1);
    }
    
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
	
    memory_size=mem_limit;
    output_file=out_file;
    for(int i=0;i<memory_size;i++){
        mem_loc.push_back(i);
    }
    
}

void EPPCompiler::compile(vector<vector<string> > code){
    ofstream file;
    file.open(output_file);
    for(vector<string> v :code){
        targ.parse(v);
        
        write_to_file(generate_targ_commands());
    }
    file.close();
}

void push(vector<string>* v,ExprTreeNode* node,Parser* p){
    if(node==NULL){
        return;
    }
    if(node->left==NULL && node->right==NULL){
        if(node->type=="VAL"){
            string add = "PUSH " + to_string(node->num);
            v->push_back(add);
            return;
        }
        else{
            string add = "PUSH mem[" + to_string(p->symtable->search(node->id)) + "]";
            v->push_back(add);
            return;
        }
    }
    else{
        push(v,node->right,p);
        push(v,node->left,p);
        v->push_back(node->type);
    }
    
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> v;
    ExprTreeNode* node = targ.expr_trees.back();
    

    if(node->left->type=="DEL"){
        string add = "DEL = mem[" + to_string(targ.last_deleted) + "]";
        v.push_back(add);
        mem_loc.push_back(targ.last_deleted);
        
        
    }
    else if(node->left->type=="RET"){
        push(&v,node->right,&targ);
        v.push_back("RET = POP");
    }
    else{
        
        push(&v,node->right,&targ);
        targ.symtable->assign_address(node->left->id,mem_loc.back());
        mem_loc.pop_back();
        
        string add= "mem[" + to_string(targ.symtable->search(node->left->id)) +"] = POP";
        v.push_back(add);
    }
    return v;
}

void EPPCompiler::write_to_file(vector<string> commands){
     ofstream write_on;
     write_on.open(output_file,ios::app);
     if(write_on.is_open()){
         for(int i=0;i<commands.size();i++){
             write_on << commands[i] << endl;
             //cout<<commands[i]<<endl;
         }
     }
     write_on.close();
}

EPPCompiler::~EPPCompiler(){
    targ.expr_trees.clear();
    mem_loc.clear();

}