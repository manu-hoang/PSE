#include "string"

using namespace std;

/*
    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
 */

class Device {
private:
    string name;
    int emissions; // gram CO2 per page
    int speed; // pages per minute

    bool busy;

public:
    Device(string name, int emissions, int speed): name(name), emissions(emissions), speed(speed){
        busy = false;
    }

    void toggle_busy();



    //Functions used for PrinterOutput.cpp
    const string &getName() const;
    int getEmissions() const;
    string getQueueInfo();
    string getCurrentInfo();
    //
};

