#ifndef BINARYTRIE_H
#define BINARYTRIE_H
#include<iostream>
#include<string>
using namespace std;

//The struct to represent the trie node;
class trieNode{
public:
	bool isElement;
	int bit;//starting from 0
	string value;
	int nextHop;
	trieNode *lChild;
	trieNode *rChild;
	trieNode *parent;
	trieNode(bool e = false,int b=-1,string v="",int nh=-1,trieNode *p=NULL,trieNode *l=NULL,trieNode *r=NULL){
		isElement = e;
		bit = b;
		value=v;
		nextHop = nh;	
		parent=p;
		lChild = l;
		rChild = r;
	}
	~trieNode(){
	}
};


class binaryTrie{
private:
	trieNode *root;	
	//recursivly post order traversal to clean up the nodes with less than two children
	bool postOrdExamine(trieNode *);
	//recursivly forward cleanup the nodes with less than two children
	bool cleanUp(trieNode*);
public:
	//constructor
	binaryTrie(){
		root=new trieNode(false,0,"",-1,NULL,NULL,NULL);
	}
	//insert a node with a string (ip address) and a int (nextHop)
	bool insert(string,int);
	//remove a node with specific string (ip address)
	bool remove(string);
	//search a node with specific string (ip address)
	trieNode *search(string);
	//forward cleanup the nodes with less than two children
	bool fwdCleanup();
	//post order traversal to clean up the nodes with less than two children
	bool npClean();
	//to print the whole trie
	void print();	
	//destructor
	~binaryTrie(){
	}
};
#endif
