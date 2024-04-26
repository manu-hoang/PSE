#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

bool DirectoryExists(const std::string dirname);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);