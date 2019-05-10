//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_ENDPOINT_HPP
#define PLYNOMER_ENDPOINT_HPP


#include "meter.hpp"
#include "network_element.hpp"
#include "customer.hpp"


class Endpoint : public NetworkElement {

	Customer & customer;

	uint64_t _throughput = 0;
	uint64_t _desired = 0;

	void changeDesired();


public:

    uint64_t cycle(uint64_t available) override;
    uint64_t currentThroughput() const override;
    uint64_t desiredThroughput() override;
    uint64_t total() const override;
    std::shared_ptr<NetworkElement> getSubnode(uint64_t subnode) override;
    void addNode(uint64_t id) override;
    void addEndpoint(Customer & customer, uint64_t id) override;
    void removeNode(uint64_t id) override;
    void setMeter(uint64_t value) override;
    bool meterBroken() override;
    size_t subnodes() override;


    Endpoint(Customer & customer, uint64_t id);


};


#endif //PLYNOMER_ENDPOINT_HPP
