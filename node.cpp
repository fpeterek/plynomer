//
// Created by Filip Peterek on 2019-04-23.
//

#include "node.hpp"
#include "endpoint.hpp"


Node::Node(const uint64_t id) : NetworkElement(id) { }

void Node::fixMeters() {

    uint64_t ref = meters.front().total();

    for (auto & meter : meters) {
        if (not meter.broken()) {
            ref = meter.total();
        }
    }

    setMeter(ref);

}

bool Node::metersBroken() {

    bool broken = false;

    for (auto & meter : meters) {
        broken = broken or meter.broken();
    }

    return broken;

}

void Node::measureThroughput(const uint64_t throughput) {

    for (auto & meter : meters) {
        meter.increment(throughput);
    }

    if (metersBroken()) {
        fixMeters();
    }

}

void Node::setMeter(const uint64_t value) {

    for (auto & meter : meters) {
        meter.set(value);
    }

}

uint64_t Node::cycle(const uint64_t available) {

    const double modifier = available / (double)totalDesired;

    uint64_t total = 0;

    for (size_t i = 0; i < subnodes.size(); ++i) {
        total += subnodes[i]->cycle(desired[i] * modifier);
    }

    measureThroughput(total);

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

uint64_t Node::getNodeIndex(const uint64_t id) const {

    uint64_t index = 0;

    for (const auto & node : subnodes) {
        if (node->id() == id) {
            return index;
        }
        ++index;
    }

    return -1;

}

void Node::checkNodeIndex(uint64_t index, const std::string & msg) const {

    if (index == -1) {
        throw std::invalid_argument(msg);
    }

}

void Node::checkNodeExists(const uint64_t id, const std::string & msg) const {

    const uint64_t index = getNodeIndex(id);
    checkNodeIndex(index, msg);

}




std::shared_ptr<NetworkElement> Node::getSubnode(uint64_t subnode) {

    const uint64_t index = getNodeIndex(subnode);
    checkNodeIndex(index, "No such node exists.");

    return subnodes[index];

}

void Node::addNode(const uint64_t id) {

    checkNodeExists(id, "Such node already exists.");

    subnodes.emplace_back(std::make_shared<Node>(Node(id)));

}

void Node::addEndpoint(Meter & meter, Customer & customer, const uint64_t id) {

    checkNodeExists(id, "Such node already exists.");

    subnodes.emplace_back(std::make_shared<Endpoint>(Endpoint(meter, customer, id)));

}

void Node::removeNode(const uint64_t id) {

    const uint64_t index = getNodeIndex(id);
    checkNodeIndex(index, "No such node exists.");

    subnodes.erase(subnodes.begin() + index);

}
