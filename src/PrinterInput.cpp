#include <iostream>
#include <string>
#include "fstream"
using namespace std;

// Parser
#include "../tinyxml/tinyxml.h"

#include "System.h"

int load(const char* filename, System &system) {

    // load input file
    TiXmlDocument doc;
    if(!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    // load error file
    std::ofstream outputFile("src/inputError.txt"); // create a new output file or overwrite an existing one

    // check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file"<<endl;
    }


    // check for root element
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }

    // read file
    TiXmlElement* elem = root->FirstChildElement();
    while (elem != NULL) {
        string element = elem->Value();


        if (element == "DEVICE"){
            // CHECK FOR ERRORS

            string name = "";
            int emission = 0;
            int speed = 0;

            for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string attrValue = attr->Value();
                string attrText = attr->GetText();

                if (attrValue == "name"){
                    name = attrText;
                }
                else if (attrValue == "emission"){
                    emission = stoi(attrText);
                }
                else if (attrValue == "speed"){
                    speed = stoi(attrText);
                }

            }

            Device *device_to_add = new Device(name,emission,speed);

            system.addDevice(device_to_add);

        }

        else if (element == "JOB"){
            // CHECK FOR ERRORS

            int jobNumber = 0;
            int pageCount = 0;
            string userName = "";

            for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string attrValue = attr->Value();
                string attrText = attr->GetText();

                if (attrValue == "jobNumber"){
                    jobNumber = stoi(attrText);
                }
                else if (attrValue == "pageCount"){
                    pageCount = stoi(attrText);
                }
                else if (attrValue == "userName"){
                    userName = attrText;
                }

            }

            Job *job_to_add = new Job(jobNumber,pageCount,userName);

            system.addJob(job_to_add);

        }
        else{
            cerr<<"UNRECOGNISED ELEMENT: "<<element<<endl;
            outputFile<<"UNRECOGNISED ELEMENT: "<<element<<endl;
        }
        elem = elem->NextSiblingElement();
    }

    // close input file
    doc.Clear();
    return 0;
}
