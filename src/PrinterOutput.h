#pragma once

#include "System.h"
#include "Device.h"
#include <fstream>
#include <sstream>

/**
\n REQUIRE(device->properlyInitialized(), "Device wasn't initialized when calling getCurrentInfo.");
*/
string getCurrentInfo(Device* &device);

/**
\n REQUIRE(device->properlyInitialized(), "Device wasn't initialized when calling getQueueInfo.");
*/
string getQueueInfo(Device* &device);

/**
   Function exports current job and queue to "in_output/output.txt"
    TODO: output file is currently hard coded (doesn't support multiple exports)
\n REQUIRE(system.properlyInitialized(), "System wasn't initialized when calling writeDeviceInfo.");
*/
void writeDeviceInfo(System& system);

/**
   Function prints message out in console and exports to "in_output/console_output.txt"
    TODO: output file is currently hard coded (doesn't support multiple exports)
\n REQUIRE(device.properlyInitialized(), "Device wasn't initialized when calling device_print_message.");
\n REQUIRE(job->properlyInitialized(), "Job wasn't initialized when calling device_print_message.");
*/
void device_print_message(Device &device, Job* &job);