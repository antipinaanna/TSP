#pragma once
#include <vector>

class DNA {
    public:
        DNA (float crossover, float mutation, unsigned n, unsigned population);
        float crossover;
        float mutation;
        unsigned n;
        unsigned population;
        std::vector<std::vector<unsigned>> dad_son;
        std::vector<unsigned> path;
};