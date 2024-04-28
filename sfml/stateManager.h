#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include "State.h"
#include <stack>
#include "../src/Device.h"
#include "../src/System.h"
#include "../src/Job.h"
#include "../src/SystemExporter.h"
#include "fstream"

class stateManager {
private:
    std::stack<State *> states;
    sf::RenderWindow& window;

    System &mainSystem;
    SystemExporter &mainExporter;

public:
    stateManager(sf::RenderWindow& window, System& mainSystem, SystemExporter &mainExporter); // Constructor

    void pushState(State *state);
    void previousState();

    void setMainSystem(System &mainSystem1) {stateManager::mainSystem = mainSystem1;}
    System &getMainSystem() const {return mainSystem;}

    SystemExporter &getMainExporter() const {return mainExporter;}
    void setMainExporter(SystemExporter &mainExporter1) {stateManager::mainExporter = mainExporter1;}

    const stack<State *> &getStates() const {return states;}

    // Getter for the current state
    State* getCurrentState() const;
};

#endif //PACMAN_STATEMANAGER_H
