#include <iostream>
#include "System.h"
#include "PrinterInput.h"
#include "PrinterOutput.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {

    System system;

    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", myfile, system);
    myfile.close();

    ofstream output("in_output/output.txt");
    writeDeviceInfo(system);

    system.automatic_run(150);
}

/*
 * input check integer
 * tests dont work on labo pc
 * IF contracts
 * output tests quality
 * mock input / output
 * just google it
 */