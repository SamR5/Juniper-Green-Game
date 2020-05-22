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

std::vector<int> get_candidates(int idx) {
    std::vector<int> cand = generalFactMul[myseq[idx-1]];
    for (int i=0; i<length; i++) {
        for (int j=cand.size()-1; j>=0; j--) {
            if (cand[j] == myseq[i]) {
                cand.erase(cand.begin()+j);
                break;
            }
        }
    }
    return cand;
}

void update_candidates(std::vector<int> &cand, int idx) {
    cand = generalFactMul[myseq[idx-1]];
    for (int i=0; i<length; i++) {
        for (int j=cand.size()-1; j>=0; j--) {
            if (cand[j] == myseq[i]) {
                cand.erase(cand.begin()+j);
                break;
            }
        }
    }
}

void iterative() {
    std::vector<std::vector<int>> stack;
    std::vector<int> None(1, -1);
    std::vector<int> candidates = None;
    while (true) {
        if (myseq[length] == 0) {
            if (candidates == None)
                candidates = get_candidates(length);
            if (candidates.empty()) {
                if (stack.empty())
                    return;
                candidates = stack.back();
                stack.pop_back();
                --length;
                myseq[length] = 0;
                continue;
            } else {
                myseq[length] = candidates.back();
                candidates.pop_back();
                stack.push_back(candidates);
                candidates = None;
            }
        }
        ++length;
        if (length == mx) {
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

