//
// Created by Filip Peterek on 2019-04-24.
//

#ifndef PLYNOMER_NETWORK_ELEMENT_HPP
#define PLYNOMER_NETWORK_ELEMENT_HPP


#include <cstdint>
#include <memory>
#include "meter.hpp"
#include "customer.hpp"


class NetworkElement {

    uint64_t _maxThroughput = 0;

protected:

    const uint64_t _id;

public:

    /* Represents one cycle                                                   */
    /* Takes one parameter, which represents how many resources are available */
    /* Returns how much was actually consumed                                 */
    virtual uint64_t cycle(const uint64_t available);
    virtual uint64_t currentThroughput() const;
    virtual uint64_t desiredThroughput() const;
    virtual uint64_t total() const;
    virtual std::shared_ptr<NetworkElement> getSubnode(uint64_t subnode);
    virtual void addNode(const uint64_t id);
    virtual void addEndpoint(Meter & meter, Customer & customer, const uint64_t id);
    virtual void removeNode(const uint64_t id);

    uint64_t maxThroughput() const;
    uint64_t id() const;
    void setMaxThroughput(const uint64_t newMax);

    NetworkElement(const uint64_t id);

};


#endif //PLYNOMER_NETWORK_ELEMENT_HPP
