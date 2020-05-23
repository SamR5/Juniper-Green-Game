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

std::vector<int> get_candidates(int idx);

void iterative();

// empty all global vectors when solving for multiple sizes
// and reset the sequence
void purge();

#endif // SOLVER_H
