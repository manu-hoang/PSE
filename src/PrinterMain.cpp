#include <iostream>
#include <fstream>
#include "System.h"
#include "SystemImporter.h"
#include "SystemExporter.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {

    System system;

    SystemExporter exporter;
    exporter.documentStart(cout);

    // input parser
    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/Use_Case_1.2_Reading_printers_and_jobs_with_different types.xml", myfile, system);
    myfile.close();

    // main loop
    system.automated_processing();

    exporter.exportOn(cout, system);
    exporter.documentEnd(cout);
}

/*
 * tests dont work on labo pc
 * IF contracts
 * mock input / output
 * just google it
 *
 * Step 1.2 [No device exists for the specified job type] Print an error message that the job could not be printed.
 */