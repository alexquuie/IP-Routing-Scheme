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

int main(int argc, char *argv[]){

	if(argc!=4){
		cerr<<"There is no enough arguments followed by ./ssp"<<endl;
		exit(0);
	}
	//clock_t start, finish;//count the run time
	//start = clock();//starting time

	//read from the graph file to get the graph informtion
	ifstream infile;
	string n_tmp;
	string m_tmp;
	string k_tmp;
	
	infile.open(argv[1]);

	if(infile.fail()){
            cerr<<"Fail to open the .txt file!"<<endl;
	    exit(0);
	}

	//there are # of vetices and # of edges in the first line
	getline(infile,n_tmp,' ');
	getline(infile,m_tmp,'\n');
	static int numOfVex = stoi(n_tmp);
	static int numOfEdge = stoi(m_tmp);
	int n;
	int m;
	int k;
	AdjGraph *graph=new AdjGraph(numOfVex);
	//read the graph file to get the edge information
	while(!infile.eof()){
		n_tmp.clear();
		m_tmp.clear();
		k_tmp.clear();
		getline(infile,n_tmp,' ');
		getline(infile,m_tmp,' ');
		getline(infile,k_tmp,'\n');
		if(n_tmp.length()&&m_tmp.length()&&k_tmp.length()){
			n = stoi(n_tmp);
			m = stoi(m_tmp);
			k = stoi(k_tmp);
			if(n!=m){
				graph->addEdge(n,m,k);
			}
		}
	}
	// Run the single source all destination algorithm (Dijkstra's algorithm)
	int *dist = new int[numOfVex];
	int *prev = new int[numOfVex];
	int src = atoi(argv[2]);
	int dst = atoi(argv[3]);
	if(dst>=numOfVex){
		cerr<<"Illegal index of nodes!"<<endl;
		exit(0);
		}
	ShortestPaths(graph,src,prev,dist);
	
	//use a vector to reverse the node list s.t. to transform the pre-node represtation to back-node reprentation
	vector<int> path;
	path.push_back(dst);

	int pre=dst;
	while(pre!=src){
		pre = prev[pre];
		if(pre<0)break;
		path.push_back(pre);
	}
	if(path.size()<=1){
		//print warning if there is no node in the path vector except the dst node.
		cout<<"There is no legal path found!"<<endl;
	}else{
		//reverse the node list.
		reverse(path.begin(),path.end());  
		cout<<dist[dst]<<endl; //print the total weight
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<" ";
		}
	}
	cout<<endl;
	
	//finish =clock();//finishing time
	//cout<<endl<<"The run time is:"<<(finish-start)/CLOCKS_PER_SEC<<"s."<<endl;
	return 0;
}
