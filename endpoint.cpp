//
// Created by Filip Peterek on 2019-04-23.
//

#include "endpoint.hpp"
#include "random.hpp"


Endpoint::Endpoint(Customer & customer, const uint64_t id)
    : NetworkElement(id), meter(customer.meter()), customer(customer) { }

uint64_t Endpoint::cycle(const uint64_t available) {

    const uint64_t consumed = Random::randInt(available / 2, available);

    _throughput = consumed;
    meter.increment(consumed);

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
    const uint64_t max = _desired * 1.4 + 4;

    _desired = Random::randInt(min, max);

}

bool Endpoint::meterBroken() {
    return meter.broken();
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

void Endpoint::setMeter(uint64_t value) {
    meter.set(value);
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
