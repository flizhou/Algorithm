#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <map>
#include "disjoint.h"
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
	void play();
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;

  private:
	int get_connected_cells(int, int, DisjointSetByRankWPC*, bool flag = false);
	vector <int> nonempties;
	DisjointSetByRankWPC* dset;
	map<int, multimap<int, int>> mmap;
	void find_swap(int&, int&);
	int find_max_score(int, int, int, int&, int&);
	int max_score_helper(int, int, int, int&);
	void set_goals(int);
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);
  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
	    
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 20;
        board[i*c+j] = tolower(board[i*c+j]);

      }
      if (islower(board[i*c+j])) {
    	nonempties.push_back(i*c+j);
	  }
  	}
  }

  set_goals(20);
  set_goals(15);
  set_goals(10);
}

void Superball::set_goals(int score){

  for(int i =0; i<r; ++i){
	  for(int j=0; j<c; ++j){

		if(goals[i*c+j] == score){

			bool flags[8] = {i>0 and j>0, i>0, i>0 and j<c-1, j>0, 
				i<r-1 and j>0, i<r-1, i<r-1 and j <c-1, j<c-1};

			int indexes[8] = {(i-1)*c+j-1, (i-1)*c+j, (i-1)*c+j+1, i*c+j-1,
				(i+1)*c+j-1, (i+1)*c+j, (i+1)*c+j+1, i*c+j+1};
			for(int n=0; n<8; ++n){
				if(flags[n] and goals[indexes[n]] == 0){
					goals[indexes[n]] = score-8;
				}
			}
		}
	}
  }

}


void Superball::play(){

	int score = 0, size = 0;
	int index, num;
	multimap<int, int>::reverse_iterator it;
	
	dset = new DisjointSetByRankWPC(r*c);
	for(int i=0; i<r*c; ++i){

		if(goals[i]==20 and board[i]!='*' and dset->Find(i) == i){
			num = get_connected_cells(i, i, dset);
			if(num>=5){
				printf("SCORE %d %d", i/c, i%c);
				delete dset;
				return;
			}
		}
	}

	delete dset;
	int index2;
	find_swap(index, index2);

	printf("SWAP %d %d %d %d\n",index/c, index%c, index2/c, index2%c);

}

int Superball::get_connected_cells(int s, int index, DisjointSetByRankWPC* dset, bool flag){


	bool flags[4] = {index/c>0, index%c>0, index/c<r-1, index%c<c-1};
	int indexes[4] = {index-c, index-1, index+c, index+1};

	int ret_num;
	if(flag){
		ret_num = goals[index]+1;
	}else{
		ret_num = 1;
	}	
	
	for(int i=0; i<4; ++i){

		if(indexes[i]!=s && flags[i] && board[indexes[i]]==board[s] & dset->Find(indexes[i])==indexes[i]){

			dset->Union(indexes[i], s);
			ret_num += get_connected_cells(s, indexes[i], dset, flag);

		}
	}
	return ret_num;


}

void Superball::find_swap(int& index, int& index2){

	int score, temp_score, num1, num2;
	dset = new DisjointSetByRankWPC(r*c);
	for(int i=0; i<r*c; ++i){

		if(islower(board[i]) and dset->Find(i) == i){
			score = get_connected_cells(i, i, dset, true);
			mmap[colors[board[i]]].insert({score, i});
		}
	}

	map<int, multimap<int, int>>::reverse_iterator mit;
	multimap<int, int>::reverse_iterator mit2;
	score = 0;

	for(mit = mmap.rbegin(); mit!= mmap.rend(); ++mit){
		for(mit2 = mit->second.rbegin(); mit2 != mit->second.rend(); ++mit2){
			delete dset;
			dset = new DisjointSetByRankWPC(r*c);
			temp_score = find_max_score(mit2->second, mit2->second, mit2->first, num1, num2);
			if(temp_score>=score){
				score = temp_score;
				index = num1;
				index2 = num2;
			}

		}

	}
}



int Superball::find_max_score(int s, int index, int sscore, int& num1, int& num2){
	
	bool flags[4] = {index/c>0, index%c>0, index/c<r-1, index%c<c-1};
	int indexes[4] = {index-c, index-1, index+c, index+1};
	int score = 0, temp_score = 0, temp_num1=-1, temp_num2=-1;

	for(int i=0; i<4; ++i){

		if(indexes[i]!=s && flags[i] && islower(board[indexes[i]])){
			temp_num1 = indexes[i];
			if(board[temp_num1]==board[s] and dset->Find(temp_num1) == temp_num1){
				dset->Union(temp_num1, s);
				temp_score = find_max_score(s, temp_num1, sscore, temp_num1, temp_num2);
			}
			else

				temp_score = max_score_helper(s, sscore, temp_num1, temp_num2);
		}
		if(score < temp_score){
			num1 = temp_num1;
			num2 = temp_num2;
			score = temp_score;
		}
	
	}

	if(temp_num1 == -1){

		num1 = index;
		num2 = -1;
		score = max_score_helper(s, sscore, num1, num2);
	}
	
	return score;
}

int Superball::max_score_helper(int s, int sscore, int num1, int& num2){

	int temp, temp_num = -1, score = 0, temp_score = 0, temp_sscore;

	DisjointSetByRankWPC* dset2;
	for(int i=0; i<nonempties.size(); ++i){
		
		temp_num = nonempties[i];

		if( temp_num != num1 and board[s] == board[temp_num] and dset->Find(temp_num) != s){
			
			dset2 = new DisjointSetByRankWPC(r*c);
			temp_sscore = get_connected_cells(temp_num, temp_num, dset2, true);
			delete dset2;
			
			dset2 = new DisjointSetByRankWPC(r*c);
			temp = board[num1];
			board[num1] = board[temp_num];
			board[temp_num] = temp;
			
			temp_score = get_connected_cells(s, s,dset2, true)-sscore-temp_sscore;
			if(dset2->Find(temp_num) == temp_num){
				temp_score += get_connected_cells(temp_num, temp_num, dset2, true);
			}
			delete dset2;
			temp = board[num1];
			board[num1] = board[temp_num];
			board[temp_num] = temp;

			if(temp_score >=score){

				score = temp_score;
				num2 = temp_num;
			}
		}
	}
	if(num2 == -1){
		for(int i=0; i<nonempties.size(); ++i){
			if(nonempties[i] != num1){
				num2=nonempties[i];
			}
		}
	}
		

	return score;
}

int main(int argc, char **argv)
{
  
  Superball *s;
  string ss;

  s = new Superball(argc, argv);

  s->play();
		
  return 0;

}
