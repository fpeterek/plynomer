//
// Created by Filip Peterek on 2019-04-26.
//

#ifndef PLYNOMER_DISTRIBUTOR_HPP
#define PLYNOMER_DISTRIBUTOR_HPP


#include <cstdint>

#include "address.hpp"
#include "network_element.hpp"


class Distributor {

    uint64_t _currentOutput = 0;
    uint64_t _totalDistributed = 0;
    uint64_t _totalMeasured = 0;
    uint64_t _maxOutput = 0;
    uint64_t _desiredLastDay = 0;
    uint64_t _producedLastDay = 0;
    uint64_t _consumedLastDay = 0;

    std::shared_ptr<NetworkElement> mainNode;

    uint64_t measure();

    uint64_t getDesired();

    void distribute(uint64_t desired);

    std::shared_ptr<NetworkElement> getNode(const Address & address);
    std::shared_ptr<NetworkElement> getParentFor(const Address & address);

public:

    uint64_t totalDistributed();
    uint64_t totalMeasured();
    uint64_t currentOutput();
    uint64_t maxOutput();
    uint64_t desiredLastDay();
    uint64_t producedLastDay();
    uint64_t consumedLastDay();
    uint64_t lossInUnits();

    void changeMaxOutput(uint64_t newOutput);
    void advanceOneDay();
    void addNode(const Address & address);
    void addEndpoint(const Address & address, Meter & meter, Customer & customer);
    void removeNode(const Address & address);

    Distributor(uint64_t maxOutput);

};


#endif //PLYNOMER_DISTRIBUTOR_HPP
