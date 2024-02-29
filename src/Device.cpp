#include "Device.h"

void Device::toggle_busy() {
    if(!this->busy){
        busy = true;
    }
    else {
        busy = false;
    }
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
    return currentinfo;
}