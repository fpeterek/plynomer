//
// Created by fpeterek on 23.4.19.
//

#include "random.hpp"

std::mt19937_64 Random::rand = std::mt19937_64(std::random_device()());

uint64_t Random::randInt(const uint64_t min, const uint64_t max) {

    std::uniform_int_distribution<uint64_t> dist(min, max);
    return dist(rand);

}
