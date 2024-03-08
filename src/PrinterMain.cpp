#include <iostream>
#include "System.h"
#include "PrinterInput.h"
#include "PrinterOutput.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {
    // a
    REQUIRE((5 >= 3), "aaaaaaaa");

    System system;
    ofstream output("./src/output.txt");

    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system);
    writeDeviceInfo(system, output);

    //system.automatic_run(100);
}

