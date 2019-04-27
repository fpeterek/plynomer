//
// Created by Filip Peterek on 2019-04-27.
//

#include <vector>
#include <iostream>
#include <functional>

#include "../address.hpp"

#ifdef assert
#undef assert
#endif

class AssertionError : public std::runtime_error {

public:

    AssertionError() : std::runtime_error("Assertion error") { }
    explicit AssertionError(const std::string & str)
        : std::runtime_error("Assertion error: " + str) { }

};

void assert(const bool condition, const std::string & msg) {
    if (not condition) {
        throw AssertionError(msg);
    }
}

void assert(const bool condition) {
    if (not condition) {
        throw AssertionError();
    }
}

void addressTest() {

    std::vector<std::pair<std::string, bool>> addresses = {
            std::make_pair("123:123:1::2:", false),
            std::make_pair("123:312:1:2", true),
            std::make_pair("123:123:1:", false),
            std::make_pair(":123:123", false),
            std::make_pair("", false),
            std::make_pair("123::312", false),
            std::make_pair("123:123:ae23", false),
            std::make_pair("01ae:123:321", false),
            std::make_pair("12.12:12", false),
            std::make_pair("1$2:3", false),
            std::make_pair("á:2:3", false),
            std::make_pair("#234", false),
            std::make_pair("123", true),
            std::make_pair("12{2}:123", false)
    };

    for (const auto & add : addresses) {

        bool isValid;

        try {
            Address a(add.first);
            std::cout << "Address " << add.first << " is valid" << std::endl;
            isValid = true;
        } catch (const std::exception & e) {
            std::cout << e.what() << std::endl;
            isValid = false;
        }

        if (isValid) {
            assert(add.second, "Address \"" + add.first + "\" is invalid but evaluated as valid");
        }
        else {
            assert(not add.second, "Address \"" + add.first + "\" is valid but evaluated as invalid");
        }

    }
}

std::vector<std::string> successfulTests;
std::vector<std::string> unsuccessfulTests;

void runTest(const std::function<void(void)> & fun, const std::string & testName) {

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Running test: " << testName << "\n" << std::endl;

    bool success = true;
    std::string msg;

    try {
        fun();
    } catch (const std::exception & e) {
        success = false;
        msg = e.what();
    }

    if (success) {
        successfulTests.emplace_back(testName);
    } else {
        unsuccessfulTests.emplace_back(testName);
    }

    std::endl(std::cout);
    std::cout << "Test result: " << (success ? "success" : "failure") << std::endl;

    if (not success) {
        std::cout << "Error: " << msg << std::endl;
    }

    std::cout << "------------------------------------------" << std::endl;

}

void summary() {

    std::cout << "-------------- Test summary --------------" << std::endl;

    auto print = [](const std::string & msg, const std::vector<std::string> & v) {
        std::cout << msg << std::endl;
        for (const auto & t : v) {
            std::cout << "    " << t << std::endl;
        }
    };

    print("Successful tests:", successfulTests);
    print("Unsuccessful tests:", unsuccessfulTests);

    std::cout << "Tests total: " << unsuccessfulTests.size() + successfulTests.size() << std::endl;
    std::cout << "Successful tests total: " << successfulTests.size() << std::endl;
    std::cout << "Unsuccessful tests total: " << unsuccessfulTests.size() << std::endl;

}

void testTest() {
    std::cout << "Unit test Unit test" << std::endl;
}

void test() {

    runTest(addressTest, "Address test");
    runTest(testTest, "Unit test test");

}

int main(int argc, const char * argv[]) {

    test();
    summary();

}