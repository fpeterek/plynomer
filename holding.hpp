//
// Created by Filip Peterek on 2019-05-11.
//

#ifndef PLYNOMER_HOLDING_HPP
#define PLYNOMER_HOLDING_HPP

#include "customer_manager.hpp"
#include "config.hpp"

class Holding {

    Distributor & distributor;
    CustomerManager & customerManager;

    void increaseProduction();

    uint64_t _desiredLastMonth = 0;
    uint64_t _producedLastMonth = 0;
    uint64_t _consumedLastMonth = 0;
    uint64_t _lossesPrevMonth = 0;

    uint64_t _pricePerUnit;

public:

    Holding(Distributor & distributor, CustomerManager & customerManager);

    void log();
    void checkProductionNeeds();
    void newMonth();

    uint64_t pricePerUnit();
    void setPrice(uint64_t newPrice);

    uint64_t totalLosses();
    uint64_t lossesLastMonth();
    uint64_t totalRevenue();
    uint64_t revenueLastMonth();
    uint64_t producedLastMonth();
    uint64_t desiredLastMonth();
    uint64_t consumedLastMonth();

};


#endif //PLYNOMER_HOLDING_HPP
