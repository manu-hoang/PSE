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


//Auxiliary function for internal use only

Device* new_device(string name, int emission, PrintingEnum type, int speed, int cost){

    if(type == bw){return new BlackWhitePrinter(name,emission,speed,cost);}

    else if (type == color){return new ColorPrinter(name,emission,speed,cost);}

    else if (type == scan){return new Scanner(name,emission,speed,cost);}

    return new Device("invalid", 1, 1, 1);
}


//Auxiliary function for internal use only

Job* new_job(int jobNumber, int pageCount, PrintingEnum type, const string& userName){

    if(type == bw){return new BlackWhiteJob(jobNumber,pageCount,userName);}

    else if (type == color){return new ColorJob(jobNumber,pageCount,userName);}

    else if (type == scan){return new ScanJob(jobNumber,pageCount,userName);}

    return new Job(1, 1, "invalid");
}










SuccessEnum SystemImporter::importSystem(const char * inputfilename, std::ostream& errStream, System& system) {

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
                    bool dont_add = false;


                    string name = "";
                    int emission = 0;
                    PrintingEnum type = invalid;
                    int speed = 0;
                    int cost = 0;


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
                        else if (attrValue == "type" ){
                            if(attrText == "bw"){
                                type = bw;
                            }
                            else if (attrText == "color"){
                                type = color;
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid type value,"
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else if (attrValue == "cost"){
                            if(isInteger(attrText)){
                                cost = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid cost value,"
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
                        Device* device = new_device(name, emission, type, speed,cost);
                        system.addDevice(device);
                    }

                }

                else if (element == "JOB"){
                    bool dont_add = false;


                    int jobNumber = 0;
                    int pageCount = 0;
                    PrintingEnum type = invalid;
                    string userName = "";


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
                        else if (attrValue == "type" ){
                            if(attrText == "bw"){
                                type = bw;
                            }
                            else if (attrText == "color"){
                                type = color;
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid type value,"
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
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
                        Job* job = new_job(jobNumber, pageCount, type, userName);
                        system.addJob(job);
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