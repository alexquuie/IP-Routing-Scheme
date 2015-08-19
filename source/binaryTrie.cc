#include<iostream>
#include<string>
#include"binaryTrie.h"
#include <deque>
using namespace std;

//insert a node with a string (ip address) and a int (nextHop)
bool binaryTrie::insert(string str,int np){
		if(str.empty()){
			cout<<"The string is empty!"<<endl;
			return false;
		}
		trieNode *tmp = root;
		int bittmp;
		for(int i=0;i<str.length()-1;i++){
			bittmp = tmp->bit;
			if(str[bittmp]=='0'){
				if(tmp->lChild==NULL){
					tmp->lChild = new trieNode(false,i+1,"",-1,tmp,NULL,NULL);
				}
				tmp = tmp->lChild;
			}else if(str[bittmp]=='1'){
				if(tmp->rChild==NULL){
					tmp->rChild = new trieNode(false,i+1,"",-1,tmp,NULL,NULL);
				}
				tmp = tmp->rChild;
			}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
			}
		}
		bittmp = str.length()-1;
		if(str[bittmp]=='0'){
			if(tmp->lChild==NULL){
				tmp->lChild = new trieNode(true,-1,str,np,tmp,NULL,NULL);
			}else{
				if(str.compare(tmp->lChild->value)==0)cout<<"This element has occured!"<<endl;
				else cout<<"Error occured!"<<endl;
				}
		}else if(str[bittmp]=='1'){
			if(tmp->rChild==NULL){
				tmp->rChild = new trieNode(true,-1,str,np,tmp,NULL,NULL);
			}else{
				if(str.compare(tmp->rChild->value)==0)cout<<"This element has occured!"<<endl;
				else cout<<"Error occured!"<<endl;
				}
		}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
		}
		return true;
}

//remove a node with specific string (ip address)
//however, there is no need to remove in this static tree;
bool binaryTrie::remove(string str){
		if(str.empty()){
			cout<<"The string is empty!"<<endl;
			return false;
		}
		trieNode *tmp = root;
		int bittmp;
		for(int i=1;i<str.length();i++){
			if(tmp==NULL){
				cout<<"No such node!"<<endl;
				return false;
			}
			bittmp = tmp->bit;
			if(str[bittmp]=='0'){
				if(tmp->lChild==NULL){
					cout<<"No such node!"<<endl;
					return false;
				}
				tmp = tmp->lChild;
			}else if(str[bittmp]=='1'){
				if(tmp->rChild==NULL){
					cout<<"No such node!"<<endl;
					return false;
				}
				tmp = tmp->rChild;
			}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
			}
		}
		bittmp = tmp->bit;
		if(str[bittmp]=='0'){
			if(tmp->lChild==NULL){
				cout<<"No such node!"<<endl;
				return false;
			}else{
				if(str.compare(tmp->lChild->value)==0){
					cout<<"Found it!"<<endl;					
					trieNode* parent =tmp;
					tmp = tmp->lChild;
					parent->lChild = NULL;
					delete tmp;
				}
				else{
					cout<<"No such node!"<<endl;
					return false;
					}
				}
		}else if(str[bittmp]=='1'){
			if(tmp->rChild==NULL){
				cout<<"No such node!"<<endl;
				return false;
			}else{
				if(str.compare(tmp->rChild->value)==0){
					cout<<"Found it!"<<endl;
					trieNode* parent =tmp;
					tmp = tmp->rChild;
					parent->rChild = NULL;
					delete tmp;
				}
				else {
					cout<<"No such node!"<<endl;
					return false;
					}
				}
		}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
		}
		return false;
	}

//search a node with specific string (ip address)
trieNode* binaryTrie::search(string str){
		if(str.empty()){
			cout<<"The string is empty!"<<endl;
			return NULL;
		}
		trieNode *tmp = root;
		int bittmp;
		while(tmp->isElement!=true){
			if(tmp==NULL){
				cout<<"No such node!"<<endl;
				return NULL;
			}
			bittmp = tmp->bit;
			if(str[bittmp]=='0'){
				if(tmp->lChild==NULL){
					cout<<"No such node!"<<endl;
					return NULL;
				}else 
					tmp = tmp->lChild;
			}else if(str[bittmp]=='1'){
				if(tmp->rChild==NULL){
					cout<<"No such node!"<<endl;
					return NULL;
				}else 
					tmp = tmp->rChild;
			}else{
				cout<<"Invalid ip bit!"<<endl;
				return NULL;
			}
		}
		std::size_t found = tmp->value.find('*');
		if(found!=std::string::npos){
			string substr1=str.substr(0,found);
			string substr2=tmp->value.substr(0,found);
			if(substr2.compare(substr1)==0){
				//cout<<"Found it!"<<endl;
				return tmp;
			}else{
			cout<<"No such node!"<<endl;
			return NULL;
			}
		}else if(str.compare(tmp->value)==0){
					//cout<<"Found it!"<<endl;
					return tmp;
		}else{
			cout<<"No such node!"<<endl;
			return NULL;
		}
		return NULL;
}

//forward cleanup the nodes with less than two children
bool binaryTrie::fwdCleanup(){
   	return cleanUp(root);
}
//recursivly forward cleanup the nodes with less than two children
//There is no need to copy the prefix
bool binaryTrie::cleanUp(trieNode *pLoc){
	if(pLoc){
		if(pLoc->lChild)cleanUp(pLoc->lChild);
		if(pLoc->rChild)cleanUp(pLoc->rChild);
	}
	
	if(pLoc->isElement==true)return true;
	else if(pLoc->lChild==NULL&&pLoc->rChild==NULL){//cannot happen??
		if(pLoc->parent){
			trieNode *parentNode = pLoc->parent;//??Is that legal?
			delete pLoc;
			pLoc = NULL;
		}else{			
			cerr<<"This is Root! The tree is empty!"<<endl;
			exit(0);
		}
	}else if(NULL==pLoc->lChild){
		//copy rchild to pLoc;
		trieNode* tmpNode = pLoc->rChild;
		pLoc->isElement = tmpNode->isElement;
		if(tmpNode->bit==-1)pLoc->bit = -1;
		pLoc->nextHop = tmpNode->nextHop;
		pLoc->value = tmpNode->value;
		pLoc->lChild = tmpNode->lChild;
		pLoc->rChild = tmpNode->rChild;
		delete tmpNode;
	}else if(NULL==pLoc->rChild){
		//copy lchild to pLoc;
		trieNode* tmpNode = pLoc->lChild;
		pLoc->isElement = tmpNode->isElement;		
		if(tmpNode->bit==-1)pLoc->bit = -1;
		pLoc->nextHop = tmpNode->nextHop;
		pLoc->value = tmpNode->value;
		pLoc->lChild = tmpNode->lChild;
		pLoc->rChild = tmpNode->rChild;		
		delete tmpNode;
	}/*else{
		cout<<"Traverse Ended!"<<endl;
		return false;
	}*/
	return true;
}

//post order traversal to clean up the nodes with less than two children
bool binaryTrie::npClean(){
	postOrdExamine(root);
	return true;
}

//recursivly post order traversal to clean up the nodes with less than two children
bool binaryTrie::postOrdExamine(trieNode *pLoc){
	if(pLoc){
		if(pLoc->lChild)postOrdExamine(pLoc->lChild);
		if(pLoc->rChild)postOrdExamine(pLoc->rChild);
		if(pLoc->lChild && pLoc->rChild&&pLoc->lChild->isElement && pLoc->rChild->isElement){
			if(pLoc->lChild->nextHop==
				pLoc->rChild->nextHop){
					string substr = pLoc->lChild->value.substr(0,pLoc->bit)+'*';							
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = substr;
					pLoc->nextHop= pLoc->rChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
					}
		}else if(pLoc->lChild && NULL==pLoc->rChild &&pLoc->lChild->isElement){						
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = pLoc->lChild->value;
					pLoc->nextHop= pLoc->lChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
		}else if(pLoc->rChild && NULL==pLoc->lChild &&pLoc->rChild->isElement){
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = pLoc->rChild->value;
					pLoc->nextHop= pLoc->rChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
		}
	}else{
		return true;
	}
}



/*Print the tree level by level*/  
void binaryTrie::print(){
	trieNode* pLoc =  root;
	if (pLoc == NULL) cout<<"Empty tree";
	std::deque<trieNode*> dq; 
	trieNode* end = pLoc;

	while (true) {
		if (pLoc->lChild)dq.push_back(pLoc->lChild);
		if (pLoc->rChild)dq.push_back(pLoc->rChild);	

		if(pLoc->isElement){
			cout<<"The prefix:"<<pLoc->parent->bit<<" Value:"<<pLoc->value<<" NextHop:"<<pLoc->nextHop;
		}else{
			cout<<"The prefix:"<<pLoc->bit;
		}
		if (pLoc != end){cout << " "; }
		else {
			cout <<endl;
			if (dq.empty()) break;
			end = dq.back();
		}
		pLoc = dq.front();
		dq.pop_front();

	}
}
