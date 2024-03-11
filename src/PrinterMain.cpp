#include <iostream>
#include "System.h"
#include "PrinterInput.h"
#include "PrinterOutput.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {

    System system;

    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system);
    system.link_jobs();

    ofstream output("./src/output.txt");
    writeDeviceInfo(system, output);

    system.automatic_run(60);


}

