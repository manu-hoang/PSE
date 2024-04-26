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
    SystemImporter::importSystem("./xml_files/CompleteInput.xml", myfile, system);
    myfile.close();

    // main loop
    system.automated_processing();

    exporter.simple_output(cout, system);
    exporter.documentEnd(cout);
}