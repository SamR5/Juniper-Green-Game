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
the solver works in steps. It finds all solutions starting by 2, then the solutions starting by 3... and merge the temporary files at the end (allow to quit and restart the program).

## Nested for-loops method
todo

## Optimizations
 1. The solutions cannot have more than one prime superior to the limit/2+1.  
    For example with a limit of 20 (primes > limit/2+1 are 11, 13, 17 and 19)   
    If the 11 is at the start we have 11 - 1 - (13 or 17 or 19). The length is 3.  
    If it is inside the sequence we have ... - 1 - 11. So it stops the sequence.  
    Thus we keep the first prime > limit/2+1 for the calculations. The others are added after by copying solutions containing this prime.  

 2. The maximal length of a sequence is: limit - (amount of primes over limit/2+1) + 1.

 3. The optimal solutions cannot begin with 1 because 1 can be preceded by every number. 
