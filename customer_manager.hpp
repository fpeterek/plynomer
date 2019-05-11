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

    Distributor & distributor;
    std::vector<std::shared_ptr<Customer>> customers;

    uint64_t pricePerUnit = 0;
    uint64_t _totalRevenue = 0;
    uint64_t _revenueLastCycle = 0;

    uint64_t chargeCustomer(Customer & customer);

public:

    explicit CustomerManager(Distributor & dist);

    void updatePrice(uint64_t newPrice);
    void addCustomer(const std::string & address);
    void removeCustomer(const std::string & address);

    uint64_t chargeCustomers();
    uint64_t totalRevenue();
    uint64_t revenueLastCycle();

};


#endif //PLYNOMER_CUSTOMER_MANAGER_HPP
