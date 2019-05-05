//
// Created by Filip Peterek on 2019-04-26.
//

#include "address.hpp"

#include <sstream>

void checkStr(const std::string & str) {

    if (str.empty()) {
        throw std::invalid_argument("Invalid address");
    }

    for (char c : str) {
        if (not isdigit(c)) {
            throw std::invalid_argument("Invalid address");
        }
    }

}

std::vector<uint64_t> parse(const std::string & str) {

    std::stringstream ss(str);
    std::vector<uint64_t> vector;

    do {
        std::string element;
        std::getline(ss, element, ':');

        checkStr(element);

        vector.emplace_back(std::stoull(element));

    } while (not ss.eof());

    if (vector.empty()) {
        throw std::invalid_argument("Invalid address");
    }

    return vector;

}

Address::iterator Address::begin() const {
    return _address.cbegin();
}

Address::iterator Address::end() const {
    return _address.cend();
}

uint64_t Address::front() const {
    return _address.front();
}

uint64_t Address::back() const {
    return _address.back();
}

Address::Address(const std::string & str) {

    try {
        _address = parse(str);
    } catch (const std::exception & e) {
        throw std::invalid_argument("Invalid address: " + str);
    }
}

Address::Address(const char * str) : Address(std::string(str)) { }

std::ostream & operator<<(std::ostream & os, const Address & ad) {

    auto it = ad.begin();

    while (it != ad.end()) {
        os << *it << ":";
        ++it;
    }

    return os;

}
