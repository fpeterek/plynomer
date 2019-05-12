//
// Created by Filip Peterek on 2019-04-23.
//

#include <iostream>
#include "endpoint.hpp"
#include "random.hpp"
#include "config.hpp"


Endpoint::Endpoint(Customer & customer, const uint64_t id)
    : NetworkElement(id), customer(customer) {
    // Calculate desired value based off of an initial basic value
    _desired = Config::initialDesired;
    changeDesired();
}

uint64_t Endpoint::cycle(const uint64_t available) {

    if (not _desired) {
        changeDesired();
        return 0;
    }

    const uint64_t consumed = Random::randInt(available / 2, available);

    _throughput = consumed;
    customer.meter().increment(consumed);

    changeDesired();

    return consumed;

}

uint64_t Endpoint::currentThroughput() const {
    return _throughput;
}

void Endpoint::changeDesired() {

    const uint64_t min = _desired * 0.6;
    // +4 so there is always room to increase desired throughput
    // And avoid getting stuck on 0
    const uint64_t max = std::min(_desired * 1.4 + 2, (double)Config::maxConsumption);

    _desired = Random::randInt(min, max);

}

bool Endpoint::meterBroken() {
    return customer.meter().broken();
}

uint64_t Endpoint::desiredThroughput() {
    return _desired;
}

uint64_t Endpoint::total() const {
    return customer.meter().total();
}

std::shared_ptr<NetworkElement> Endpoint::getSubnode(uint64_t subnode) {
    return std::shared_ptr<NetworkElement>();
}

void Endpoint::setMeter(uint64_t value) {
    customer.meter().set(value);
}

void Endpoint::addNode(const uint64_t) {
    throw std::runtime_error("Cannot add subnodes to an endpoint");
}

void Endpoint::addEndpoint(Customer &, const uint64_t) {
    throw std::runtime_error("Cannot add subnodes to an endpoint");
}

void Endpoint::removeNode(const uint64_t) {
    throw std::runtime_error("Cannot remove subnodes from an endpoint");
}

size_t Endpoint::subnodes() {
    return 0;
}

void Endpoint::print(std::ostream & os, uint64_t depth) const {
    os << indent(depth) << _id << "   Endpoint" << "\n";
}

bool Endpoint::isEndpoint() const {
    return true;
}
