//
// Created by Filip Peterek on 2019-04-23.
//

#include <iostream>
#include "node.hpp"
#include "endpoint.hpp"


Node::Node(const uint64_t id) : NetworkElement(id) { }

void Node::fixMeters() {

    uint64_t ref = _meters.front().total();

    for (auto & meter : _meters) {
        if (not meter.broken()) {
            ref = meter.total();
        }
    }

    setMeter(ref);

}

bool Node::metersBroken() {

    bool broken = false;

    for (auto & meter : _meters) {
        broken = broken or meter.broken();
    }

    return broken;

}

bool Node::meterBroken() {


    for (auto & meter : _meters) {
        if (not meter.broken()) {
            return false;
        }
    }

    return true;

}

void Node::measureThroughput(const uint64_t throughput) {

    for (auto & meter : _meters) {
        meter.increment(throughput);
    }

    if (metersBroken()) {
        fixMeters();
    }

}

void Node::setMeter(const uint64_t value) {

    for (auto & meter : _meters) {
        meter.set(value);
    }

}

uint64_t Node::cycle(const uint64_t available) {

    const double modifier = available / (double)_totalDesired;

    uint64_t total = 0;

    for (size_t i = 0; i < _subnodes.size(); ++i) {
        total += _subnodes[i]->cycle(_desired[i] * modifier);
    }

    measureThroughput(total);

    return total;

}

uint64_t Node::currentThroughput() const {

    uint64_t total = 0;

    for (const auto & subnode : _subnodes) {
        total += subnode->currentThroughput();
    }

    return total;

}

uint64_t Node::desiredThroughput() {

    _desired.clear();
    _desired.reserve(_subnodes.size());

    _totalDesired = 0;

    for (auto & subnode : _subnodes) {

        const uint64_t des = subnode->desiredThroughput();
        _desired.emplace_back(des);
        _totalDesired += des;

    }

    return _totalDesired;

}

uint64_t Node::total() const {

    uint64_t total = 0;

    for (const auto & subnode : _subnodes) {
        total += subnode->total();
    }

    return total;

}

size_t Node::subnodes() {
    return _subnodes.size();
}

uint64_t Node::getNodeIndex(const uint64_t id) const {

    uint64_t index = 0;

    for (const auto & node : _subnodes) {
        if (node->id() == id) {
            return index;
        }
        ++index;
    }

    return -1;

}

bool Node::nodeExists(uint64_t id) const {
    return getNodeIndex(id) != -1;
}

void Node::checkNodeIndex(uint64_t index, const std::string & msg) const {

    if (index == -1) {
        throw std::invalid_argument(msg);
    }

}

void Node::checkNodeExists(const uint64_t id, const std::string & msg) const {

    if (not nodeExists(id)) {
        throw std::invalid_argument(msg);
    }

}

void Node::checkNodeDoesntExist(uint64_t id, const std::string & msg) const {

    if (nodeExists(id)) {
        throw std::invalid_argument(msg);
    }

}

std::shared_ptr<NetworkElement> Node::getSubnode(uint64_t subnode) {

    const uint64_t index = getNodeIndex(subnode);
    checkNodeIndex(index, "No such node exists.");

    return _subnodes[index];

}

void Node::addNode(const uint64_t id) {

    checkNodeDoesntExist(id, "Such node already exists.");
    _subnodes.emplace_back(std::make_shared<Node>(id));

}

void Node::addEndpoint(Customer & customer, const uint64_t id) {

    checkNodeDoesntExist(id, "Such node already exists.");
    std::shared_ptr<NetworkElement> ptr = std::make_shared<Endpoint>(customer, id);
    _subnodes.emplace_back(ptr);

}

void Node::removeNode(const uint64_t id) {

    const uint64_t index = getNodeIndex(id);
    checkNodeIndex(index, "No such node exists.");

    _subnodes.erase(_subnodes.begin() + index);

}

void Node::print(std::ostream & os, const uint64_t depth) const {

    os << indent(depth) << _id << "   Node" << "\n";
    for (const auto & sub : _subnodes) {
        sub->print(os, depth + 1);
    }

}

bool Node::isEndpoint() const {
    return false;
}
