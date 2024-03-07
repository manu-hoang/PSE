#include <vector>
#include "string"
#include "Job.h"

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

    Job* current_job;
    vector<Job*> jobs;
    double printing_time; // time to complete current job (seconds)

public:
    Device(string name, int emissions, int speed): name(name), emissions(emissions), speed(speed){
        busy = false;
    }

    void print_page();
    void print_message(Job *&job);

    void add_job(Job *&job);
    Job* getCurrentJob();
    void update_current_job(int current_time);

    double get_printing_time();

    //Functions used for PrinterOutput.cpp
    const string &getName() const;
    int getEmissions() const;
    string getQueueInfo();
    string getCurrentInfo();

    void setBusy(bool busy);
    bool getBusy();
    //
};

