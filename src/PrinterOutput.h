//
// Created by michael on 7/03/24.
//


#ifndef PROJECTTITLE_PRINTEROUTPUT_H
#define PROJECTTITLE_PRINTEROUTPUT_H

#pragma once

#include "System.h"
#include "Device.h"
#include <fstream>
#include <sstream>

string getQueueInfo(Device* &device);
string getCurrentInfo(Device* &device);

void writeDeviceInfo(System& system, std::ofstream& file);

#endif //PROJECTTITLE_PRINTEROUTPUT_H
