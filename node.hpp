//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_NODE_HPP
#define PLYNOMER_NODE_HPP


#include <cstdint>
#include "meter.hpp"


class Node : public Meter {
public:
    void update() override;

    void changeThroughput(const uint64_t newThroughput) override;

    uint64_t throughput() override;

    uint64_t total() override;

private:

    std::vector<std::shared_ptr<Meter>> subnodes;

public:



};


#endif //PLYNOMER_NODE_HPP
