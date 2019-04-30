//
// Created by Filip Peterek on 2019-04-23.
//

#include "meter.hpp"
#include "random.hpp"

void Meter::breakFor(const uint64_t hours) {
    _brokenFor = hours;
}

void Meter::randomlyBreak() {

    uint64_t rand = Random::randInt(0, 99);

    if (rand < _chanceToBreak) {
        breakFor(Random::randInt(1, 48));
    }

}

uint64_t Meter::total() const {
    return _total;
}

void Meter::reset() {

    randomlyBreak();
    _total = 0;

}

void Meter::set(const uint64_t newValue) {

    randomlyBreak();
    _total = newValue;

}

void Meter::increment(const uint64_t inc) {

    randomlyBreak();
    if (broken()) { return 0; }
    _total += inc;

}

bool Meter::broken() const {
    return not _brokenFor;
}

