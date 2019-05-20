//
//  sb-analyze.cpp
//  Superball
//
//  Created by Fanli Zhou on 3/28/19.
//  Copyright © 2019 Fanli Zhou. All rights reserved.
//

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
    void analyze_superball();
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
    
private:
    int get_connected_cells(int, int);
    DisjointSetByRankWPC* dset;
    map<int, int> smap;
};

void usage(const char *s)
{
    fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
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
                goals[i*c+j] = 1;
                board[i*c+j] = tolower(board[i*c+j]);
            }
        }
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

void Superball::analyze_superball(){
    
    int i, j;
    dset = new DisjointSetByRankWPC(r*c);
    
    
    for(i=0; i<r; ++i){
        for(j=0; j<c; ++j){

            if(goals[i*c+j] == 1 && board[i*c+j] != '*' && dset->Find(i*c+j) == i*c+j){
                int cell_num = get_connected_cells(i*c+j, i*c+j);
                if(cell_num >= 5){
                    smap[i*c+j] = cell_num;
                }
            }
        }
    }
    printf("Scoring sets:\n");
    
    for(map<int, int>::iterator itr = smap.begin(); itr != smap.end(); ++itr){

            printf("  Size: %2d  Char: %c  Scoring Cell: %d,%d\n", itr->second, (char) board[itr->first], itr->first/c, itr->first%c);

    }
    delete dset;
}

int main(int argc, char **argv)
{
    Superball *s;
    int i;
    int ngoal, tgoal;
    
    s = new Superball(argc, argv);
    
    tgoal = 0;
    ngoal = 0;
    for (i = 0; i < s->r*s->c; i++) {
        if (s->goals[i] && s->board[i] != '*') {
            tgoal += s->colors[s->board[i]];
            ngoal++;
        }
    }
    s->analyze_superball();

    return 0;
}
