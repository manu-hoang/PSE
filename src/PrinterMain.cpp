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

    // input parser
    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/CompleteInput.xml", myfile, system);
    myfile.close();

    myfile.open("in_output/advanced_textual_output.txt");
    exporter.documentStart(myfile);

    // main loop
    int seconds = 1; // total run time of the program
    system.divideJobs(); // divide all jobs to respective devices queue before loop (prevents multiple unnecessary divisions)
    for (int i = 0; i <= seconds; ++i) {
        system.tick();
        exporter.advanced_textual_output(myfile, system);
    }

    exporter.documentEnd(myfile);
    myfile.close();

/*    system.automated_processing();*/

    // simple output
    myfile.open("in_output/simple_output.txt");

    exporter.documentStart(myfile);
    exporter.simple_output(myfile, system);
    exporter.documentEnd(myfile);

    myfile.close();
}