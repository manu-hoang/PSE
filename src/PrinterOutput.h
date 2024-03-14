//
// Created by michael on 7/03/24.
//


#ifndef PROJECTTITLE_PRINTEROUTPUT_H
#define PROJECTTITLE_PRINTEROUTPUT_H

#pragma once

#include "System.h"
#include <fstream>
#include <sstream>

void writeDeviceInfo(const System& system, std::ofstream& file);

void device_print_message(Device &device, Job* &job);

#endif //PROJECTTITLE_PRINTEROUTPUT_H
