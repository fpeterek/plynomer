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
#include "meter.hpp"
#include "network_element.hpp"


class Node : NetworkElement {

    std::vector<std::shared_ptr<NetworkElement>> subnodes;

public:

    Node(const uint64_t id);

};


#endif //PLYNOMER_NODE_HPP
