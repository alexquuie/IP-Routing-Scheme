#include <stdio.h>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "time.h"
#include "fibonacci.h"
#include "Dijkstra.h"
#include "AdjGraph.h"
using namespace std;

int main(){
	static int numOfVex = 5;
	AdjGraph *graph=new AdjGraph(numOfVex);
        graph->addEdge(0,1,2);
	graph->addEdge(0,2,2);
	graph->addEdge(0,3,2);
	//graph->addEdge(0,4,2);

	int *dist = new int[numOfVex];
	int *prev = new int[numOfVex];
	int src = 0;
	int dst = 4;
	if(dst>=numOfVex){
		cerr<<"Illegal index of nodes!"<<endl;
		exit(0);
		}
	ShortestPaths(graph,src,prev,dist);

	vector<int> path;
	path.push_back(dst);

	int pre=dst;
	while(pre!=src){
		pre = prev[pre];
		if(pre<0)break;
		path.push_back(pre);
	}
	if(path.size()<=1){
		cout<<"There is no legal path found!"<<endl;
	}else{
		reverse(path.begin(),path.end());  
		cout<<dist[dst]<<endl; //print the total weight
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<" ";
		}
	}
	cout<<endl;
	return 0;
}
