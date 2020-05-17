#include <iostream>
#include <vector>
#include <algorithm>
#include "solver.h"


std::vector<std::vector<int>> generalFactMul; // all factors and multiples of each number
int * myseq = nullptr; // the sequence
std::vector<std::vector<int>> solutions;
int limit; // limt of the sequence included
int mx; // temporary maximum
int length; // length of the sequence to avoid recalculations


// return factors and multiples n has below lim
std::vector<int> fact_mult(int n, int lim) { // working
    std::vector<int> fm;
    for (int i=1; i<=lim; i++) {
        if (n%i==0 && i!=n) // if factor
            fm.push_back(i);
        if (n*i<=lim && i!=1) // if multiple
            fm.push_back(n*i);
    }
    return fm;
}

void initialize(int lim, int step) {
    limit = lim;
    mx = 0; // max length of the sequence
    myseq = new int [limit] ();
    limit = lim;
    length = 0;
    myseq[0] = step;
    length++;
    

   // generate the factors/multiples of each number
    std::vector<int> emp;
    std::vector<int> f;
    for (int i=1; i<=limit; i++) {
        f = fact_mult(i, limit);
        std::sort(f.begin(), f.end());
        generalFactMul.push_back(f);
    }
}

void next_poss(bool poss[], int const &last) {
    for (size_t i=0; i<generalFactMul[last].size(); i++) {
        poss[generalFactMul[last][i]] = true;
    }
    for (int i=0; i<limit; i++) { // length, to add in arguments
        poss[myseq[i]] = false;
    }
}

void add_one(int const& last) {
    
    bool nextPoss[limit+1];
    for (int i=0; i<limit+1; i++)
        nextPoss[i] = false;
    next_poss(nextPoss, last-1);
    
    for (int i=1; i<=limit; i++) {
        if (nextPoss[i]) {
            myseq[length] = i;
            length++;
            add_one(i);
            
            // after no new possibilities, next poss
            length--;
            myseq[length] = 0;
        }
    }
    if (length > mx) {
        mx = length;
        solutions.clear();
        solutions.push_back(std::vector<int>(myseq, myseq+length)); // faster ??
    } else if (length == mx)
        solutions.push_back(std::vector<int>(myseq, myseq+length));
}

void purge() {
    myseq = nullptr;
    solutions.clear();
    generalFactMul.clear();
}

