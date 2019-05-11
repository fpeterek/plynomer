//
// Created by Filip Peterek on 2019-04-24.
//

#ifndef PLYNOMER_NETWORK_ELEMENT_HPP
#define PLYNOMER_NETWORK_ELEMENT_HPP


#include <cstdint>
#include <sstream>
#include <memory>
#include "meter.hpp"
#include "customer.hpp"


class NetworkElement {

    uint64_t _maxThroughput = 0;

protected:

    const uint64_t _id;

    static std::string indent(uint64_t depth);

public:

    /* Represents one cycle                                                   */
    /* Takes one parameter, which represents how many resources are available */
    /* Returns how much was actually consumed                                 */
    virtual uint64_t cycle(uint64_t available) = 0;
    virtual uint64_t currentThroughput() const = 0;
    virtual uint64_t desiredThroughput() = 0;
    virtual uint64_t total() const = 0;
    virtual std::shared_ptr<NetworkElement> getSubnode(uint64_t subnode) = 0;
    virtual void addNode(uint64_t id) = 0;
    virtual void addEndpoint(Customer & customer, uint64_t id) = 0;
    virtual void removeNode(uint64_t id) = 0;
    virtual void setMeter(uint64_t value) = 0;
    virtual void print(std::ostream & os, uint64_t depth) const = 0;
    virtual bool meterBroken() = 0;
    virtual bool isEndpoint() const = 0;

    virtual size_t subnodes() = 0;

    uint64_t maxThroughput() const;
    uint64_t id() const;
    void setMaxThroughput(uint64_t newMax);

    explicit NetworkElement(uint64_t id);

};


#endif //PLYNOMER_NETWORK_ELEMENT_HPP
