#include <iostream>
#include <string>
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
            for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string attrValue = attr->Value();
                string attrText = attr->GetText();

                cout<<attrValue<<endl;
                cout<<attrText<<endl;

            }

        }

        else if (element == "TRAM"){

            // CHECK FOR ERRORS
            for(TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string data = attr->Value();
                string attrValue = attr->Value();
                string attrText = attr->GetText();

            }

        }

            // If not STATION or TRAM
        else {std::cerr << "Element not recognized (not STATION or TRAM)" << std::endl;}
        elem = elem->NextSiblingElement();
    }

    // close input file
    doc.Clear();
    return 0;
}
