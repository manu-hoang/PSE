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

    Job* getCurrentJob();

    void add_job(Job *job);

    void writeOn(std::ostream& onStream);

    bool getBusy();

    queue<Job*> get_queue();

    int get_limit();

protected:
    void set_limit(int limit);

private:
    Device* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    string name;

    int CO2_limit;
    int emissions; // gram CO2 per page

    double speed; // pages per minute
    double cost;

    bool busy;

    queue<Job*> queue;

    double printing_time; // time to complete current job (seconds)
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
