#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../src/Device.h"
#include "../src/System.h"
#include "../src/Job.h"
#include "fstream"

#include "memory"
#include <random>

// Forward declaration of stateManager to resolve circular dependency
class stateManager;

class State {
protected:
    stateManager& manager;  // Add a reference to stateManager
    sf::Font font;
    bool admin = false;

public:
    State(stateManager& manager) : manager(manager) {}
    virtual void enter(sf::RenderWindow& window, System &sys) = 0;
    virtual void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) = 0;
    virtual void exit(sf::RenderWindow& window) = 0;

    virtual bool isAdmin() const {return admin;}
};

class MenuState : public State {
private:
    sf::Texture menuTexture;
    sf::Sprite menuBg;

public:
    MenuState(sf::RenderWindow& window, stateManager& manager, bool isAdmin);
    void enter(sf::RenderWindow& window, System &sys) override;
    void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) override;
    void exit(sf::RenderWindow& window) override;

};

class LoginState : public State {
private:
    sf::Texture loginTexture;
    sf::Sprite loginBg;

    sf::Texture viewTexture;
    sf::Sprite viewBg;

    sf::Text typeText;
    std::string typeString;

    sf::Text pagesText;
    std::string pagesString;

    sf::Text rightTypeText;
    sf::Text wrongTypeText;

    sf::Text allowedPagesText;

    JobEnum type;
    string username;

    int enterCount = 0;

public:
    LoginState(sf::RenderWindow& window, stateManager& manager, bool isAdmin);
    void enter(sf::RenderWindow& window, System &sys) override;
    void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) override;
    void exit(sf::RenderWindow& window) override;
};

class ViewState : public State {
private:
    sf::Texture viewTexture;
    sf::Sprite viewBg;

    ofstream myFile;
    int click = 0;
    int timer = 0;

    string toOutput;

public:
    ViewState(sf::RenderWindow& window, stateManager& manager, bool isAdmin);
    void enter(sf::RenderWindow& window, System &sys) override;
    void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) override;
    void exit(sf::RenderWindow& window) override;

};

class JobState : public State {
private:
    sf::Texture viewTexture;
    sf::Sprite viewBg;

    std::vector<sf::RectangleShape> squaresJobs;
    std::vector<std::vector<sf::Text>> textsJobs;
public:
    JobState(sf::RenderWindow& window, stateManager& manager, bool isAdmin);
    void enter(sf::RenderWindow& window, System &sys) override;
    void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) override;
    void exit(sf::RenderWindow& window) override;
};

class DeviceState : public State {
private:
    sf::Texture viewTexture;
    sf::Sprite viewBg;

    std::vector<sf::RectangleShape> squaresDevice;
    std::vector<std::vector<sf::Text>> textsDevice;
public:
    DeviceState(sf::RenderWindow& window, stateManager& manager, bool isAdmin);
    void enter(sf::RenderWindow& window, System &sys) override;
    void update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) override;
    void exit(sf::RenderWindow& window) override;
};

bool isNumeric(const std::string& str);
int getRandomNumber(int min, int max);
Job* addNewJob(int jobNumber, int pageCount, JobEnum type, const string& userName);
bool checkIfTypeExists(string type, System &sys);
bool queueEmpty(System &sys);


#endif //PACMAN_STATE_H
