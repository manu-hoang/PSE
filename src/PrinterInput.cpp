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

        if (element == "STATION"){

            // CHECK FOR ERRORS
            for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string attrValue = attr->Value();
                string attrText = attr->GetText();

                // Check if correct string
                if (attrValue != "naam" and attrValue != "type" and attrValue != "vorige" and attrValue != "volgende" and attrValue != "spoor"){
                    std::cerr << "Unrecognised STATION element: Station attribute NOT FOUND." << std::endl;
                }
                if ((attrText.length() != 1 or isupper(attrText[0]) == false)
                    and (attrValue == "naam" or attrValue == "vorige" or attrValue == "volgende")){
                    std::cerr << "Invalid STATION information: INVALID Station name." << std::endl;
                }

                // Check if integer
                long long unsigned int checker = 0;
                if (attrValue == "spoor") {
                    for (long long unsigned int j = 0; j < attrText.size(); ++j) {
                        if (isdigit(attrText[j])) {
                            checker++;
                        }
                    }
                    if (checker != attrText.size()) {
                        std::cerr << "Invalid STATION information: Spoor NOT INTEGER." << std::endl;
                    }
                }
            }

            // Create station
            string naam = elem->FirstChildElement("naam")->GetText();
            string type = elem->FirstChildElement("type")->GetText();
            string vorige = elem->FirstChildElement("vorige")->GetText();
            string volgende = elem->FirstChildElement("volgende")->GetText();
            int spoorNr = atoi(elem->FirstChildElement("spoor")->GetText());
            Station s(naam, type, vorige, volgende, spoorNr);

            metro.addStation(s);

        }

        else if (element == "TRAM"){

            // CHECK FOR ERRORS
            for(TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                string data = attr->Value();
                string attrValue = attr->Value();
                string attrText = attr->GetText();

                // Check if correct string
                if (attrValue != "lijnNr" and attrValue != "voertuigNr" and attrValue != "beginStation"
                    and attrValue != "type" and attrValue != "aantalDefecten" and attrValue != "reparatieTijd"){
                    std::cerr << "Unrecognised TRAM element: TRAM attribute NOT FOUND." << std::endl;
                }
                if((attrText.length() != 1 or isupper(attrText[0]) == false) and attrValue == "beginStation"){
                    std::cerr << "Invalid TRAM information: INVALID Station name." << std::endl;
                }

                // Check if integer
                long long unsigned int checker = 0;
                if (attrValue == "lijnNr") {
                    for (long long unsigned int j = 0; j < attrText.size(); ++j) {
                        if (isdigit(attrText[j])) {
                            checker++;
                        }
                    }
                    if (checker != attrText.size()) {
                        std::cerr << "Invalid TRAM information: Spoor NOT INTEGER." << std::endl;
                    }
                }

                // Check if types are correct
                if (attrValue == "type" and (attrText != "PCC" and attrText != "Stadslijner" and attrText != "Albatros")){
                    std::cerr << "Invalid TRAM information: INVALID Tram type." << std::endl;
                }
            }

            // Create tram
            int lijnNr = atoi(elem->FirstChildElement("lijnNr")->GetText());
            int vehicleNr = atoi(elem->FirstChildElement("voertuigNr")->GetText());
            string beginStation = elem->FirstChildElement("beginStation")->GetText();
            string type = elem->FirstChildElement("type")->GetText();

            if (type == "PCC") {
                int aantalDefecten = atoi(elem->FirstChildElement("aantalDefecten")->GetText());
                int reparatieTijd = atoi(elem->FirstChildElement("reparatieTijd")->GetText());
                Tram t(lijnNr, type, vehicleNr, beginStation,aantalDefecten,reparatieTijd);
                metro.addTram(t);
            } else {
                Tram t(lijnNr, type, vehicleNr, beginStation,0,0);
                metro.addTram(t);
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
