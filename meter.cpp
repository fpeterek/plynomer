//
// Created by Filip Peterek on 2019-04-23.
//

#include "meter.hpp"
#include "random.hpp"
#include "config.hpp"


void Meter::breakFor(const uint64_t hours) {
    _brokenFor = hours;
}

void Meter::fix() {
    --_brokenFor;
}

void Meter::randomlyBreak() {

    if (broken()) {
        return;
    }

    const uint64_t rand = Random::randInt(0, 99);

    if (rand < Config::meterChanceToBreak) {
        breakFor(Random::randInt(1, 48));
    }

}

uint64_t Meter::total() const {
    return _total;
}

void Meter::reset() {
    _total = 0;
    randomlyBreak();
}

void Meter::set(const uint64_t newValue) {
    _total = newValue;
    randomlyBreak();
}

void Meter::increment(const uint64_t inc) {

    if (broken()) { return fix(); }
    _total += inc;
    randomlyBreak();

}

bool Meter::broken() const {
    return _brokenFor;
}

