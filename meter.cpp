//
// Created by Filip Peterek on 2019-04-23.
//

#include "meter.hpp"
#include "random.hpp"

void Meter::breakFor(const uint64_t hours) {
    brokenFor = hours * 60;
}

void Meter::randomlyBreak() {

    uint64_t rand = Random::randInt(0, 99);

    if (rand < chanceToBreak) {
        breakFor(Random::randInt(1, 240));
    }

}

uint64_t Meter::total() {
    randomlyBreak();
    return _total;
}

void Meter::reset() {

    randomlyBreak();
    if (broken()) { return; }
    _total = 0;

}

void Meter::set(const uint64_t newValue) {

    randomlyBreak();
    if (broken()) { return; }
    _total = newValue;

}

void Meter::increment(const uint64_t inc) {

    randomlyBreak();
    if (broken()) { return; }
    _total += inc;

}

bool Meter::broken() const {
    return not brokenFor;
}

