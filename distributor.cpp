//
// Created by Filip Peterek on 2019-04-26.
//

#include "distributor.hpp"
#include "meter.hpp"
#include "customer.hpp"
#include "node.hpp"

#include <numeric>
#include <iostream>


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

uint64_t Distributor::maxOutput() {
    return _maxOutput;
}

void Distributor::changeMaxOutput(const uint64_t newOutput) {
    _maxOutput = newOutput;
}

std::shared_ptr<NetworkElement> Distributor::getNode(const Address & address) {

    return getParentFor(address)->getSubnode(address.back());

}

std::shared_ptr<NetworkElement> Distributor::getParentFor(const Address & address) {

    auto it = address.begin();
    std::shared_ptr<NetworkElement> node = mainNode;

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
    const uint64_t consumed = mainNode->cycle(produced);

    _desiredLastDay += desired;
    _producedLastDay += produced;
    _consumedLastDay += consumed;

    _totalDistributed += consumed;
    _currentOutput = consumed;

}

void Distributor::advanceOneDay() {

    for (uint8_t i = 0; i < 24; ++i) {
        uint64_t des = getDesired();
        distribute(des);
        _totalMeasured = measure();
    }

}

void Distributor::addNode(const Address & address) {

    std::shared_ptr<NetworkElement> parent = getParentFor(address);
    parent->addNode(address.back());

}

void Distributor::addEndpoint(const Address & address, Customer & customer) {

    std::shared_ptr<NetworkElement> parent = getParentFor(address);
    parent->addEndpoint(customer, address.back());

}

void Distributor::removeNode(const Address & address) {

    std::shared_ptr<NetworkElement> parent = getParentFor(address);
    parent->removeNode(address.back());

}

uint64_t Distributor::lossInUnits() {
    return _totalDistributed - _totalMeasured;
}

uint64_t Distributor::desiredLastDay() {
    return _desiredLastDay;
}

uint64_t Distributor::producedLastDay() {
    return _producedLastDay;
}

uint64_t Distributor::consumedLastDay() {
    return _consumedLastDay;
}

Distributor::Distributor(uint64_t maxOutput) : _maxOutput(maxOutput) {
    mainNode = std::make_shared<Node>(0);
}
