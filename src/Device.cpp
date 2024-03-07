#include "Device.h"
#include <sstream>
#include "iostream"


void Device::toggle_busy() {
    if(!this->busy){
        busy = true;
    }
    else {
        busy = false;
    }
}

void Device::print() {

    if(jobs.empty()) {
        cout << "yo device jobs queue is empty" << endl;
        return;
    }

    jobs[0]->process();
}


const string &Device::getName() const {
    return name;
}

int Device::getEmissions() const {
    return emissions;
}

string Device::getQueueInfo() {
    string queueinfo;
    return queueinfo;
}

string Device::getCurrentInfo() {
    string currentinfo;
    Job* currentjob = this->jobs[0];
    int jobnummer = currentjob->getJobNumber();
    string user = currentjob->getUserName();
    currentinfo = "[#" + to_string(jobnummer) + "|" + user + "]";
    return currentinfo;
}

bool Device::getBusy() {
    return busy;
}