//
// Created by Filip Peterek on 2019-05-11.
//

#include <iostream>
#include "app.hpp"

std::string getMenuOption(const std::string & msg) {

    std::cout << msg;
    std::cout << "\n\n";
    std::cout << "In: ";

    std::string in;
    std::cin >> in;

    return in;

}

std::string getAddress() {
    std::cout << "Address: ";
    std::string in;
    std::cin >> in;
    return in;
}

const std::string App::mainMenuOptions
    = "[1] Continue [2] Reports [3] Structural Changes [4] Change Price [5] Exit";
const std::string App::reportMenuOptions
    = "[1] Print Structure [2] Financial Report [3] Back";
const std::string App::structureMenuOptions
    = "[1] Add Node [2] Remove Node [3] Add Customer [4] Remove Customer [5] Back";

App::App() : distributor(250), customerManager(distributor),
             holdingCompany(distributor, customerManager) {

    mainMenu["1"] = std::bind(&App::advanceOneMonth, this);
    mainMenu["2"] = std::bind(&App::report, this);
    mainMenu["3"] = std::bind(&App::changeStructure, this);
    mainMenu["4"] = std::bind(&App::changePrice, this);

    structureSubmenu["1"] = std::bind(&App::addNode, this);
    structureSubmenu["2"] = std::bind(&App::removeNode, this);
    structureSubmenu["3"] = std::bind(&App::addCustomer, this);
    structureSubmenu["4"] = std::bind(&App::removeCustomer, this);

    infoSubmenu["1"] = std::bind(&App::printStructure, this);
    infoSubmenu["2"] = std::bind(&App::financialReport, this);

}

void App::advanceOneMonth() {

    holdingCompany.newMonth();

    for (uint64_t i = 0; i < Config::daysInMonth; ++i) {
        distributor.advanceOneDay();
        holdingCompany.log();
    }

    std::cout << "Advanced by one month" << std::endl;
    holdingCompany.checkProductionNeeds();

}

void App::report() {

    std::string in = getMenuOption(reportMenuOptions);

    if (infoSubmenu.count(in)) {
        infoSubmenu[in]();
    }

    if (in == "3") {
        return;
    }

    report();

}

void App::changeStructure() {

    std::string in = getMenuOption(structureMenuOptions);

    if (structureSubmenu.count(in)) {
        structureSubmenu[in]();
    }

    if (in == "5") {
        return;
    }

    changeStructure();

}

void App::changePrice() {

    std::cout << "Old price: " << holdingCompany.pricePerUnit() << std::endl;
    std::cout << "New price: ";
    std::string in;
    std::cin >> in;
    try {
        holdingCompany.setPrice(std::stoull(in));
    } catch (const std::exception &) {
        std::cout << "Price could not be changed" << std::endl;
    }
}

void App::addCustomer() {

    try {
        auto add = getAddress();
        customerManager.addCustomer(add);
    } catch (const std::exception &) {
        std::cout << "Customer could not be added" << std::endl;
    }

}

void App::removeCustomer() {

    try {
        auto add = getAddress();
        customerManager.removeCustomer(add);
    } catch (const std::exception &) {
        std::cout << "Node could not be removed" << std::endl;
    }

}

void App::addNode() {

    try {
        auto add = getAddress();
        distributor.addNode(add);
    } catch (const std::exception &) {
        std::cout << "Node could not be added" << std::endl;
    }

}

void App::removeNode() {

    try {
        auto add = getAddress();
        distributor.removeNode(add);
    } catch (const std::exception &) {
        std::cout << "Node could not be removed" << std::endl;
    }

}

void App::printStructure() {
    distributor.printNetwork(std::cout);
}

void App::financialReport() {

    std::cout << "Total revenue: " << holdingCompany.totalRevenue() << std::endl;
    std::cout << "Expected revenue last month: " << holdingCompany.revenueLastMonth() << std::endl;
    std::endl(std::cout);

    std::cout << "Desired last month: " << holdingCompany.desiredLastMonth() << std::endl;
    std::cout << "Produced last month: " << holdingCompany.producedLastMonth() << std::endl;
    std::cout << "Consumed last month: " << holdingCompany.consumedLastMonth() << std::endl;
    std::cout << "Price per unit: " << holdingCompany.pricePerUnit() << std::endl;
    std::endl(std::cout);

    std::cout << "Total losses: " << holdingCompany.totalLosses() << std::endl;
    std::cout << "Losses last month: " << holdingCompany.lossesLastMonth() << std::endl;
    std::endl(std::cout);

}

bool App::menu() {

    std::string in = getMenuOption(mainMenuOptions);

    if (in == "5") {
        return false;
    }

    if (mainMenu.count(in)) {
        mainMenu[in]();
    }

    return true;

}

void App::run() {

    while (menu());

}
