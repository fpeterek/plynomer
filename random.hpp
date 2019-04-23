//
// Created by fpeterek on 23.4.19.
//

#ifndef PLYNOMER_RANDOM_HPP
#define PLYNOMER_RANDOM_HPP


#include <random>

class Random {

    static std::mt19937_64 rand;

public:

    static uint64_t randInt(const uint64_t min, const uint64_t max);

};


#endif //PLYNOMER_RANDOM_HPP
