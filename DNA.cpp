#include "DNA.h"
#include <vector>

DNA::DNA(float crossover, float mutation, unsigned n, unsigned population)
    :crossover(crossover),
     mutation(mutation),
     n(n),
     population(population),
     dad_son(population, std::vector<unsigned>(n, 0)),
     path(n, 0)
     {}
