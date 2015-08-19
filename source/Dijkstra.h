#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <climits>
#include "AdjGraph.h"
#include "fibonacci.h"
#include <set>

// The structure represents the path nodes

class pathNode{	
public:
//Data Members
	//the path weight and the destination, note that the source node is known.
	int weight;
	int vex;
	pathNode(){
		weight = 0.0;
		vex = 0;
	}
//Member Functions
	pathNode(int w, int v){
		weight = w;
		vex = v;
	}
	pathNode &operator = (const pathNode &nodeB){
		weight = nodeB.weight;
		vex = nodeB.vex;
		return *this;
	}
	bool operator < (pathNode nodeB){
		return (weight<nodeB.weight);
	}
	
	bool operator > (pathNode nodeB){
		return (weight>nodeB.weight);
	}
	
	bool operator <= (pathNode nodeB){
		return (weight<=nodeB.weight);
	}

	
	bool operator >= (pathNode nodeB){
		return (weight>=nodeB.weight);
	}
	
	bool operator == (pathNode nodeB){
		return (weight==nodeB.weight);
	}


};

//The function implement the single source all destination algorithm (Dijkstra's algorithm).

void ShortestPaths(AdjGraph *graph, int v, int *prev,int *dist)
// the prev[] stores the previous node from destination node to source node
// the dist[] stores the distance from destination node to source node
{
	int numofVex = graph->numV;
	// heapNodeAddList[] is used to store the pointer address of each path node in the Fibonacci Heap
	long * heapNodeAddList = (long *)malloc(sizeof(char*)* numofVex);
	FibonacciHeap<pathNode> disHeap; 
	// The set S is used to represent if the node has been removed from the Fibonacci Heap or not
	// To speed up, we use STL set;
	set<int> S;
	for(int i=0;i< numofVex ;i++){
		dist[i] = INT_MAX;
		prev[i] = -1;
		pathNode tmpNode(dist[i],i);
		heapNodeAddList[i] = reinterpret_cast<long>(disHeap.insert(tmpNode));
	}
	prev[v] = v;
	dist[v] = 0;
	 
	pathNode newNode(0,v);					
	disHeap.decreaseKey(reinterpret_cast<heapNode<pathNode>*>(heapNodeAddList[v]),newNode);
	
	while(!disHeap.isEmpty()){
		int u = disHeap.removeMinimum().vex;
		S.insert(u);
		  // Determine n - 1 paths from v.
                  /* Choose u from among those vertices in Fibonacci such that dist[u] is minimum;*/
		  // update the dist[tmpv] for all nodes tmpv adjcent with node u.	
		  AdjListNode* pCrawl = graph->vexList[u].head;
		  while (pCrawl != NULL){
			  int tmpv = pCrawl->dest;
			  // If shortest distance to v is not finalized yet, and distance to v
			  // through u is less than its previously calculated distance
			  if (dist[u] != INT_MAX && 
                     pCrawl->weight + dist[u] <= dist[tmpv]){
					 dist[tmpv] = dist[u] + pCrawl->weight;
					 
					 // update distance value in Fibonacci heap if tmpv has not removed from the heap;
					 pathNode newNode(dist[tmpv],tmpv);			
					if(S.find(tmpv)==S.end()){
						disHeap.decreaseKey(reinterpret_cast<heapNode<pathNode>*>(heapNodeAddList[tmpv]),newNode);
					}
					 prev[tmpv] = u;
            }
		pCrawl = pCrawl->next;
        }
    }
}

// the nextHop[] stores the nextHop from source node to destination node
// This function transform the prev node representation of the path to next hop representation of the path, 
// which is needed by the router scheme.
void getNextHop(int v, int numOfVex, int *prev, int *nextHop){
	for(int i=0;i < numOfVex;i++){
		int src = v;
		int dst = i;
		if(src==dst)nextHop[i] = i;
		else{
			int pre = prev[dst];
			int np = dst;
			while(pre!=src){				
				if(pre<0){
					np=-1;
					break; 
				}
				np = pre;
				pre = prev[pre];
			}
			//Only record the prev node before src which is the nexhop from src to dst
			nextHop[i] = np;
		}
	}
	
}

#endif
