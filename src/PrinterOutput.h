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

void writeDeviceInfo(System& system);

void device_print_message(Device &device, Job* &job);

#endif //PROJECTTITLE_PRINTEROUTPUT_H
