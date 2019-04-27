//
// Created by Filip Peterek on 2019-04-26.
//

#include "distributor.hpp"
#include "meter.hpp"
#include "customer.hpp"

#include <numeric>


uint64_t Distributor::measure() {
    return mainNode->total();
}

uint64_t Distributor::totalDistributed() {
    return _totalDistributed;
}

uint64_t Distributor::totalMeasured() {
    return _totalMeasured;
}

uint64_t Distributor::currentOutput() {
    return _currentOutput;
}

uint64_t Distributor::expectedRevenue() {
    return _totalDistributed * _pricePerUnit;
}

uint64_t Distributor::actualRevenue() {
    return _totalMeasured * _pricePerUnit;
}

uint64_t Distributor::price() {
    return _pricePerUnit;
}

uint64_t Distributor::maxOutput() {
    return _maxOutput;
}

uint64_t Distributor::desired() {
    return _desired;
}

void Distributor::changeMaxOutput(const uint64_t newOutput) {
    _maxOutput = newOutput;
}

std::shared_ptr<NetworkElement> Distributor::getNode(const Address & address) {

    return getParentFor(address)->getSubnode(address.back());

}

std::shared_ptr<NetworkElement> Distributor::getParentFor(const Address & address) {

    auto it = address.begin();
    auto node = mainNode;

    while (it != (address.end() - 1)) {
        node = node->getSubnode(*(it++));
    }

    return node;

}

uint64_t Distributor::getDesired() {
    return mainNode->desiredThroughput();
}

void Distributor::distribute(const uint64_t desired) {

    const uint64_t produced = std::min(desired, _maxOutput);

    mainNode->cycle(produced);

    _totalDistributed += produced;
    _currentOutput = produced;

}

void Distributor::update() {

    _desired = getDesired();
    distribute(_desired);
    _totalMeasured = measure();

}

void Distributor::updatePrice(const uint64_t newPrice) {
    _pricePerUnit = newPrice;
}

void Distributor::addNode(const Address & address) {

    auto parent = getParentFor(address);
    parent->addNode(address.back());

}

void Distributor::addEndpoint(const Address & address, Meter & meter, Customer & customer) {

    auto parent = getParentFor(address);
    parent->addEndpoint(meter, customer, address.back());

}

void Distributor::removeNode(const Address & address) {

    auto parent = getParentFor(address);
    parent->removeNode(address.back());

}
