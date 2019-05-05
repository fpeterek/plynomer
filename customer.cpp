//
// Created by Filip Peterek on 2019-04-26.
//

#include "customer.hpp"


Customer::Customer(const std::string & address, const uint64_t maxPrice)
    : _address(address), _maxPrice(maxPrice) { }

Meter & Customer::meter() {
    return _meter;
}

const Address & Customer::address() const {
    return _address;
}

bool Customer::acceptsPrice(const uint64_t price) {
    return price <= _maxPrice;
}
