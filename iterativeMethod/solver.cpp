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
std::vector<std::vector<int>> allPoss; // all possibilities for every indexes

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
    std::vector<int> z;
    for (int i=1; i<=limit; i++)
        z.push_back(i);
    generalFactMul.push_back(z);
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

void update_candidates(std::vector<int> *cnd, int idx) {
    int n = myseq[idx-1];
    *cnd = generalFactMul[n];
    for (int i=cnd->size()-1; i>=0; i--) {
        for (int j=0; j<length; j++) {
            if ((*cnd)[i] == *(myseq+j)) {
                cnd->erase(cnd->begin()+i);
                break;
            }
        }
    }
}

void print() {
    for (int i=0; i<length; i++)
        std::cout << myseq[i] << "-";
    std::cout << std::endl;
}

void iterative() {
    allPoss = std::vector<std::vector<int>> (limit, std::vector<int>());
    std::vector<int> none(1, -1);
    int currPoss = 0;
    allPoss[currPoss] = none;
    std::vector<int> *candidates = &allPoss[currPoss];
    while (true) {
        if (myseq[length] == 0) {
            if (*candidates == none) {
                update_candidates(candidates, length);
            }
            if (candidates->empty()) {
                if (allPoss[0].empty()) // 1 because of the steps
                    return;
                candidates->clear();
                candidates = &allPoss[--currPoss];
                myseq[--length] = 0;
                continue;
            } else {
                myseq[length] = candidates->back();
                candidates->pop_back();
                allPoss[++currPoss] = none;
                candidates = &allPoss[currPoss];
            }
        }
        length++;
        if (length==mx) {
            solutions.push_back(std::vector<int>(myseq, myseq+length));
        } else if (length > mx) {
            mx = length;
            solutions.clear();
            solutions.push_back(std::vector<int>(myseq, myseq+length));
        }
    }
}

void purge() {
    myseq = nullptr;
    solutions.clear();
    generalFactMul.clear();
}

