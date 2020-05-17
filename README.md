# Juniper Green Game

The Juniper Green game is a two player game.  
The players alternatively choose a number between 1 and a fixed limit.  
Each number must be a factor or a multiple of the previous one and
they can only be picked once.
The first player that can't choose a number loose.  
Example of a game (limit=20):  
3 - 6 - 2 - 18 - 9 - 1 - 15 - 5 - 10 - 20 - 4 - 8 - 16

The goal here is to find the longuest sequence for several limits.  

## Backtracking method
The classic back-track algorithm that test all possibilities and save the best.  
At each step, the number added is in the factors and multiples of the previous one (without being present is the sequence).  
Since the time increases exponentially with the limit of the sequence, 
the solver works in steps. It finds all solutions starting by 2, then the solutions starting by 3... and merge the temporary files at the end.

## Nested for-loops method
todo
