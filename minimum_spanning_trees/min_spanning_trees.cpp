#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

//Prototypes
void MST(int [], int);
void PrintMST(set<pair<int, int>>&, int);

int main(){

	int size, i, distance, *edges;
	while(cin>>size){
		
		edges = new int[size*size];
		for(i=0; i<size*size; ++i){
			
			cin>>distance;
			edges[i] = distance;
		}

		MST(edges, size);

		delete edges;
	
	}

}

void MST(int edges[], int size){
	
	vector<int> nodes(size, -1);
	int visited[size] = {0};
  	multimap<int, int> myMap;
	multimap<int, int>::iterator current;
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> range;  
	set<pair<int, int>> mst;

	int i, nextNode, currNode, score = 0;

	for(i=1; i<size; ++i){

		if(edges[i]!=-1){
			myMap.insert(pair<int, int>(edges[i], i));
			nodes[i] = edges[i];
		}
	}

	while(!myMap.empty()){

		current = myMap.begin();
		myMap.erase(current);
		
		
		nextNode = (current->second)%size;
		currNode = (current->second)/size;

		visited[currNode] = 1;

		score += edges[current->second];
	
		if(nextNode > currNode){
			mst.insert(pair<int, int>(currNode, nextNode));
		}else{
			mst.insert(pair<int, int>(nextNode, currNode));
		}

		for(i = 0; i<size; ++i){


			if(edges[nextNode*size+i] != -1 and visited[i] == 0){
					
				if(nodes[i] != -1){

					if(edges[nextNode*size+i] > nodes[i]){
						continue;
					}

					range = myMap.equal_range(nodes[i]);

					for(current = range.first; current != range.second; ++current){
						
						if(current->second%size == i){
							
							myMap.erase(current->first);
							break;
						}
					}
				}
				myMap.insert(pair<int, int>(edges[nextNode*size+i], nextNode*size+i));
				nodes[i] = edges[nextNode*size+i];
			}
		
		}
	}

	cout<<score<<'\n';
	PrintMST(mst, size);

	cout<<"\n";		

}

void PrintMST(set<pair<int, int>>& mst, int size){

	char nodes[size];
	set<pair<int, int>>::iterator sit;

	for(int i=0; i<size; ++i){

		nodes[i] = (char) i+65;
	}

	for(sit = mst.begin(); sit != mst.end(); ++sit){

		cout<<nodes[sit->first]<<nodes[sit->second]<<'\n';
	}
}
