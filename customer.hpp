//
// Created by Filip Peterek on 2019-04-26.
//

#ifndef PLYNOMER_CUSTOMER_HPP
#define PLYNOMER_CUSTOMER_HPP

#include <string>

#include "meter.hpp"
#include "address.hpp"


class Customer {

        const Address _address;
        Meter _meter;
        const uint64_t _maxPrice;

        public:

        Customer(const std::string & address, uint64_t maxPrice = 15);
        Meter & meter();
        const Address & address() const;
        bool acceptsPrice(uint64_t price);

};


#endif //PLYNOMER_CUSTOMER_HPP
