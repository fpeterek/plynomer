#include <iostream>
#include <array>

// #include "address.hpp"
#include "meter.hpp"
#include "random.hpp"

int main() {

    std::cout << "Hello, world" << std::endl;
    std::array<Meter, 3> meters;

    for (auto & m : meters) {
        m.increment(Random::randInt(100, 1000));
    }

    for (const auto & m : meters) {
        std::cout << m.total() << std::endl;
    }



}