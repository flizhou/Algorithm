This implements a bipartite matching using Edmonds-Karp algorithm.

The input to this program is as follows: 

1. The dice available, encoded as described above. 

2. A list words to check if they can be spelled using these dice 

For example, the word "RAGE" may be spelled using 'R' from the "PRR" die, 'A' from the "SAA" die, 'G' from the "ENG" die and 'E' from the "EAE" die. Similarly, "SEEP" may be spelled with 'S' from the "SAA" die, 'E' from the "EAE" die, 'E' from the "ENG" die and 'P' from the "PRR" die. 

However, you cannot spell "PEEN", even though all the letters are there, because you would have to use the "ENG" die for both the 'E' and 'N'.

Example:

UNIX> cat Dice1.txt

ENG

SAA

PRR

EAE

UNIX> cat Words1.txt

RAGE

SEEP

PEEN

GASP

UNIX> worddice Dice1.txt Words1.txt

2,1,0,3: RAGE

1,0,3,2: SEEP

Cannot spell PEEN

0,3,1,2: GASP

UNIX> 
