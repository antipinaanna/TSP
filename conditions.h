#pragma once
#include "vector"


class Conditions {
    public:
        Conditions(std::vector<std::vector<float>> &distance);
        std::vector<std::vector<float>> distance;
};