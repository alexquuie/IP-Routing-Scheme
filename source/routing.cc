#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include "fibonacci.h"
#include "AdjGraph.h"
#include "Dijkstra.h"
#include "binaryTrie.h"
using namespace std;

int main(int argc, char* argv[]){
	if(argc!=5){
		cerr<<"There is no enough arguments followed by ./routing"<<endl;
		exit(0);
		}
	////Phase 1 Construct Graph
	//get graph information from graph file.
	ifstream infile1;
	string n_tmp;
	string m_tmp;
	string k_tmp;
	infile1.open(argv[1]);
	if(infile1.fail()){
            cerr<<"Fail to open the graph file!"<<endl;
	    exit(0);
	}
	getline(infile1,n_tmp,' ');
	getline(infile1,m_tmp,'\n');

	//get # of vetices and edges in the first line
	static int numOfVex = stoi(n_tmp);
	static int numOfEdge = stoi(m_tmp);
	int n;
	int m;
	int k;
	AdjGraph *graph=new AdjGraph(numOfVex);
	
	//get edge information from graph file.
	while(!infile1.eof()){
		n_tmp.clear();
		m_tmp.clear();
		k_tmp.clear();
		getline(infile1,n_tmp,' ');
		getline(infile1,m_tmp,' ');
		getline(infile1,k_tmp,'\n');
		if(n_tmp.length()&&m_tmp.length()&&k_tmp.length()){
			n = stoi(n_tmp);
			m = stoi(m_tmp);
			k = stoi(k_tmp);
			if(n!=m){
				graph->addEdge(n,m,k);
			}
		}
	}
	
	////Phase 2 Construct Binary Trie
	ifstream infile2;
	string n1_tmp;
	string n2_tmp;
	string n3_tmp;
	string n4_tmp;
	int n1,n2,n3,n4;
	vector<string> nip;
	string n1str;
	string n2str;
	string n3str;
	string n4str;
	string nstr;
	infile2.open(argv[2]);
	if(infile2.fail()){
            cerr<<"Fail to open the ip file!"<<endl;
	    exit(0);
	}
	
	//get ip address for each node and then convert the decimal format to binary format
	while(!infile2.eof()){
		n1_tmp.clear();
		n2_tmp.clear();
		n3_tmp.clear();
		n4_tmp.clear();
		getline(infile2,n1_tmp,'.');
		getline(infile2,n2_tmp,'.');
		getline(infile2,n3_tmp,'.');
		getline(infile2,n4_tmp,'\n');
		if(n1_tmp.length()&&n2_tmp.length()&&n3_tmp.length()&&n4_tmp.length()){
			n1 = stoi(n1_tmp);
			n2 = stoi(n2_tmp);
			n3 = stoi(n3_tmp);
			n4 = stoi(n4_tmp);
			bitset<8> n1bit(n1);
			bitset<8> n2bit(n2);
			bitset<8> n3bit(n3);
			bitset<8> n4bit(n4);
			n1str = n1bit.to_string();
			n2str = n2bit.to_string();
			n3str = n3bit.to_string();
			n4str = n4bit.to_string();

			nstr = n1bit.to_string() + n2bit.to_string()
				+ n3bit.to_string()+ n4bit.to_string();

			nip.push_back(nstr.c_str());
		}
	}


	////Phase 3 Construct Router Table for each node

	int *dist = new int[numOfVex];
	int *prev = new int[numOfVex];

	int *nextHop= new int[numOfVex];
	static int src = atoi(argv[3]); 
	static int dst = atoi(argv[4]);
	if(dst>=numOfVex){
		cerr<<"Illegal index of nodes!"<<endl;
		exit(0);
	}
	vector<int> path;
	path.push_back(dst);
	//first run Dijkstra's algorithm for the src node
	ShortestPaths(graph,src,prev,dist);	
	//get the path from src to dst
	//use a vector to reverse the node list s.t. 
	//to transform the pre-node represtation to back-node reprentation
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
		
		//run Dijkstra's algorithm for each node at the path, 
		//construct the binary Trie, search for the destination's ip address
		//in this binary Trie and then print the prefix.
		
		string strtmp = nip[dst];// the ip address for destination
		
		for(int ind=0;ind<path.size()-1;ind++){
			//intermediate node tmpSrc;
			int tmpSrc = path[ind];			
			if(tmpSrc!=src)ShortestPaths(graph,tmpSrc,prev,dist);
			
			getNextHop(tmpSrc, numOfVex, prev, nextHop);
			binaryTrie tmpBT;
			for(int jnd=0;jnd<numOfVex;jnd++){
				if(jnd!=tmpSrc){
					//insert each node's ip address with nextHop to the binary trie for 
					//intermediate node at this time
					//jnd does not equal to src
					tmpBT.insert(nip[jnd],nextHop[jnd]);
				}
			}
			// post order examine to combine the nodes with same next hop;
			tmpBT.npClean();
			//search for the destination's ip address in this binary Trie
			trieNode *tmpNode = tmpBT.search(strtmp);
			if(tmpNode){
				int tmpInd = tmpNode->parent->bit;
				string tmpIP = nip[dst];
				cout<<tmpIP.substr(0,tmpInd+1)<<" ";
			}else{
				//if the search result is NULL, that is to say there is no legal path from
				//intermediate node to the dst node
				cerr<<"there is no legal path from node "<<src<<" to node "
				<<dst<<" through the intermediate node "<<tmpSrc<<endl;
				exit(0);
				}
		}
		cout<<endl;
	}
	return 0;
}
