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

bool is_prime(int n) {
    if (n<2 || n==4)
        return false;
    for (int i=2; i<n/2; i++) {
        if (n%i == 0)
            return false;
    }
    return true;
}

std::vector<int> fact_mult(int n, int lim, std::vector<int>& toSkip) {
    std::vector<int> fm;
    for (int i=1; i<=lim; i++) {
        if (std::find(toSkip.begin(), toSkip.end(), i) != toSkip.end())
            continue;
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
    
    // sequence has at most one primes > limit
    std::vector<int> toSkip;
    for (int i=limit/2+1; i<=limit; i++) {
        if (is_prime(i)) {
            toSkip.push_back(i);
        }
    }
    // only the first prime will be used
    if (toSkip.size() > 1) {
        toSkip.erase(toSkip.begin());
    }

    // generate the factors/multiples of each number
    std::vector<int> emp;
    std::vector<int> f;
    for (int i=1; i<=limit; i++) {
        if (std::find(toSkip.begin(), toSkip.end(), i) != toSkip.end()) {
            generalFactMul.push_back(emp);
            continue;
        }
        f = fact_mult(i, limit, toSkip);
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
            length--;
            myseq[length] = 0;
        }
    }
    if (length > mx) {
        mx = length;
        solutions.clear();
        solutions.push_back(std::vector<int>(myseq, myseq+length));
    } else if (length == mx)
        solutions.push_back(std::vector<int>(myseq, myseq+length));
}

void purge() {
    myseq = nullptr;
    solutions.clear();
    generalFactMul.clear();
}

