//============================================================================
// Name        : TicTacToeImporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "contracts/DesignByContract.h"
#include "SystemImporter.h"
#include "../tinyxml/tinyxml.h"

using namespace std;


//Auxiliary function for internal use only

const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
    if (pElement == NULL) return "";

    TiXmlNode *elemNode = pElement->FirstChild();
    if (elemNode == NULL) return "";
    TiXmlText* text = elemNode->ToText();
    if(text == NULL) return "";
    return text->Value();
}

//Auxiliary function for internal use only

bool isInteger(string &str) {
    if(str.empty()){
        return false;
    }

    // Check if the first character is a minus sign, if so, start loop from next character
    int start = (str[0] == '-') ? 1 : 0;


    int length = str.length();
    for(int i = start; i < length; i++) {
        if(!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

//Auxiliary function for internal use only

bool isString(const std::string &str) {
    bool hasNonDigit = false;

    // Check each character
    for (char ch : str) {
        // Check if the character is not a digit and not a space
        if (!isdigit(ch) && !isspace(ch) && ch != '.' && ch != '-') {
            hasNonDigit = true;
            break;
        }
    }

    return hasNonDigit;
}

//Below is a static member function but one cannot repeat the static keyword in the implementation

SuccessEnum SystemImporter::importSystem(
        const char * inputfilename, std::ostream& errStream, System& system) {

    TiXmlDocument doc;
    SuccessEnum endResult = Success;

    REQUIRE(system.properlyInitialized(), "system wasn't initialized when passed to SystemImporter::importSystem");

    if(!doc.LoadFile(inputfilename)) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << endl;
        return ImportAborted;
    };

    for(TiXmlElement* root = doc.FirstChildElement();
        root != NULL; root = root->NextSiblingElement()) {
        string rootName = root->Value();
        if (rootName != "SYSTEM") {
            errStream << "XML PARTIAL IMPORT: Expected <SYSTEM> ... </SYSTEM> and got <"
                      << rootName <<  "> ... </" << rootName << ">." << endl;
            endResult = PartialImport;
        }
        else {
            TiXmlElement* elem = root->FirstChildElement();
            while (elem != NULL) {
                string element = elem->Value();

                if (element == "DEVICE"){

                    string name = "";
                    int emission = 0;

                    int speed = 0;
                    bool dont_add = false;

                    for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                        string attrValue = attr->Value();
                        string attrText = attr->GetText();

                        if (attrValue == "name"){
                            name = attrText;
                        }
                        else if (attrValue == "emission" ){
                            if(isInteger(attrText)){
                                emission = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid emission value,"
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else if (attrValue == "speed"){
                            if(isInteger(attrText)){
                                speed = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid speed value,"
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute,"
                                         "got <" << attrValue <<  "> ... </" << attrValue << ">." << endl;
                            endResult = PartialImport;
                        }

                    }

                    if (!dont_add){
                        Device *device_to_add = new Device(name,emission,speed);
                        system.addDevice(device_to_add);
                    }
                }

                else if (element == "JOB"){

                    int jobNumber = 0;
                    int pageCount = 0;
                    string userName = "";
                    bool dont_add = false;

                    for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                        string attrValue = attr->Value();
                        string attrText = attr->GetText();

                        if (attrValue == "jobNumber"){
                            if(isInteger(attrText)){
                                jobNumber = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid jobNumber value,"
                                             "got: " << attrText << endl;
                            }
                        }
                        else if (attrValue == "pageCount"){
                            if(isInteger(attrText)){
                                pageCount = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid pageCount value,"
                                             "got: " << attrText << endl;
                            }
                        }
                        else if (attrValue == "userName"){
                            userName = attrText;
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute,"
                                         "got <" << attrValue <<  "> ... </" << attrValue << ">." << endl;
                            endResult = PartialImport;
                        }
                    }

                    if (!dont_add){
                        Job *job_to_add = new Job(jobNumber,pageCount,userName);
                        system.addJob(job_to_add);
                    }
                }

                else{
                    errStream << "XML PARTIAL IMPORT: Expected <DEVICE> ... </DEVICE> or <JOB> ... </JOB> "
                                 "and got <" << element <<  "> ... </" << element << ">." << endl;
                    endResult = PartialImport;
                }
                elem = elem->NextSiblingElement();
            }
        }
    }

    system.link_jobs();

    doc.Clear();

    return endResult;
}