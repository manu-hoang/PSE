#include <fstream>
#include "System.h"
#include "SystemImporter.h"
#include "SystemExporter.h"
#include "contracts/DesignByContract.h"
#include "chrono"
#include "../sfml/State.h"
#include "../sfml/stateManager.h"

using namespace std;

int main() {

    System system;
    AdvancedTextualExporter advanced_exporter;
    GraphicsExporter graphics_exporter;

    // input parser
    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/CompleteInput.xml", myfile, system);
    myfile.close();

    /*
    myfile.open("in_output/advanced_textual_output.txt");
    advanced_exporter.documentStart(myfile);

    // main loop
    int seconds = 1; // total run time of the program
    system.divideJobs(); // divide all jobs to respective devices queue before loop (prevents multiple unnecessary divisions)
    for (int i = 0; i <= seconds; ++i) {
        system.tick();
        advanced_exporter.output(myfile, system);
    }

    system.automated_processing(cout);
    advanced_exporter.output(myfile, system);
    system.calculateStatistics();

    advanced_exporter.documentEnd(myfile);
    myfile.close();

    // simple output
    SimpleExporter simple_exporter;
    myfile.open("in_output/simple_output.txt");

    simple_exporter.documentStart(myfile);
    simple_exporter.output(myfile, system);
    simple_exporter.documentEnd(myfile);

    myfile.close();


    // 3D Graphical output
    GraphicsExporter graphics_exporter;
    myfile.open("in_output/graphics.ini");
    graphics_exporter.documentStart(myfile);
    graphics_exporter.output(myfile, system);
    graphics_exporter.documentEnd(myfile);
    myfile.close();

     */

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(500, 700), "SFML Window");
    system.divideJobs();
    stateManager s(window,system,advanced_exporter, graphics_exporter);
    window.setFramerateLimit(60);

    std::string userInput;
    sf::Text userText;
    sf::Font font;

    // Load the default font
    if (!font.loadFromFile("./fonts/coolvetica_rg.otf")) {
        std::cerr << "Failed to load default font!" << std::endl;
    }
    userText.setFont(font);
    userText.setOrigin(userText.getLocalBounds().width/2.0f, userText.getLocalBounds().height / 2.0f);
    userText.setPosition(250.f,380.f);
    userText.setCharacterSize(24);
    userText.setFillColor(sf::Color::Black);

    sf::Texture backTexture;
    sf::Sprite backBg;

    // Load all textures (and give an error in case failure)
    if (!backTexture.loadFromFile("./assets/back.png")) {
        std::cerr << "Error loading texture file!" << std::endl;
    }
    backBg.setTexture(backTexture);
    backBg.setPosition(15,15);

    // Timer variables
    auto lastClickTime = std::chrono::steady_clock::now();
    constexpr float CLICK_INTERVAL_SECONDS = 0.5f; // 0.5 seconds


    // Main loop
    while (window.isOpen()) {

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered and
                (dynamic_cast<LoginState*>(s.getCurrentState()) or dynamic_cast<ViewState*>(s.getCurrentState()))
                and !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) and !userInput.empty()){
                    userInput.pop_back();
                    userText.setString(userInput);
                    userText.setOrigin(userText.getLocalBounds().width/2.0f, userText.getLocalBounds().height / 2.0f);
                    userText.setPosition(250.f,380.f);
                }

                else if (event.text.unicode < 128) {
                    userInput += event.text.unicode;
                    userText.setString(userInput);
                    //std::cout << "Input: " << userInput << std::endl; // Debugging
                    userText.setOrigin(userText.getLocalBounds().width/2.0f, userText.getLocalBounds().height / 2.0f);
                    userText.setPosition(250.f,380.f);
                }
            }
        }


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Check if enough time has passed since the last click
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastClickTime);

        if (mousePos.x >= 15 and mousePos.x <= 45
            and mousePos.y >= 15 and mousePos.y < 45
            and sf::Mouse::isButtonPressed(sf::Mouse::Left)
            and elapsedTime.count() >= CLICK_INTERVAL_SECONDS) {
            lastClickTime = currentTime;
            s.previousState();
        }

        if (dynamic_cast<ViewState*>(s.getCurrentState())){
            if (mousePos.x >= 212 and mousePos.x <= 241
                and mousePos.y >= 633 and mousePos.y < 662
                and sf::Mouse::isButtonPressed(sf::Mouse::Left)
                and elapsedTime.count() >= CLICK_INTERVAL_SECONDS) {
                lastClickTime = currentTime;
                // tick back
            }
            else if(mousePos.x >= 257 and mousePos.x <= 287
                    and mousePos.y >= 633 and mousePos.y < 662
                    and sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    and elapsedTime.count() >= CLICK_INTERVAL_SECONDS){
                lastClickTime = currentTime;
                system.tick();
                myfile.open("in_output/advanced_textual_output.txt");
                advanced_exporter.documentStart(myfile);
                advanced_exporter.output(myfile,system);
                advanced_exporter.documentEnd(myfile);
                myfile.close();
                myfile.open("in_output/graphics.ini");
                graphics_exporter.documentStart(myfile);
                graphics_exporter.output(myfile, system);
                graphics_exporter.documentEnd(myfile);
                myfile.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw your content here
        //s.updateCurrentState();
        State* currentState = s.getCurrentState();

        if (currentState)
        {
            currentState->update(window, userInput, userText);
        }

        window.draw(backBg);

        // Display the window
        window.display();

        State* afterUpdateState = s.getCurrentState();
        if (currentState != afterUpdateState){
            userInput = "";
            userText.setString(userInput);
        }
    }

    return 0;
}