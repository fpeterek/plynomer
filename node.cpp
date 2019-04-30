//
// Created by Filip Peterek on 2019-04-23.
//

#include "node.hpp"


Node::Node(const uint64_t id) : NetworkElement(id) { }

uint64_t Node::cycle(uint64_t available) {

    uint64_t sum = 0;

    for (auto & subnode : subnodes) {
        sum += subnode->cycle();
    }



}

uint64_t Node::currentThroughput() const {
    return 0;
}

uint64_t Node::desiredThroughput() {
    return 0;
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
