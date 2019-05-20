// dijsktras.cpp
#include <iostream>
#include <map>
#include <cstdio>
#include <vector>

using namespace std;

class Dijkstras{

public:

	Dijkstras(int, int);
	
	void findRoute(int, int);
	
	int row, col;
	vector<int> tileMap, distances, backedges, visited;	

private:
	void printRoute(int, int);
	inline void setEdge(int &, int, bool);
};

// Main Execution

int main() {

	int size, i, row, col, score, startX, startY, endX, endY;
	char tile;
	map<char, int> scoreMap;
    Dijkstras *dijkstras;

	cin>>size;

	for(i=0; i<size; ++i){

		cin>>tile>>score;
		scoreMap[tile] = score;
		
	}

	cin>>row>>col;

	dijkstras = new Dijkstras(row, col);	

	for(i=0; i<row*col; ++i){
		
		cin>>tile;

		dijkstras->tileMap[i] = scoreMap[tile];



	}

	cin>>startX>>startY>>endX>>endY;


	dijkstras->findRoute(startX*col+startY, endX*col+endY);
	
	delete dijkstras;

	return 0;
}


Dijkstras::Dijkstras(int r, int c): row(r), col(c), tileMap(vector<int>(row*col)), distances(vector<int>(row*col, -1)), backedges(vector<int>(row*col, -1)), visited(vector<int>(row*col, 0)) {

}



void Dijkstras::findRoute(int start, int end){

	multimap<int, int> myMap;
	multimap<int, int>::iterator current;
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> range;
	int index, i, distance;
	int edges[4] = {-1,-1,-1,-1};


	distances[start] = 0;
	visited[start] = 1;
	myMap.insert(pair<int, int>(0, start));	


	while(!myMap.empty()){
		
		current = myMap.begin();
		myMap.erase(current);
		index = current->second;
		visited[index] = 1;

		setEdge(edges[0], index-col, index/col);
		setEdge(edges[1], index-1, index%col);
		setEdge(edges[2], index+1, index%col<col-1);
		setEdge(edges[3], index+col, index/col<row-1);

		for( i=0; i<4; ++i){

			if(edges[i] != -1){

				distance = distances[index]+tileMap[index];

				if (distances[edges[i]]!=-1){
					
					if(distances[edges[i]] > distance){

						range = myMap.equal_range(distances[edges[i]]);

						for(current = range.first; current != range.second; ++current){
						
							if(current->second == edges[i]){
								myMap.erase(current);
								break;
							}
						}

					}else{

						continue;
					}

					
				}
					
				distances[edges[i]] = distance;
				backedges[edges[i]] = index;
				myMap.insert(pair<int, int>(distance, edges[i]));

				
				if(edges[i] == end){
	
					printRoute(start, end);
					return;
				}
			}
		}
	}
	
	
}


void Dijkstras::printRoute(int start, int end){

	int index = end;
	vector<int> route;
	cout<<distances[end]<<'\n';
	
	route.push_back(index);

	while(index!=start){

		index = backedges[index];
		route.push_back(index);

	}

	for(int i=route.size()-1; i>=0; --i){
		cout<<route[i]/col<<' '<<route[i]%col<<'\n';
	}

}


void Dijkstras::setEdge(int &edge, int index, bool flag){

	if(flag and !visited[index]){
		edge = index;	
	}else{
		edge = -1;	
	}
}
