#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <fstream>
using namespace std;

class Graph{

	public:
		Graph(vector<string>&);
		void Clean();
		void ProcessWord(string&);
		void Print();
	
	private:
		vector<string> diceNodes;
		string word;
		multimap<int, int> *edges;
		vector<int> *visited;
		map<int, int> *path;
		map<char, set<int>> diceDict;
};


int main(int argc, char* argv[]){

	if(argc != 3){

		cerr<<"usage: worddice dices words\n";
		exit(0);
	}

	Graph *myGraph;
	vector<string> dices;
	string ss;
	ifstream dicesIn(argv[1]), wordsIn(argv[2]); 

	if(!dicesIn or !wordsIn){

		cerr<<"cannot open file\n";
		exit(0);
	}

	dices.reserve(50);
	while(dicesIn>>ss){

		dices.push_back(ss);
	}

	myGraph = new Graph(dices);

	while(wordsIn>>ss){

		myGraph->ProcessWord(ss);
		myGraph->Print();
		myGraph->Clean();
		
	}
	

	delete myGraph;
	dicesIn.close();
	wordsIn.close();
}
		
Graph::Graph(vector<string>& dices):diceNodes(dices){

	for(int i=0; i<diceNodes.size(); ++i){
		for(int j=0; j<diceNodes[i].size(); ++j){

			diceDict[diceNodes[i][j]].insert(i);	
		}

	}

	/*
	map<char, set<int>>::iterator it;
	set<int>::iterator sit;
	for(it=diceDict.begin(); it!=diceDict.end(); ++it){
		cout<<it->first<<' ';
		for(sit=it->second.begin(); sit!=it->second.end();++sit){

			cout<<*sit<<' ';
		}
		cout<<endl;
			
	}
			 */
}

void Graph::Clean(){

	delete edges;
	delete visited;
	delete path;

}


void Graph::ProcessWord(string& ss){

	word = ss;
	visited = new vector<int>(diceNodes.size()+word.size(), 0);
	map<char, set<int>>::iterator mit;
	set<int>::iterator sit;
	edges = new multimap<int, int>;

	for(int i=0; i<word.size(); ++i){

		mit = diceDict.find(word[i]);
		if(mit == diceDict.end()){

			cout<<"Cannot spell "<<word<<'\n';
			return;
		}else{

			for(sit=mit->second.begin(); sit!=mit->second.end(); ++sit){
				
				edges->insert(pair<int, int>(*sit, i));
			}

		}
	}

	/*
	cout<<word<<'\n';
	multimap<int, int>::iterator it;
	for(it=edges->begin(); it!=edges->end(); ++it){
		
		cout<<it->first<<' '<<it->second<<' '<<diceNodes[it->second]<<'\n';
	}
	cout<<'\n';
*/
}


void Graph::Print(){

	int i, node = 0, end;
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> range;
	multimap<int, int>::iterator mit;

	cout<<"Node 0: SOURCE EDGES to ";
	for(i=0; i<diceNodes.size(); ++i){

		cout<<i+1<<' ';
	}
	cout<<'\n';

	for(i=0; i<diceNodes.size(); ++i){

		printf("Node %d: %s Edges to ", ++node, diceNodes[i].c_str());
		range = edges->equal_range(i);
		for(mit=range.first; mit!=range.second; ++mit){

			cout<<mit->second+diceNodes.size()+1<<' ';
		}
		cout<<'\n';
	}

	end = node+word.size()+1;

	for(i=0; i<word.size(); ++i){

		printf("Node %d: %c Edges to %d\n", ++node, word[i], end);
	}


	printf("Node %d: SINK Edges to \n\n", end);
}
