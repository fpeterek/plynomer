//
// Created by Filip Peterek on 2019-04-24.
//

#include "network_element.hpp"
#include "config.hpp"


uint64_t NetworkElement::maxThroughput() const {
    return _maxThroughput;
}

void NetworkElement::setMaxThroughput(const uint64_t newMax) {
    _maxThroughput = newMax;
}

std::string NetworkElement::indent(const uint64_t depth) {
    return std::string(depth * Config::spacesToIndent, ' ');
}

uint64_t NetworkElement::id() const {
    return _id;
}

NetworkElement::NetworkElement(const uint64_t id) : _id(id) { }
