#pragma once

#include <iostream>
#include <string>
#include "fstream"
#include <cctype>

// Parser
#include "../tinyxml/tinyxml.h"

#include "System.h"

// TODO: change input load function to return different success / failure states
enum SuccessEnum {ImportAborted, PartialImport, Success};

/**
// Read an XML description of a printing system(s) from the given filename and load it into the system class
// Currently only returns 0 if success, 1 if failure
//
//\n REQUIRE(system.properlyInitialized(), "system wasn't initialized when passed to input load function");
*/
int load(const char* filename, System &system);