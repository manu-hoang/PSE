#include <iostream>
#include "PrinterInput.cpp"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {
    // a
    REQUIRE((5 >= 3), "aaaaaaaa");

    System system;
    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system);
}

