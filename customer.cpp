//
// Created by Filip Peterek on 2019-04-26.
//

#include "customer.hpp"


Customer::Customer(const std::string & address)
    : _address(address) { }

Meter & Customer::meter() {
    return _meter;
}

const Address & Customer::address() const {
    return _address;
}
