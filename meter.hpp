//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_METER_HPP
#define PLYNOMER_METER_HPP

#include <cstdint>

class Meter {

    uint64_t _total = 0;
    uint64_t _brokenFor = 0;
    const uint64_t _chanceToBreak = 1;

    void randomlyBreak();
    void breakFor(uint64_t cycles);

    void fix();

public:
    uint64_t total() const;
    void reset();
    void set(uint64_t newValue);
    void increment(uint64_t inc);
    bool broken() const;

};


#endif //PLYNOMER_METER_HPP
