This implements Dijkstra's Algorithm to find the shortes path in a weighted graph. 

Given a text representing a 2D landscape. Each tile has a symbol and can be assigned a specific cost. The task is to help the runner go from cell(x, y) to cell (i, j) with the lowest overall cost

Example input:

6

f 3

g 1

G 2

h 4

m 7

r 5

10 10

G r g g m m m r f m

G g r G G G G m f h

m r f m m f G r h h

G m G f h r g m g g

g g g m h m h f m f

h r g f f f g h r h

m G f r m m G r g f

m r h h h h G m m r

r r g f G r r m f r

G g r g g r h m m r

0 0

7 6

Output:

27

0 0

0 1

0 2

0 3

1 3

1 4

1 5

1 6

2 6

3 6

4 6

5 6

6 6

7 6
