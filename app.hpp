//
// Created by Filip Peterek on 2019-05-11.
//

#ifndef PLYNOMER_APP_HPP
#define PLYNOMER_APP_HPP

#include <unordered_map>

#include "distributor.hpp"
#include "customer_manager.hpp"
#include "holding.hpp"


class App {

    static const std::string mainMenuOptions;
    static const std::string reportMenuOptions;
    static const std::string structureMenuOptions;


    Distributor distributor;
    CustomerManager customerManager;
    Holding holdingCompany;

    typedef std::function<void()> menuOption;

    std::unordered_map<std::string, menuOption> mainMenu;
    std::unordered_map<std::string, menuOption> infoSubmenu;
    std::unordered_map<std::string, menuOption> structureSubmenu;

    /* Main menu options */

    void advanceOneMonth();
    void report();
    void changeStructure();
    void changePrice();

    /* Void submenu options */
    void addCustomer();
    void removeCustomer();
    void addNode();
    void removeNode();

    void printStructure();
    void financialReport();

    bool submenu();
    bool menu();

public:

    App();
    void run();

};


#endif //PLYNOMER_APP_HPP
