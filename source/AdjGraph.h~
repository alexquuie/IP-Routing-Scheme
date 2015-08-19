#ifndef ADJGRAPH_H
#define ADJGRAPH_H
#include<iostream>
using namespace std;
//The structure to represent an adjacency list node
struct AdjListNode{
	AdjListNode(int d,int w){
		dest = d;
		weight = w;
		next = NULL;
	}
	AdjListNode(int d, int w, AdjListNode *tmpN){
		dest = d;
		weight = w;
		next = tmpN;
	}

    int dest;
	int weight;
	AdjListNode* next;
};
 
//The structure to represent an adjacency list
struct AdjList{
    AdjListNode *head;  // pointer to head of list
};
 
//The class represents the adjcent Graph 
class AdjGraph{	
public: 
//Data Members
    int numV;
    AdjList* vexList;// The array of all nodes' vex lists

//Member Functions
    //constructor		
    AdjGraph(int n=0){ 
	numV = n;
	vexList = (AdjList*) malloc(n*sizeof(AdjList));
	for (int i = 0; i < numV; ++i)vexList[i].head = NULL;
    }
     // Please notice that it can only be used for undirected graph
	void addEdge(int src, int dest, int w){
		// Add an edge from src to dest.  A new node is added to the adjacency
		// list of src.  The node is added at the begining
		AdjListNode *newNode = new AdjListNode(dest,w);
		if(vexList[src].head==NULL){			
			newNode->next=NULL; 
			vexList[src].head = newNode; 
		}else{
			newNode->next = vexList[src].head;
			vexList[src].head = newNode; 
		}
		//Add an edge from dest to src
		newNode = new AdjListNode(src,w);
		if(vexList[dest].head==NULL){			
			newNode->next=NULL; 
			vexList[dest].head = newNode; 
		}else{
			newNode->next = vexList[dest].head;
			vexList[dest].head = newNode; 
		}
	}
	//The function to print the adjacenncy list representation of graph
	void printGraph(){
		for (int indV = 0; indV < numV; ++indV){        
			AdjListNode* pCrawl = vexList[indV].head;
			cout<<endl<<"Adjacency list of vertex"<<indV<<" head "<<endl;
			while (pCrawl){
				cout<<"->"<<pCrawl->dest;
				pCrawl = pCrawl->next;
			}
		}
	}

};
#endif
