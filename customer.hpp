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
        uint64_t _chargedFor = 0;

        public:

        Customer(const std::string & address);
        Meter & meter();
        const Address & address() const;

        friend class CustomerManager;

};


#endif //PLYNOMER_CUSTOMER_HPP
