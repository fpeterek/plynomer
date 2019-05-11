//
// Created by Filip Peterek on 2019-04-26.
//

#include "customer_manager.hpp"


uint64_t CustomerManager::chargeCustomer(Customer & customer) {

    const uint64_t chargeableAmount = customer._meter.total() - customer._chargedFor;
    const uint64_t priceToPay = chargeableAmount * pricePerUnit;
    customer._chargedFor = customer._meter.total();
    return priceToPay;

}

CustomerManager::CustomerManager(Distributor & dist) : distributor(dist) { }

void CustomerManager::updatePrice(const uint64_t newPrice) {
    pricePerUnit = newPrice;
}

void CustomerManager::addCustomer(const std::string & address) {

    customers.emplace_back(std::make_shared<Customer>(address));
    distributor.addEndpoint(address, *customers.back());

}

void CustomerManager::removeCustomer(const std::string & address) {

    const Address add = address;

    for (uint64_t i = 0; i < customers.size(); ++i) {
        if (customers[i]->address() == add) {
            customers.erase(customers.begin() + i);
        }
    }

    distributor.removeNode(add, false);

}

uint64_t CustomerManager::chargeCustomers() {

    uint64_t totalCharged = 0;

    for (auto & customer : customers) {
        totalCharged += chargeCustomer(*customer);
    }

    _totalRevenue += totalCharged;
    _revenueLastCycle = totalCharged;

    return totalCharged;

}

uint64_t CustomerManager::totalRevenue() {
    return _totalRevenue;
}

uint64_t CustomerManager::revenueLastCycle() {
    return _revenueLastCycle;
}
