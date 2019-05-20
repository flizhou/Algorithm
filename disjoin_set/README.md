This implements a Superball game

sb-player.cpp is an interactive play ground

sb-play.cpp is a stupid AI that plays the game

Example:

>sb-player 8 10 5 pbyrg 

You have a 8x10 grid which is the game board. 

Each cell of the game board may be empty or hold a color: 

P - Purple: worth 2 points. 

B - Blue: worth 3 points. 

Y - Yellow: worth 4 points. 

R - Red: worth 5 points. 

G - Green: worth 6 points. 

The board starts with five random colors set. On your turn, you may do one of two things: 

1. You may swap two cells. After the swap, five new random cells will be filled with a random colors. 

2. You may "score" a cell. To score a cell, the cell must be one of the "goal" cells, and there are sixteen of these, in rows 2-5, columns 0, 1, 8 and 9. (Everything is zero indexed). Moreover, there must be at least five touching cells of the same color, one of which must be the goal cell that you want to score. When you score, you get the sum of the cells connected to the cell that you are scoring, and then all of those cells leave the board, and three new random ones are added. 


