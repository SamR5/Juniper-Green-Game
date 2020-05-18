#ifndef SOLVER_H
#define SOLVER_H

#include <vector>


extern int * myseq; // the sequence
extern std::vector<std::vector<int>> solutions; // all solutions found

bool is_prime(int n);

// return factors and multiples of n below lim
std::vector<int> fact_mult(int n, int lim);

// initialize the global variables
void initialize(int limit, int step);

// return a vector of the possibilities for the next turn
// i.e. factors and multiples of last without the ones in the sequence
void next_poss(bool poss[], int const &last);

// adds the next integer to the sequence according to the possibilities
// and backtrack when no possibilities left
void add_one(int const& last);

// empty all global vectors when solving for multiple sizes
// and reset the sequence
void purge();

#endif // SOLVER_H
