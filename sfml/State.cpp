#include "State.h"
#include <iostream>
#include "fstream"
#include "stateManager.h"
#include "cctype"
#include "random"
#include "../src/SystemImporter.h"
#include "../src/SystemExporter.h"

MenuState::MenuState(sf::RenderWindow& window, stateManager& manager, bool isAdmin) : State(manager) {

    // Load all textures (and give an error in case failure)
    if (!menuTexture.loadFromFile("./assets/main_screen.png")) {
        std::cerr << "Error loading texture file!" << std::endl;
    }
    // Set background of main menu
    menuBg.setTexture(menuTexture);
}
void MenuState::enter(sf::RenderWindow& window, System &sys) {
}
void MenuState::update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) {

    window.draw(menuBg);

    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (mousePos.x >= 97 and mousePos.x <= 400
    and mousePos.y >= 292 and mousePos.y <+ 333
    and sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        manager.pushState(new LoginState(window, manager, true));
    }
    else if (mousePos.x >= 97 and mousePos.x <= 400
        and mousePos.y >= 451 and mousePos.y <+ 493
        and sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        manager.pushState(new LoginState(window, manager, false));
    }

}
void MenuState::exit(sf::RenderWindow &window) {
}

LoginState::LoginState(sf::RenderWindow &window, stateManager &manager, bool isAdmin)  : State(manager){
    admin = isAdmin;
}
void LoginState::enter(sf::RenderWindow& window, System &sys) {

    // Admin screen
    if(admin){
        // Load all textures (and give an error in case failure)
        if (!loginTexture.loadFromFile("./assets/login_admin.png")) {
            std::cerr << "Error loading texture file!" << std::endl;
        }

    }
    // User screen
    else{
        // Load all textures (and give an error in case failure)
        if (!loginTexture.loadFromFile("./assets/login_user.png")) {
            std::cerr << "Error loading texture file!" << std::endl;
        }
        // Load all textures (and give an error in case failure)
        if (!viewTexture.loadFromFile("./assets/empty.png")) {
            std::cerr << "Error loading texture file!" << std::endl;
        }

        // Load the default font
        if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
            std::cerr << "Failed to load default font!" << std::endl;
        }

        // Create a type text object
        typeText.setFont(font);
        typeText.setString("Type : ");
        typeText.setCharacterSize(24);
        typeText.setFillColor(sf::Color{0,46,101});
        typeText.setPosition(100.f, 250.f);

        // Create a pages text object
        pagesText.setFont(font);
        pagesText.setString("Pages : ");
        pagesText.setCharacterSize(24);
        pagesText.setFillColor(sf::Color{0,46,101});
        pagesText.setPosition(100.f, 450.f);
    }

    rightTypeText.setFont(font);
    rightTypeText.setString("Allowed types : bw, color, scan");
    rightTypeText.setCharacterSize(18);
    rightTypeText.setFillColor(sf::Color{52,178,51});
    rightTypeText.setPosition(100.f, 290.f);

    wrongTypeText.setFont(font);
    wrongTypeText.setString("This type is currently unavailable");
    wrongTypeText.setCharacterSize(18);
    wrongTypeText.setFillColor(sf::Color{171,7,7});
    wrongTypeText.setPosition(100.f, 320.f);

    allowedPagesText.setFont(font);
    allowedPagesText.setString("Fill in any amount of pages");
    allowedPagesText.setCharacterSize(18);
    allowedPagesText.setFillColor(sf::Color{52,178,51});
    allowedPagesText.setPosition(100.f, 490.f);


    // Set background of main menu
    loginBg.setTexture(loginTexture);
    viewBg.setTexture(viewTexture);
}
void LoginState::update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) {
    if(enterCount == 0 or admin){
        window.draw(loginBg);
        window.draw(toPrint);
    }
    else{
        window.draw(viewBg);
    }

    if(admin and input == "CO2" and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        manager.pushState(new ViewState(window, manager, true));
    }
    if(!admin and !input.empty() and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) and enterCount == 0){
        username = input;
        enterCount ++;
    }
    if(enterCount > 0){

        toPrint.setOrigin(0,0);

        if (enterCount == 1){
            toPrint.setPosition(172.f,typeText.getPosition().y);
            if ((input == "bw" or input == "color" or input == "scan")
            and !checkIfTypeExists(input, this->manager.getMainSystem())){
                window.draw(wrongTypeText);
            }
        }
        else if (enterCount == 2){
            toPrint.setPosition(180.f,pagesText.getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if (enterCount == 1 and (input == "bw" or input == "color" or input == "scan")
            and checkIfTypeExists(input,this->manager.getMainSystem())){
                if(input == "bw"){
                    type = bw_job;
                }
                else if(input == "color"){
                    type = color_job;
                }
                else{
                    type = scan_job;
                }
                typeText.setString(typeText.getString()+input);
                typeString = input;
                enterCount ++;

            }
            else if (enterCount == 2 and isNumeric(input)){
                pagesText.setString(pagesText.getString()+input);
                pagesString = input;

                Job* job = addNewJob(getRandomNumber(1,100), stoi(pagesString), type, username);
                this->manager.getMainSystem().addJob(job);

                // reset everything
                typeText.setString("Type : ");
                pagesText.setString("Pages : ");
                username = "";
                typeString = "";
                pagesString = "";

                manager.pushState(new DeviceState(window, manager, false));
            }
            else{
                input = "";
            }
        }
        window.draw(typeText);
        window.draw(pagesText);
        window.draw(rightTypeText);
        window.draw(allowedPagesText);
        if (!input.empty()){
            window.draw(toPrint);
        }
    }

}
void LoginState::exit(sf::RenderWindow& window) {}

bool isNumeric(const std::string& str) {
    if (str.empty()) {
        return false; // String is empty
    }

    for (char c : str) {
        if (!std::isdigit(c)) {
            return false; // Found a non-numeric character
        }
    }
    return true; // All characters are numeric
}
int getRandomNumber(int min, int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    return distr(gen); // Generate and return the random number
}
Job* addNewJob(int jobNumber, int pageCount, JobEnum type, const string& userName){

    if(type == bw_job){return new BlackWhiteJob(jobNumber,pageCount,userName,getRandomNumber(1,1000));}

    else if (type == color_job){return new ColorJob(jobNumber,pageCount,userName,getRandomNumber(1,1000));}

    else if (type == scan_job){return new ScanJob(jobNumber,pageCount,userName,getRandomNumber(1,1000));}

    return nullptr;
}
bool checkIfTypeExists(string type, System &sys){
    vector<string> existingTypes;

    int deviceSize = sys.getDevices().size();

    for (int i = 0; i < deviceSize; ++i) {
        existingTypes.emplace_back(sys.getDevices()[i]->getType());
    }

    // Convert string
    if(type == "bw"){
        type = "Black-and-white printer";
    }
    else if(type == "scan"){
        type = "Scanner";
    }
    else if(type == "color"){
        type = "Color printer";
    }

    for (const std::string& element : existingTypes) {
        if (element == type) {
            return true; // String found in the vector
        }
    }
    return false; // String not found in the vector
}

ViewState::ViewState(sf::RenderWindow &window, stateManager &manager, bool isAdmin)  : State(manager){
    admin = isAdmin;
}
void ViewState::enter(sf::RenderWindow& window, System &sys) {

    // Admin screen
    if(admin){
        // Load all textures (and give an error in case failure)
        if (!viewTexture.loadFromFile("./assets/admin_screen.png")) {
            std::cerr << "Error loading texture file!" << std::endl;
        }

    }
    // User screen
    else{
        // Load all textures (and give an error in case failure)
        if (!viewTexture.loadFromFile("./assets/empty.png")) {
            std::cerr << "Error loading texture file!" << std::endl;
        }

        // Load the default font
        if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
            std::cerr << "Failed to load default font!" << std::endl;
        }
    }
    // Set background of main menu
    viewBg.setTexture(viewTexture);

}
void ViewState::update(sf::RenderWindow& window, std::string &input, sf::Text toPrint) {

    window.draw(viewBg);
    timer ++;
    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(admin) {
        if (mousePos.x >= 97 and mousePos.x <= 400
            and mousePos.y >= 292 and mousePos.y < +333
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            manager.pushState(new DeviceState(window, manager, true));
        } else if (mousePos.x >= 97 and mousePos.x <= 400
            and mousePos.y >= 451 and mousePos.y < +493
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            manager.pushState(new JobState(window, manager, true));
        } else if(mousePos.x >= 441 and mousePos.x <= 484
            and mousePos.y >= 12 and mousePos.y < +55
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            manager.pushState(new CO2State(window, manager, true));
        } else if (mousePos.x >= 100 and mousePos.x <= 242
            and mousePos.y >= 562 and mousePos.y < +616
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)
            and click == 0) {
            click = 1;
        } else if (mousePos.x >= 257 and mousePos.x <= 400
            and mousePos.y >= 562 and mousePos.y < +616
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)
            and click == 1) {
            click = 0;
            if (!queueEmpty(this->manager.getMainSystem())){
            }
        }
    }
    if (click == 1 and timer%60 == 0){
        this->manager.getMainSystem().tick();
        toOutput += this->manager.getMainExporter().advanced_textual_output_string(this->manager.getMainSystem());
        myFile.open("in_output/advanced_textual_output.txt");
        this->manager.getMainExporter().documentStart(myFile);
        myFile << toOutput;
        this->manager.getMainExporter().documentEnd(myFile);
        myFile.close();
        myFile.open("in_output/graphics.ini");
        this->manager.getGraphicalExporter().documentStart(myFile);
        this->manager.getGraphicalExporter().output(myFile, this->manager.getMainSystem());
        this->manager.getGraphicalExporter().documentEnd(myFile);
        myFile.close();
    }

}
void ViewState::exit(sf::RenderWindow& window) {}

bool queueEmpty(System &sys){
    int deviceSize = sys.getDevices().size();
    int empty = 0;

    for (int i = 0; i < deviceSize; ++i) {
        if (sys.getDevices()[i]->get_queue().empty()){
            empty ++;
        }
    }
    if (empty == deviceSize){
        return true;
    }
    return false;
}

JobState::JobState(sf::RenderWindow &window, stateManager &manager, bool isAdmin)  : State(manager) {admin = isAdmin;}
void JobState::enter(sf::RenderWindow& window, System &sys){
    // Load all textures (and give an error in case failure)
    if (!viewTexture.loadFromFile("./assets/empty.png")) {
        std::cerr << "Error loading texture file!" << std::endl;
    }

    viewBg.setTexture(viewTexture);

    if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
        std::cerr << "Failed to load default font!" << std::endl;
    }

    if(admin) {
        int jobSize = sys.getJobs().size();

        for (int i = 0; i < jobSize; ++i) {
            sf::RectangleShape newSquare(sf::Vector2f(350, 100));
            newSquare.setOutlineThickness(3);
            newSquare.setOutlineColor(sf::Color{0,46,101});
            newSquare.setOrigin(175, 50);
            newSquare.setPosition(sf::Vector2f(250, 260 + i * 100));

            squaresJobs.emplace_back(newSquare);

            std::vector<sf::Text> jobToAdd;
            sf::Text name("Job : "+sys.getJobs()[i]->getUserName(), font, 18);
            name.setFillColor(sf::Color::Black);
            name.setPosition(80, 212 + i * 100);
            jobToAdd.emplace_back(name);

            sf::Text type("Type : "+sys.getJobs()[i]->getType(), font, 18);
            type.setFillColor(sf::Color::Black);
            type.setPosition(80, 212 + 24 + i * 100);
            jobToAdd.emplace_back(type);

            sf::Text emission("PageCount : "+sys.getJobs()[i]->getTotalPages(), font, 18);
            emission.setFillColor(sf::Color::Black);
            emission.setPosition(80, 212 + 48 + i * 100);
            jobToAdd.emplace_back(emission);

            sf::Text speed("JobNumber : "+to_string(sys.getJobs()[i]->getJobNumber()), font, 18);
            speed.setFillColor(sf::Color::Black);
            speed.setPosition(80, 212 + 72 + i * 100);
            jobToAdd.emplace_back(speed);


            textsJobs.emplace_back(jobToAdd);
        }
    }
    else{
    }
}
void JobState::update(sf::RenderWindow& window, std::string &input, sf::Text toPrint){
    window.draw(viewBg);
    if (admin){
        int squareSize = squaresJobs.size();
        for (int i = 0; i < squareSize; ++i){
            if (squaresJobs[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                            sf::Mouse::getPosition(window).y)){
                squaresJobs[i].setFillColor(sf::Color{255, 255, 0, 80});
            }
            else{
                squaresJobs[i].setFillColor(sf::Color::Transparent);
            }
            window.draw(squaresJobs[i]);
        }
        for (const auto & textJob : textsJobs) {
            for (const auto & k : textJob) {
                window.draw(k);
            }
        }
    }
    else{
    }

}
void JobState::exit(sf::RenderWindow& window){}

DeviceState::DeviceState(sf::RenderWindow &window, stateManager &manager, bool isAdmin)  : State(manager) {admin = isAdmin;}
void DeviceState::enter(sf::RenderWindow& window, System &sys){
    // Load all textures (and give an error in case failure)
    if (!viewTexture.loadFromFile("./assets/empty.png")) {
        std::cerr << "Error loading texture file!" << std::endl;
    }

    viewBg.setTexture(viewTexture);

    if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
        std::cerr << "Failed to load default font!" << std::endl;
    }
    int deviceSize = sys.getDevices().size();
    for (int i = 0; i < deviceSize; ++i) {
        sf::RectangleShape newSquare(sf::Vector2f(350, 100));
        newSquare.setOutlineThickness(3);
        newSquare.setOutlineColor(sf::Color{0,46,101});
        newSquare.setOrigin(175, 50);
        newSquare.setPosition(sf::Vector2f(250, 260 + i * 100));

        squaresDevice.emplace_back(newSquare);

        std::vector<sf::Text> deviceToAdd;
        sf::Text name("Device : "+sys.getDevices()[i]->getName(), font, 18);
        name.setFillColor(sf::Color::Black);
        name.setPosition(80, 212 + i * 100);
        deviceToAdd.emplace_back(name);

        sf::Text type("Type : "+sys.getDevices()[i]->getType(), font, 18);
        type.setFillColor(sf::Color::Black);
        type.setPosition(80, 212 + 18 + i * 100);
        deviceToAdd.emplace_back(type);

        sf::Text emission("emission : "+sys.getDevices()[i]->getEmissions(), font, 18);
        emission.setFillColor(sf::Color::Black);
        emission.setPosition(80, 212 + 36 + i * 100);
        deviceToAdd.emplace_back(emission);

        sf::Text speed("speed : "+sys.getDevices()[i]->getSpeed(), font, 18);
        speed.setFillColor(sf::Color::Black);
        speed.setPosition(80, 212 + 54 + i * 100);
        deviceToAdd.emplace_back(speed);

        sf::Text cost("cost : "+to_string(sys.getDevices()[i]->getCosts()), font, 18);
        cost.setFillColor(sf::Color::Black);
        cost.setPosition(80, 212 + 72 + i * 100);
        deviceToAdd.emplace_back(cost);

        sf::Text co2("CO2 : "+to_string(sys.getDevices()[i]->get_CO2()), font, 18);
        if (sys.getDevices()[i]->exceeds_CO2_limit(sys.getDevices()[i]->get_CO2())){
            co2.setFillColor(sf::Color{171,7,7});
        }
        else{
            co2.setFillColor(sf::Color{52,200,51});
        }
        co2.setPosition(350, 212 + 72 + i * 100);
        deviceToAdd.emplace_back(co2);

        textsDevice.emplace_back(deviceToAdd);
    }

}
void DeviceState::update(sf::RenderWindow& window, std::string &input, sf::Text toPrint){
    window.draw(viewBg);

    int squareSize = squaresDevice.size();
    for (int i = 0; i < squareSize; ++i) {
        if (squaresDevice[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                        sf::Mouse::getPosition(window).y)) {
            squaresDevice[i].setFillColor(sf::Color{255, 255, 0, 80});

            // debugging

            //cout<<this->manager.getMainSystem().getDevices()[i]->getTypeJob()<< " "
            //<<this->manager.getMainSystem().getJobs()[this->manager.getMainSystem().getJobs().size()-1]->getType()<<endl;


            if (!admin and this->manager.getMainSystem().getDevices()[i]->getTypeJob() ==
            this->manager.getMainSystem().getJobs()[this->manager.getMainSystem().getJobs().size()-1]->getType()
            and sf::Mouse::isButtonPressed(::sf::Mouse::Left)) {
                // CO2 gets compensated

                int compNumber = getRandomNumber(1,1000);
                auto* compensation = new Compensation(compNumber, "compensation"+ to_string(compNumber));
                this->manager.getMainSystem().addCompensation(compensation);

                this->manager.getMainSystem().getJobs()[this->manager.getMainSystem().getJobs().size()-1]->setCompNumber(compNumber);
                this->manager.getMainSystem().getJobs()[this->manager.getMainSystem().getJobs().size()-1]->getCompensated();

                this->manager.getMainSystem().getDevices()[i]->add_job(this->manager.getMainSystem().getJobs()[this->manager.getMainSystem().getJobs().size()-1]);
                int stackSize = this->manager.getStates().size();
                for (int j = 0; j < stackSize-1; ++j) {
                    this->manager.previousState();
                }
            }
        }
        else{
            squaresDevice[i].setFillColor(sf::Color::Transparent);
        }
        window.draw(squaresDevice[i]);
    }
    for (const auto & textDevice : textsDevice) {
        for (const auto & j : textDevice) {
            window.draw(j);
        }
    }
    if (admin){


    }

}
void DeviceState::exit(sf::RenderWindow& window){}

CO2State::CO2State(sf::RenderWindow& window, stateManager& manager, bool isAdmin) : State(manager){admin = isAdmin;}
void CO2State::enter(sf::RenderWindow &window, System &sys) {
    sys.calculateStatistics();
    // Load all textures (and give an error in case failure)
    if (!viewTexture.loadFromFile("./assets/empty.png")) {
        std::cerr << "Error loading texture file!" << std::endl;
    }

    viewBg.setTexture(viewTexture);

    if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
        std::cerr << "Failed to load default font!" << std::endl;
    }

    cost += sys.getTotalOperatingCosts();
    sf::Text totalOperatingCost("Total Operating Costs : "+to_string(sys.getTotalOperatingCosts()), font, 18);
    totalOperatingCost.setFillColor(sf::Color::Black);
    totalOperatingCost.setPosition(50, 260);
    neededText.emplace_back(totalOperatingCost);

    sf::Text mostUsedDevice("Most Used Device : "+sys.getMostUsedDevice()->getName(), font, 18);
    mostUsedDevice.setFillColor(sf::Color::Black);
    mostUsedDevice.setPosition(50, 320);
    neededText.emplace_back(mostUsedDevice);

    sf::Text totalCO2Emission("Total CO2 Emission : "+to_string(sys.getTotalEmissions()), font, 18);
    totalCO2Emission.setFillColor(sf::Color::Black);
    totalCO2Emission.setPosition(50, 380);
    neededText.emplace_back(totalCO2Emission);

    sf::Text averageCO2PerPage("Average CO2 Per Page : "+to_string(sys.getAverageCO2perPage()), font, 18);
    averageCO2PerPage.setFillColor(sf::Color::Black);
    averageCO2PerPage.setPosition(50, 440);
    neededText.emplace_back(averageCO2PerPage);

    sf::Text mostUsedCompensation("Most Used Compensation : "+sys.getMostUsedCompensation()->getName(), font, 18);
    mostUsedCompensation.setFillColor(sf::Color::Black);
    mostUsedCompensation.setPosition(50, 500);
    neededText.emplace_back(mostUsedCompensation);
}
void CO2State::update(sf::RenderWindow &window, std::string &input, sf::Text toPrint) {
    window.draw(viewBg);
    for (auto &text : neededText) {
        window.draw(text);
    }
}
void CO2State::exit(sf::RenderWindow &window) {}