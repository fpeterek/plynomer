//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_METER_HPP
#define PLYNOMER_METER_HPP

#include <cstdint>
#include <random>


class Meter {

    uint64_t _total = 0;
    uint64_t brokenFor = 0;
    uint64_t chanceToBreak = 5;

    void randomlyBreak();
    void breakFor(const uint64_t cycles);

public:
    uint64_t total();
    void reset();
    void set(const uint64_t newValue);
    void increment(const uint64_t inc);
    bool broken() const;

};


#endif //PLYNOMER_METER_HPP
