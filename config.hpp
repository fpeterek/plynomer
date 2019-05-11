//
// Created by Filip Peterek on 2019-05-11.
//

#ifndef PLYNOMER_CONFIG_HPP
#define PLYNOMER_CONFIG_HPP

#include <cstdint>


namespace Config {

    const uint64_t initialDesired = 2;
    const uint64_t maxConsumption = 10;
    const uint64_t initialPrice = 1;
    const uint64_t daysInMonth = 30;
    const uint64_t meterChanceToBreak = 1;
    const uint64_t spacesToIndent = 2;

    const double producedDesiredRatioThreshhold = 1.0;
    const double consumedProducedRatioThreshhold = 0.9;
    const double maxProductionIncreaseModifier = 1.3;
}

#endif //PLYNOMER_CONFIG_HPP
