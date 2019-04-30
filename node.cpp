//
// Created by Filip Peterek on 2019-04-23.
//

#include "node.hpp"


Node::Node(const uint64_t id) : NetworkElement(id) { }

uint64_t Node::cycle(uint64_t available) {

    const double modifier = available / (double)totalDesired;

    uint64_t total = 0;

    for (size_t i = 0; i < subnodes.size(); ++i) {
        total += subnodes[i]->cycle(desired[i] * modifier);
    }

    return total;

}

uint64_t Node::currentThroughput() const {

    uint64_t total = 0;

    for (const auto & subnode : subnodes) {
        total += subnode->currentThroughput();
    }

    return total;

}

uint64_t Node::desiredThroughput() {

    desired.clear();
    desired.reserve(subnodes.size());

    totalDesired = 0;

    for (auto & subnode : subnodes) {

        const uint64_t des = subnode->desiredThroughput();
        desired.emplace_back(des);
        totalDesired += des;

    }

    return totalDesired;

}

uint64_t Node::total() const {
    return 0;
}

std::shared_ptr<NetworkElement> Node::getSubnode(uint64_t subnode) {
    return std::shared_ptr<NetworkElement>();
}

void Node::addNode(uint64_t id) {

}

void Node::addEndpoint(Meter & meter, Customer & customer, uint64_t id) {

}

void Node::removeNode(uint64_t id) {

}
