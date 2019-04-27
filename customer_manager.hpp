//
// Created by Filip Peterek on 2019-04-26.
//

#ifndef PLYNOMER_CUSTOMER_MANAGER_HPP
#define PLYNOMER_CUSTOMER_MANAGER_HPP


#include <memory>
#include <string>

#include "distributor.hpp"
#include "meter.hpp"
#include "random.hpp"
#include "customer.hpp"

class CustomerManager {

    std::shared_ptr<Distributor> distributor;
    std::vector<Customer> customers;

public:

    void updatePrice(const uint64_t newPrice);
    void updateDistributor(std::shared_ptr<Distributor> dist);

    void addCustomer();
    void removeCustomer(const std::string & address);



};


#endif //PLYNOMER_CUSTOMER_MANAGER_HPP
