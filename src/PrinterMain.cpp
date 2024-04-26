#include <iostream>
#include <fstream>
#include "System.h"
#include "SystemImporter.h"
#include "SystemExporter.h"
#include "contracts/DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {

    System system;

    // input parser
    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/CompleteInput.xml", myfile, system);
    myfile.close();

    // main loop

    /*    while (ttt_.notDone()) {
        ttt_.doMove(); REPLACE THIS WITH TIMESTEP
        ttt_.writeOn(myfile);
    }*/

    system.automated_processing();

    // simple output
    myfile.open("in_output/simple_output.txt");

    SystemExporter exporter;
    exporter.documentStart(myfile);
    exporter.simple_output(myfile, system);
    exporter.documentEnd(myfile);

    myfile.close();
}