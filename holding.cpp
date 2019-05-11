//
// Created by Filip Peterek on 2019-05-11.
//

#include <iostream>
#include "holding.hpp"


Holding::Holding(Distributor & distributor, CustomerManager & customerManager)
    : distributor(distributor), customerManager(customerManager) {

    setPrice(Config::initialPrice);

}

void Holding::increaseProduction() {

    const double mod = Config::maxProductionIncreaseModifier;
    const uint64_t newMax = distributor.maxOutput() * mod;
    std::cout << "Production increase necessary, increasing "
              << "max production to " << newMax << std::endl;
    distributor.changeMaxOutput(newMax);

}

void Holding::checkProductionNeeds() {

    const double prodDesRatio = _producedLastMonth / (double)_desiredLastMonth;
    const double consProdRatio = _consumedLastMonth / (double)_producedLastMonth;

    if (prodDesRatio >= Config::producedDesiredRatioThreshhold) {
        return;
    }

    if (consProdRatio <= Config::consumedProducedRatioThreshhold) {
        return;
    }

    increaseProduction();

}

void Holding::log() {

    _desiredLastMonth += distributor.desiredLastDay();
    _producedLastMonth += distributor.producedLastDay();
    _consumedLastMonth += distributor.consumedLastDay();

}

void Holding::newMonth() {

    _desiredLastMonth = 0;
    _producedLastMonth = 0;
    _consumedLastMonth = 0;
    _lossesPrevMonth = distributor.lossInUnits();

}

uint64_t Holding::pricePerUnit() {
    return _pricePerUnit;
}

void Holding::setPrice(const uint64_t newPrice) {
    customerManager.updatePrice(newPrice);
    _pricePerUnit = newPrice;
}

uint64_t Holding::lossesLastMonth() {
    return (distributor.lossInUnits() - _lossesPrevMonth) * _pricePerUnit;
}

uint64_t Holding::totalLosses() {
    return distributor.lossInUnits() * _pricePerUnit;
}

uint64_t Holding::totalRevenue() {
    return distributor.totalMeasured() * _pricePerUnit;
}

uint64_t Holding::revenueLastMonth() {
    return _consumedLastMonth * _pricePerUnit;
}

uint64_t Holding::producedLastMonth() {
    return _producedLastMonth;
}

uint64_t Holding::desiredLastMonth() {
    return _desiredLastMonth;
}

uint64_t Holding::consumedLastMonth() {
    return _consumedLastMonth;
}
