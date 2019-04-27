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

        Customer(const std::string & address);
        Customer(const std::string & address, const uint64_t maxPrice);
        Meter & meter();
        bool acceptsPrice(const uint64_t price);

};


#endif //PLYNOMER_CUSTOMER_HPP
