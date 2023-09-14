#include <iostream>
#include "solver.h"
#include  <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
#include <random>

Solver::Solver(float crossover, float mutation, unsigned population, unsigned n, std::vector<std::vector<float>> &distance) 
    :dna(crossover, mutation, n, population),
     conditions(distance)
    {std::cout << "hey" << std::endl;}

void Solver::mix(std::vector<std::vector<unsigned>> &vec) {
    std::cout << "mix" << std::endl;
    for (int i = 0; i < dna.population; i++) {
        for (int j = 0; j < dna.n; j++) {
            vec[i][j] = j;
        }
    }
    std::default_random_engine rd;
    std::random_device g;
    for (int i = 0; i < dna.population; i++) {
        std::shuffle(vec[i].begin(), vec[i].end(), rd);
    }
}


int Solver::GetRandomNumber(int min, int max) {
  std::cout << "rand" << std::endl;
  srand(time(NULL));
  int num = min + rand() % (max - min + 1);
  return num;
}

float Solver::sum_vec (std::vector<unsigned> &vec) {
    float sum = 0, n = dna.n;
    for (int i = 0; i < n - 1; i++) {
        sum += sqrt((conditions.distance[vec[i]][0] - conditions.distance[vec[i + 1]][0]) * (conditions.distance[vec[i]][0] - conditions.distance[vec[i + 1]][0]) + (conditions.distance[vec[i]][1] - conditions.distance[vec[i + 1]][1]) * (conditions.distance[vec[i]][1] - conditions.distance[vec[i + 1]][1])); 
    }
    sum += sqrt((conditions.distance[vec[0]][0] - conditions.distance[vec[n - 1]][0]) * (conditions.distance[vec[0]][0] - conditions.distance[vec[n - 1]][0]) + (conditions.distance[vec[0]][1] - conditions.distance[vec[n - 1]][1]) * (conditions.distance[vec[0]][1] - conditions.distance[vec[n - 1]][1])); 
    return sum;
}

std::vector<unsigned> Solver::crossover(std::vector<unsigned> &parent1, std::vector<unsigned> &parent2) {
    std::cout << "cros" << std::endl;
    std::vector<unsigned> son (dna.n, 0);
    unsigned n = son.size();
    std::vector<bool> in_or_not (n, 0);
    std::vector<unsigned> leftovers;
    for (int i = n/3; i < n*2/3; i++) {
        son[i] = parent1[i];
        in_or_not[parent1[i]] = 1;
    }
    for (int i = 0; i < n/3 - 1; i++) {
        if (!in_or_not[parent2[i]]) {son[i] = parent2[i];  in_or_not[parent2[i]] = 1;}
        else 
            in_or_not[parent2[i]] = 2;
    }
        for (int i = n*2/3; i < n; i++) {
        if (!in_or_not[parent2[i]]) {son[i] = parent2[i];  in_or_not[parent2[i]] = 1;}
        else 
            leftovers.push_back(parent2[i]);
    }
    int i = 0;
    while (!leftovers.empty()) {
        if (son[i] == 0) {son[i] = leftovers.back(); leftovers.pop_back();}
    }
    return son;
}

void Solver::pairing(std::vector<std::vector<unsigned>> &pairs) {
    std::cout << "pairing" << std::endl;
    int j;
    for (int i = 0; i < dna.population; i++) {
        pairs[i][0] = GetRandomNumber(int((1 - dna.crossover) * dna.population), dna.population - 1); /////////////////
        j = GetRandomNumber(int((1 - dna.crossover) * dna.population), dna.population - 1);
        while (pairs[i][0] == j){
            j =  GetRandomNumber(int((1 - dna.crossover) * dna.population), dna.population - 1);
        }
        pairs[i][1] = j;
    }
}

void Solver::selection_recombination(unsigned &iter) {
    if (iter > 10) return;
     std::cout << "selecreco" <<" " << iter << std::endl;
    iter++;
    unsigned k;
    std::sort(dna.dad_son.begin(), dna.dad_son.end(), [this](std::vector<unsigned> &a, std::vector<unsigned> &b) { return sum_vec(a) < sum_vec(b);});
    if (dna.path < dna.dad_son[dna.population - 1]) dna.path = dna.dad_son[dna.population - 1];
    k = dna.crossover * dna.n;
    std::vector<std::vector<unsigned>> pairs (dna.n, std::vector<unsigned>(2, 0));

    for (int i = 0; i < int(dna.population * (1 - dna.crossover)); i++) {
        dna.dad_son[i] = crossover(dna.dad_son[pairs[i][0]], dna.dad_son[pairs[i][1]]);
    }
    selection_recombination(iter);
}


void Solver::solve() {
    std::cout << "hello10" << std::endl;
    mix(dna.dad_son);
    unsigned iter = 0;
    selection_recombination(iter);
}