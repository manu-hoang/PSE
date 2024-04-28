#include <iostream>
#include "stateManager.h"

stateManager::stateManager(sf::RenderWindow& window, System &mainSystem, SystemExporter &mainExporter )
: window(window), mainSystem(mainSystem), mainExporter(mainExporter) {
    pushState(new MenuState(window, *this, false));
}


void stateManager::pushState(State *state) {
    if (!states.empty()) {
        states.top()->exit(window);
    }
    states.push(state);
    state->enter(window,mainSystem);
}

State* stateManager::getCurrentState() const {
    return states.empty() ? nullptr : states.top();
}

void stateManager::previousState() {
    if (states.size() > 1) {
        // Pause and remove the current state
        states.pop();
    }
}

