//
// Created by Filip Peterek on 2019-04-24.
//

#ifndef PLYNOMER_NETWORK_ELEMENT_HPP
#define PLYNOMER_NETWORK_ELEMENT_HPP


#include <cstdint>


class NetworkElement {

protected:

public:

    virtual uint64_t currentThroughput() const;
    virtual uint64_t desiredThroughput() const;
    uint64_t maxThroughput() const;
    void setMaxThroughput(const uint64_t newMax);

};


#endif //PLYNOMER_NETWORK_ELEMENT_HPP
