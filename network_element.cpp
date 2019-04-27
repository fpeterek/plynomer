//
// Created by Filip Peterek on 2019-04-24.
//

#include "network_element.hpp"

uint64_t NetworkElement::maxThroughput() const {
    return _maxThroughput;
}

void NetworkElement::setMaxThroughput(const uint64_t newMax) {
    _maxThroughput = newMax;
}

uint64_t NetworkElement::id() const {
    return _id;
}
