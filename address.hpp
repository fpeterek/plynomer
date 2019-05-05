//
// Created by Filip Peterek on 2019-04-26.
//

#ifndef PLYNOMER_ADDRESS_HPP
#define PLYNOMER_ADDRESS_HPP


#include <vector>
#include <ostream>


class Address {

    std::vector<uint64_t> _address;

public:

    typedef std::vector<uint64_t>::const_iterator iterator;

    iterator begin() const;
    iterator end() const;
    uint64_t front() const;
    uint64_t back() const;

    Address(const std::string & str);
    Address(const char * str);

};

std::ostream & operator<<(std::ostream & os, const Address & ad);


#endif //PLYNOMER_ADDRESS_HPP
