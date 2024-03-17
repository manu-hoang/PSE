#pragma once

#include "System.h"
#include "Device.h"
#include <fstream>
#include <sstream>

string getQueueInfo(Device* &device);

string getCurrentInfo(Device* &device);

void writeDeviceInfo(System& system);

void device_print_message(Device &device, Job* &job);