//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_ENDPOINT_HPP
#define PLYNOMER_ENDPOINT_HPP


#include "meter.hpp"
#include "network_element.hpp"
#include "customer.hpp"


class Endpoint : NetworkElement {

    Meter & meter;
	Customer & customer;

	uint64_t _throughput = 0;

public:

    virtual void changeThroughput(const uint64_t newThroughput);

    Endpoint(Meter & meter, Customer & customer, const uint64_t id);


};


#endif //PLYNOMER_ENDPOINT_HPP
