#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include "State.h"
#include <stack>
#include "../src/Device.h"
#include "../src/System.h"
#include "../src/Job.h"

class stateManager {
private:
    std::stack<State *> states;
    sf::RenderWindow& window;

    System &mainSystem;
public:
    stateManager(sf::RenderWindow& window, System& mainSystem); // Constructor

    void pushState(State *state);
    void previousState();

    void setMainSystem(System &mainSystem1) {stateManager::mainSystem = mainSystem1;}
    System &getMainSystem() const {return mainSystem;}

    const stack<State *> &getStates() const {return states;}

    // Getter for the current state
    State* getCurrentState() const;
};

#endif //PACMAN_STATEMANAGER_H
