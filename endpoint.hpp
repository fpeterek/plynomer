//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_ENDPOINT_HPP
#define PLYNOMER_ENDPOINT_HPP


#include "meter.hpp"


class Endpoint {

    Meter meter;
	
	uint64_t _throughput;

	virtual void changeThroughput(const uint64_t newThroughput);
	virtual uint64_t throughput();

public:
    uint64_t total();


};


#endif //PLYNOMER_ENDPOINT_HPP
