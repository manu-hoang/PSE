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
