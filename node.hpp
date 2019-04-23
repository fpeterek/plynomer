//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_NODE_HPP
#define PLYNOMER_NODE_HPP


#include <cstdint>
#include <memory>
#include "meter.hpp"


class Node {

    std::vector<std::shared_ptr<Meter>> subnodes;

public:
    void update();
    void changeThroughput(const uint64_t newThroughput);
    uint64_t total();

};


#endif //PLYNOMER_NODE_HPP
