//
// Created by Filip Peterek on 2019-04-23.
//

#include "node.hpp"

uint64_t Node::total() {

    auto fn = [&](uint64_t acc, std::shared_ptr<Meter> ptr) { return acc + ptr->total() };
    return std::accumulate(subnodes.begin(), subnodes.end(), 0, fn);

}

void Node::update() {

}

void Node::changeThroughput(const uint64_t newThroughput) {
    Meter::changeThroughput(newThroughput);
}

uint64_t Node::throughput() {
    return Meter::throughput();
}
