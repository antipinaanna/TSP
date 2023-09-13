#pragma once
#include <vector>
#include "conditions.h"
#include "DNA.h"

class Solver {
    public:
        Solver(float crossover, float mutation, unsigned population, unsigned n, std::vector<std::vector<float>> &distance);
        void mix(std::vector<std::vector<unsigned>> &vec);
        int GetRandomNumber(int min, int max);
        float sum_vec (std::vector<unsigned> &vec);
        std::vector<unsigned> crossover(std::vector<unsigned> &parent1, std::vector<unsigned> &parent2);
        void pairing(std::vector<std::vector<unsigned>> &pairs);
        void selection_recombination(unsigned &iter);
        void solve();
    private:
        Conditions conditions;
        DNA dna;
};