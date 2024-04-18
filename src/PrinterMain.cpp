#include <iostream>
#include <fstream>
#include "System.h"
#include "SystemImporter.h"
#include "SystemExporter.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {

    System system;

    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", myfile, system);
    myfile.close();

/*    SystemExporter exporter;
    exporter.documentStart(cout);*/

    system.automatic_run(150);
}

/*
 * input check integer
 * tests dont work on labo pc
 * IF contracts
 * output tests quality
 * mock input / output
 * just google it
 *
 * Step 1.2 [No device exists for the specified job type] Print an error message that the job could not be printed.

 */