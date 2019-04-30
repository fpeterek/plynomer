//
// Created by Filip Peterek on 2019-04-23.
//

#include "endpoint.hpp"
#include "random.hpp"


Endpoint::Endpoint(Meter & meter, Customer & customer, const uint64_t id)
    : NetworkElement(id), meter(meter), customer(customer) { }

uint64_t Endpoint::cycle(const uint64_t available) {
    _throughput = available;
    changeDesired();
    meter.increment(available);
    return available;
}

uint64_t Endpoint::currentThroughput() const {
    return _throughput;
}

void Endpoint::changeDesired() {

    const uint64_t min = _desired * 0.6;
    // +4 so there is always room to increase desired throughput
    // And avoid getting stuck on 0
    const uint64_t max = _desired * 1.4 + 4;

    _desired = Random::randInt(min, max);

}

uint64_t Endpoint::desiredThroughput() {
    return _desired;
}

uint64_t Endpoint::total() const {
    return meter.total();
}

std::shared_ptr<NetworkElement> Endpoint::getSubnode(uint64_t subnode) {
    return std::shared_ptr<NetworkElement>();
}

void Endpoint::addNode(const uint64_t) {
    throw std::runtime_error("Cannot add subnodes to an endpoint");
}

void Endpoint::addEndpoint(Meter &, Customer &, const uint64_t) {
    throw std::runtime_error("Cannot add subnodes to an endpoint");
}

void Endpoint::removeNode(const uint64_t) {
    throw std::runtime_error("Cannot remove subnodes from an endpoint");
}
