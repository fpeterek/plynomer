//
// Created by Filip Peterek on 2019-04-27.
//

#include <vector>
#include <iostream>
#include <functional>

#include "../address.hpp"
#include "../meter.hpp"
#include "../random.hpp"
#include "../customer.hpp"
#include "../node.hpp"
#include "../distributor.hpp"
#include "../endpoint.hpp"


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

void meterTest() {

    constexpr uint64_t initial = 500;
    constexpr uint64_t cycles = 3000;
    constexpr uint64_t total = initial + cycles;

    Meter meter;
    meter.increment(initial);

    uint64_t brokenFor = 0;

    for (uint64_t i = 0; i < cycles; ++i) {

        if (meter.broken()) {
            ++brokenFor;
        }
        meter.increment(1);

    }

    assert(meter.total() == total - brokenFor);

    std::cout << "Meter.total(): " << meter.total() << std::endl;
    std::cout << "Meter was broken for " << brokenFor << " cycles" << std::endl;

}

void randomTest() {

    const uint64_t min = 54;
    const uint64_t max = 213;

    for (uint64_t i = 0; i < 100; ++i) {
        const uint64_t rand = Random::randInt(min, max);
        assert(54 <= rand and rand <= 213, "Random number outside bounds");
    }

}

void endpointTest() {

    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<NetworkElement>> endpoints;
    uint64_t produced = 0;
    uint64_t consumed = 0;

    for (uint64_t i = 0; i < 10; ++i) {
        customers.emplace_back(std::make_shared<Customer>(std::to_string(i)));
        endpoints.emplace_back(std::make_shared<Endpoint>(*customers.back(), i));
    }

    for (uint64_t i = 0; i < 10; ++i) {
        for (auto & ptr : endpoints) {

            const uint64_t desired = ptr->desiredThroughput();
            const uint64_t cons = ptr->cycle(desired);
            produced += desired;
            consumed += cons;

        }
    }

    uint64_t total = 0;
    for (auto & ptr : endpoints) {
        total += ptr->total();
    }
    std::cout << "Total consumed" << std::endl;
    assert(total <= consumed, "Logged more than actually consumed");
    assert(consumed <= produced, "Consumption cannot exceed production");

}

void treeTest() {

    std::vector<std::shared_ptr<Customer>> customers;

    Distributor dist(150);

    dist.addNode("0");
    dist.addNode("1");

    dist.addNode("0:0");
    dist.addNode("0:1");
    dist.addNode("0:2");

    dist.addNode("1:0");
    dist.addNode("1:0:0");

    std::cout << "Infrastructure built, adding customers" << std::endl;

    dist.addNode("1:0:0:2");
    dist.removeNode("1:0:0:2");

    customers.emplace_back(std::make_shared<Customer>("1:2"));
    dist.addEndpoint("1:2", *customers.back());

    customers.emplace_back(std::make_shared<Customer>("2"));
    dist.addEndpoint("2", *customers.back());

    customers.emplace_back(std::make_shared<Customer>("0:1:0"));
    dist.addEndpoint("0:1:0", *customers.back());

    customers.emplace_back(std::make_shared<Customer>("0:1:1"));
    dist.addEndpoint("0:1:1", *customers.back());

    customers.emplace_back(std::make_shared<Customer>("0:1:2"));
    dist.addEndpoint("0:1:2", *customers.back());

    customers.emplace_back(std::make_shared<Customer>("1:0:0:1"));
    dist.addEndpoint("1:0:0:1", *customers.back());

    std::cout << "Network built, attempting to advance" << std::endl;
    dist.advanceOneDay();
    std::cout << "Advanced successfully" << std::endl;
    std::cout << "Desired: " << dist.desiredLastDay() << "\nConsumed: " << dist.consumedLastDay()
              << "\nMeasured: " << dist.totalMeasured() << std::endl;
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

    auto & v = (success) ? successfulTests : unsuccessfulTests;
    v.emplace_back(testName);

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
    runTest(meterTest, "Meter test");
    runTest(randomTest, "Random test");
    runTest(endpointTest, "Endpoint test");
    runTest(treeTest, "Tree test");

}

int main(int argc, const char * argv[]) {

    test();
    summary();

}
