#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "disjoint.h"
#include <map>

using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
public:
    Superball(int argc, char **argv);
    int swap(int, int, int, int);
    int collect_score(int, int);
    void print(int);
    int r;
    int c;
    int mss;
    int empty;
    int score;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
    
private:
    int get_connected_cells(int, int);
    int update(int);
    void update_score(int, int);
    int check_status();
    void empty_scored(int, int);
    DisjointSetByRankWPC* dset;
    vector<int> empties;
    vector<char> cur_color;
    
};

void usage(const char *s)
{
    fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
    if (s != NULL) fprintf(stderr, "%s\n", s);
    exit(1);
}

Superball::Superball(int argc, char **argv):score(0)
{
    int i, j;
    string s;
    
    if (argc != 5) usage(NULL);
    
    if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
    if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
    if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");
    
    colors.resize(256, 0);
    empties.resize(r*c, 0);
    
    for (i = 0; i < strlen(argv[4]); i++) {
        if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
        if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
        if (colors[argv[4][i]] != 0) usage("Duplicate color");
        colors[argv[4][i]] = 2+i;
        colors[toupper(argv[4][i])] = 2+i;
        cur_color.push_back(argv[4][i]);
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
            if (board[i*c+j] == '.') {
                empties[empty] = i*c+j;
                empty++;
            }
            if (board[i*c+j] == '*') {
                empties[empty] = i*c+j;
                empty++;
            }
            
            if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
                goals[i*c+j] = 1;
                board[i*c+j] = tolower(board[i*c+j]);
            }
        }
    }
}



int Superball::swap(int row1, int col1, int row2, int col2){
    
    if(row1 >= r or col1 >= c or row2 >= r or col2 >= c){
        
        printf("invalid input: row < %d col < %d\n", r, c);
        return 0;
        
    }
    int index1 = row1*c+col1, index2 = row2*c+col2;
    
    if(board[index1] == '.' or board[index1] == '*' or board[index2] == '.' or board[index2] == '*'){
        
        printf("invalid input: choose a non-empty cell\n");
        return 0;

    }
    
    int temp = board[index1];
    board[index1] = board[index2];
    board[index2] = temp;
    
    return update(5);
    
}

int Superball::check_status(){
    
    dset = new DisjointSetByRankWPC(r*c);
    
    for(int i=0; i<r; ++i){
        for(int j=0; j<c; ++j){
            if(goals[i*c+j] == 1 && board[i*c+j] != '*'&& dset->Find(i*c+j) == i*c+j){
                
                int cell_num = get_connected_cells(i*c+j, i*c+j);
                if(cell_num >= 5){
                    delete dset;
                    return 0;
                }
            }
        }
    }
    delete dset;

    return 1;
}


int Superball::update(int count){
    
    if(empty < count){
        
        if(check_status()){
            print(1);
            printf("Game over.  Final score = %d\n", score);
            return 1;
        }else{
            return 2;
        }
    }
    
    int index;

    while(count != 0){
        
        index = rand()%empty;
        board[empties[index]] = cur_color[rand()%cur_color.size()];
        cout<<empties[index]/c<<' '<<empties[index]%c<<' '<<(char)board[empties[index]]<<endl;
        -- empty;
        empties[index] = empties[empty];
        -- count;
    }
    print(0);
    return 0;
}

void Superball::print(int flag){
    
    printf("Empty Cells: %d     Score: %d\n", empty, score);

    for(int i=0; i<r; ++i){
        for(int j=0; j<c; ++j){
            if(goals[i*c+j]){
                cout<<(char)toupper((char)board[i*c+j]);
            }else{
                cout<<(char)board[i*c+j];
            }
        }
        cout<<endl;
    }
    if(!flag){
        printf("Type Return for the next play\n");

    }
}

void Superball::empty_scored(int s, int index){
    
    bool flags[4] = {index/c>0, index%c>0, index/c<r-1, index%c<c-1};
    int indexes[4] = {index-c, index-1, index+c, index+1};

    for(int i=0; i<4; ++i){
        
        if(indexes[i] != s && flags[i] && board[indexes[i]] == board[s]){
            
            if(goals[indexes[i]]){
                board[indexes[i]] = '*';
            }else{
                board[indexes[i]] = '.';
            }
            empties[empty] = indexes[i];
            ++ empty;
            empty_scored(s, indexes[i]);
        }
        
    }
}

        
int Superball::collect_score(int row, int col){
    
    int index = row*c+col;
    
    if(goals[index] != 1 or board[index] == '*'){
        
        printf("Invalid cell\n");
        return 0;
    }
    
    dset = new DisjointSetByRankWPC(r*c);

    int cell_num = get_connected_cells(index, index);
    delete dset;
    if(cell_num >= 5){
        score += cell_num*colors[board[index]];
        empty_scored(index, index);
        board[index] = '*';
        empties[empty] = index;
        ++ empty;
        return update(3);
    }else{
        printf("No score collected\n");
        print(0);
        return 0;
    }
    
}

int Superball::get_connected_cells(int s, int index){
    
    
    bool flags[4] = {index/c>0, index%c>0, index/c<r-1, index%c<c-1};
    int indexes[4] = {index-c, index-1, index+c, index+1};
    int cell_num = 1;
    
    for(int i=0; i<4; ++i){
        
        if(indexes[i] != s && flags[i] && board[indexes[i]] == board[s] && dset->Find(indexes[i]) == indexes[i]){
            
            dset->Union(indexes[i], s);
            cell_num += get_connected_cells(s, indexes[i]);
        }
        
    }
    return cell_num;
}


int main(int argc, char **argv)
{
    Superball *s;
    
    s = new Superball(argc, argv);
    
    s->print(0);

    string action;
    int row1, col1, row2, col2, flag;

    while(cin>>action){
        if(action == "SWAP"){
            cin>>row1>>col1>>row2>>col2;
            printf("Move is: SWAP %d %d %d %d\n", row1, col1, row2, col2);
            flag = s->swap(row1, col1, row2, col2);
            if( flag == 1){
                break;
            }else if(flag == 2){
                s->swap(row2, col2, row1, col1);
                printf("Cannot swap\nCollect score to continue\n");
            }
            
        }else if (action == "SCORE"){
            cin>>row1>>col1;
            printf("Move is: SCORE %d %d\n", row1, col1);
            s->collect_score(row1, col1);
            
        }else{
            printf("You can type two commands:\n\
                        SWAP r1 c1 r2 c2\n\
                        SCORE r c\n");
        }
        
    }
    return 0;
}
