//
// Created by Filip Peterek on 2019-04-26.
//

#ifndef PLYNOMER_DISTRIBUTOR_HPP
#define PLYNOMER_DISTRIBUTOR_HPP


#include <cstdint>

#include "address.hpp"
#include "network_element.hpp"


class Distributor {

    uint64_t _currentOutput;
    uint64_t _totalDistributed;
    uint64_t _totalMeasured;
    uint64_t _pricePerUnit;
    uint64_t _maxOutput;
    uint64_t _desired;

    std::shared_ptr<NetworkElement> mainNode;

    uint64_t measure();

    uint64_t getDesired();

    void distribute(const uint64_t desired);

    std::shared_ptr<NetworkElement> getNode(const Address & address);
    std::shared_ptr<NetworkElement> getParentFor(const Address & address);

public:

    uint64_t totalDistributed();
    uint64_t totalMeasured();
    uint64_t currentOutput();
    uint64_t expectedRevenue();
    uint64_t actualRevenue();
    uint64_t price();
    uint64_t maxOutput();
    uint64_t desired();

    void changeMaxOutput(const uint64_t newOutput);
    void update();
    void updatePrice(const uint64_t newPrice);
    void addNode(const Address & address);
    void addEndpoint(const Address & address, Meter & meter, Customer & customer);
    void removeNode(const Address & address);

};


#endif //PLYNOMER_DISTRIBUTOR_HPP
