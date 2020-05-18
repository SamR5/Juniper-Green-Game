/*
Juniper Green Game Solver
Find a sequence from 1 to N where for each number
the next is either a multiple or a factor
*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include "solver.h"

void add_primes_solutions(int sz); // add all solutions that were skipped because in primes > limit
bool is_superior(std::vector<int> A, std::vector<int> B);
void write_step(int sz, int step);
int find_longest(int sz); // find longuest sequence from temp files
int merge_files(int sz); // merge all the temp files of size sz
void remove_temp_files(int sz);
bool step_exists(int sz, int step);
bool size_exists(int sz);


void add_primes_solutions(int sz) {
    std::vector<int> up;
    for (int i=sz/2+1; i<=sz; i++) {
        if (is_prime(i))
            up.push_back(i);
    }
    if (up.size() <= 1)
        return;
    int prime = up[0];
    up.erase(up.begin());
    size_t solSize = solutions.size();
    for (int p : up) {
        for (size_t i=0; i<solSize; i++) {
            if (std::find(solutions[i].begin(), solutions[i].end(), prime) != solutions[i].end()) {
                std::vector<int> v(solutions[i]);
                std::replace(v.begin(), v.end(), prime, p);
                solutions.push_back(v);
            }
        }
    }
}

void write_step(int sz, int step) {
    std::ofstream myfile("results/" +
                         std::to_string(sz) + "_" + std::to_string(step) +
                         ".temp", std::ios::app);
    if (myfile) {
        for (std::vector<int> sol : solutions) {
            for (size_t i=0; i<sol.size(); i++) {
                myfile << sol[i];
                if (i+1!=sol.size())
                    myfile << "-";
            }
            myfile << std::endl;
        }
    }
}

int find_longest(int sz) {
    std::string tempLine;
    int maxLength(0);
    for (int step=0; step<=sz; step++) {
        std::ifstream mystep("results/" + std::to_string(sz) +
                             "_" + std::to_string(step) + ".temp", std::ios::in);
        if (mystep) {
            std::getline(mystep, tempLine);
            int len(std::count_if(tempLine.begin(), tempLine.end(),
                                  [](char n) {return n=='-';}) + 1);
            if (len>maxLength)
                maxLength = len;
        }
    }
    return maxLength;
}

int merge_files(int sz) {
    std::vector<std::string> res;
    int maxLength(find_longest(sz));
    std::string tempLine;
    // get all results of temp files in res
    for (int step=0; step<=sz; step++) {
        std::ifstream mystep("results/" + std::to_string(sz) +
                             "_" + std::to_string(step) + ".temp", std::ios::in);
        if (mystep) {
            std::getline(mystep, tempLine);
            int len(std::count_if(tempLine.begin(), tempLine.end(),
                    [](char n) {return n=='-';})+1);
            if (len<maxLength)
                continue;
            res.push_back(tempLine);
            while (std::getline(mystep, tempLine)) {
                res.push_back(tempLine);
            }
        }
    }
    // write res to file
    std::ofstream myfile("results/" + std::to_string(sz) + ".txt");
    if (myfile) {
        for (std::string s : res)
            myfile << s << std::endl;
    }
    return res.size();
}

void remove_temp_files(int sz) {
    for (int step=0; step<=sz; step++) {
        std::string name = "results/" + std::to_string(sz) +
                           "_" + std::to_string(step) + ".temp";
        std::remove(name.c_str());
    }
}

bool step_exists(int sz, int step) {
    std::string name = "results/" + std::to_string(sz) +
                  "_" + std::to_string(step) + ".temp";
    std::ifstream mystep(name, std::ios::in);
    return !mystep.fail();
}

bool size_exists(int sz) {
    std::string name = "results/" + std::to_string(sz) + ".txt";
    std::ifstream mysize(name, std::ios::in);
    return !mysize.fail();
}

int main() {
    int low, high;
    std::cout << "Lower and upper bound (space separated): ";
    std::cin >> low >> high;
    if (low > high)
        return 0;
    system("mkdir results");
    for (int i=low; i<high+1; i++) {
        if (size_exists(i)) {
            std::printf("Solution for size %i already exists\n", i);
            continue;
        }
        // 1 can always be preceded
        for (int step=2; step<=i; step++) {
            if (step_exists(i, step)) {
                std::printf("Solution for size %i (step %i) already exists\n", i, step);
                continue;
            }
            auto start(std::chrono::high_resolution_clock::now());
            purge();
            initialize(i, step);
            add_one(step);
            add_primes_solutions(i);
            write_step(i, step);
            auto stop(std::chrono::high_resolution_clock::now());
            auto duration(std::chrono::duration_cast<std::chrono::seconds>(stop - start));
            std::printf("Size %d (step %d) : %ds with %zu solutions found\n",
                   i, step, (int)duration.count(), solutions.size());
        }
        int sol(merge_files(i));
        remove_temp_files(i);
        std::printf("Size %i : %i solutions found\n", i, sol);
    }
    return 0;
}
