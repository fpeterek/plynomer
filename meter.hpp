//
// Created by Filip Peterek on 2019-04-23.
//

#ifndef PLYNOMER_METER_HPP
#define PLYNOMER_METER_HPP

#include <cstdint>
#include <random>


class Meter {

    uint64_t _throughput;
    uint64_t _total;
    uint64_t _limit;

protected:
    std::random_device & rand;

public:
    virtual void update();
    virtual void changeThroughput(const uint64_t newThroughput);
    virtual void changeLimit(const uint64_t limit);
    virtual uint64_t throughput();
    virtual uint64_t total();
    virtual uint64_t limit();

    Meter(std::random_device & rand);

};


#endif //PLYNOMER_METER_HPP
