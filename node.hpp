//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_NODE_HPP
#define PLYNOMER_NODE_HPP


#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

#include "meter.hpp"
#include "network_element.hpp"


class Node : NetworkElement {

    std::vector<std::shared_ptr<NetworkElement>> subnodes;
    std::vector<uint64_t> desired;
    uint64_t totalDesired;

    std::array<Meter, 3> meters;

    void measureThroughput(uint64_t throughput);
    bool metersBroken();
    void fixMeters();

    void checkNodeIndex(uint64_t index, const std::string & msg) const;
    void checkNodeExists(uint64_t id, const std::string & msg) const;
    uint64_t getNodeIndex(uint64_t id) const;

public:

    explicit Node(uint64_t id);

    uint64_t cycle(uint64_t available) override;
    uint64_t currentThroughput() const override;
    uint64_t desiredThroughput() override;
    uint64_t total() const override;
    std::shared_ptr<NetworkElement> getSubnode(uint64_t subnode) override;
    void addNode(uint64_t id) override;
    void addEndpoint(Meter & meter, Customer & customer, uint64_t id) override;
    void removeNode(uint64_t id) override;

    void setMeter(uint64_t value) override;
    void checkMeters() override;

};


#endif //PLYNOMER_NODE_HPP
