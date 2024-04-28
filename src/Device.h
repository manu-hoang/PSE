#pragma once

#include <queue>
#include "string"
#include "Job.h"

using namespace std;

/*
    TOTAL EMISSIONS LIMITS:

    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
*/

enum DeviceEnum {bw_device, color_device, scan_device, invalid_device};

class Device {
public:

    Device(string name, int emissions, double speed, int cost);

    virtual DeviceEnum get_type() = 0;

    bool properlyInitialized();

    void print(int totalRunTime); // print for 1 second

     void popQueue();

    void updatePositions(int totalRunTime);

    Job* getCurrentJob();

    void add_job(Job *job);

    queue<Job*> get_queue();

    int get_CO2();

    void set_CO2(int value);

    bool exceeds_CO2_limit(int value);

    int get_emissions();

    int get_limit();

    // Use Case 2.2, Simple Output
    string getName();
    string getEmissions();
    string getSpeed();
    string getType();
    string getCosts();

protected:
    void set_limit(int limit);

private:
    Device* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    string name;

    int CO2_value; // current device value
    int CO2_limit; // limit

    int emissions; // gram CO2 per page

    int speed; // pages per minute
    int cost; // cents per page

    bool busy;

    queue<Job*> queue;
};

class BlackWhitePrinter : public Device {
public:
    BlackWhitePrinter(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class ColorPrinter : public Device {
public:
    ColorPrinter(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class Scanner : public Device {
public:
    Scanner(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};
