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

Device* new_device(string name, int emission, DeviceEnum type, int speed, int cost){

    if(type == bw_device){return new BlackWhitePrinter(name,emission,speed,cost);}

    else if (type == color_device){return new ColorPrinter(name,emission,speed,cost);}

    else if (type == scan_device){return new Scanner(name,emission,speed,cost);}

    return nullptr;
}


//Auxiliary function for internal use only

Job* new_job(int jobNumber, int pageCount, JobEnum type, const string& userName, int compNumber){

    if(type == bw_job){return new BlackWhiteJob(jobNumber,pageCount,userName,compNumber);}

    else if (type == color_job){return new ColorJob(jobNumber,pageCount,userName,compNumber);}

    else if (type == scan_job){return new ScanJob(jobNumber,pageCount,userName,compNumber);}

    return nullptr;
}


//Auxiliary function for internal use only

bool consistency_check(std::ostream& errStream, System& system){
    bool consistent = true;

    // Consistency check devices
    for(auto device : system.getDevices()){
        if(device->get_emissions() < 0 || device->get_type() == invalid_device || device->get_speed() < 0 || device->getCosts() < 0){
            errStream << "Device did not pass consistency check" << endl;
            consistent = false;
        }
    }


    // Consistency check jobs
    for(auto job : system.getJobs()){
        if(job->getJobNumber() < 0 || job->getTotalPageCount() < 0 || job->get_type() == invalid_job || job->getCompNumber() < 0){
            errStream << "Job did not pass consistency check" << endl;
            consistent = false;
        }
    }


    // Consistency check compensations
    for(auto compensation : system.getCompensations()){
        if(compensation->getCompNumber() < 0){
            errStream << "Compensation did not pass consistency check" << endl;
            consistent = false;
        }
    }


    return consistent;
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
                    DeviceEnum type = invalid_device;
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
                                errStream << "XML PARTIAL IMPORT: Invalid emission value, "
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
                                errStream << "XML PARTIAL IMPORT: Invalid speed value, "
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else if (attrValue == "type" ){
                            if(attrText == "bw"){
                                type = bw_device;
                            }
                            else if (attrText == "color"){
                                type = color_device;
                            }
                            else if (attrText == "scan"){
                                type = color_device;
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid type value, "
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
                                errStream << "XML PARTIAL IMPORT: Invalid cost value, "
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute, "
                                         "got <" << attrValue <<  "> ... </" << attrValue << ">." << endl;
                            endResult = PartialImport;
                        }

                    }

                    if (!dont_add){
                        Device* device = new_device(name, emission, type, speed,cost);

                        if(device != nullptr){
                            system.addDevice(device);
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid device" << endl;
                            endResult = PartialImport;
                        }

                    }

                }

                else if (element == "JOB"){
                    bool dont_add = false;


                    int jobNumber = 0;
                    int pageCount = 0;
                    JobEnum type = invalid_job;
                    string userName = "";

                    int compNumber = 0;


                    for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                        string attrValue = attr->Value();
                        string attrText = attr->GetText();

                        if (attrValue == "jobNumber"){
                            if(isInteger(attrText)){
                                jobNumber = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid jobNumber value, "
                                             "got: " << attrText << endl;
                            }
                        }
                        else if (attrValue == "pageCount"){
                            if(isInteger(attrText)){
                                pageCount = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid pageCount value, "
                                             "got: " << attrText << endl;
                            }
                        }
                        else if (attrValue == "type" ){
                            if(attrText == "bw"){
                                type = bw_job;
                            }
                            else if (attrText == "color"){
                                type = color_job;
                            }
                            else if (attrText == "scan"){
                                type = scan_job;
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid type value, "
                                             "got: " << attrText << endl;
                                endResult = PartialImport;
                            }
                        }
                        else if (attrValue == "userName"){
                            userName = attrText;
                        }
                        else if (attrValue == "compNumber"){
                            if(isInteger(attrText)){
                                compNumber = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid jobNumber value, "
                                             "got: " << attrText << endl;
                            }
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute, "
                                         "got <" << attrValue <<  "> ... </" << attrValue << ">." << endl;
                            endResult = PartialImport;
                        }
                    }

                    if (!dont_add){
                        Job* job = new_job(jobNumber, pageCount, type, userName, compNumber);

                        if(job != nullptr){
                            system.addJob(job);
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid job" << endl;
                            endResult = PartialImport;
                        }
                    }
                }

                else if (element == "COMPENSATION"){
                    bool dont_add = false;

                    int compNumber = 0;
                    string name = "";


                    for (TiXmlElement* attr = elem->FirstChildElement(); attr != NULL; attr = attr->NextSiblingElement()) {
                        string attrValue = attr->Value();
                        string attrText = attr->GetText();

                        if (attrValue == "compNumber"){
                            if(isInteger(attrText)){
                                compNumber = stoi(attrText);
                            }
                            else{
                                dont_add = true;
                                errStream << "XML PARTIAL IMPORT: Invalid jobNumber value, "
                                             "got: " << attrText << endl;
                            }
                        }
                        else if (attrValue == "name"){
                            name = attrText;
                        }
                        else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute, "
                                         "got <" << attrValue <<  "> ... </" << attrValue << ">." << endl;
                            endResult = PartialImport;
                        }
                    }

                    if (!dont_add){
                        auto* compensation = new Compensation(compNumber, name);

                        system.addCompensation(compensation);
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

    bool consistent = consistency_check(errStream, system);

    if(!consistent){
        errStream << "Consistency check failed" << endl;
        endResult = PartialImport;
    }

    doc.Clear();

    return endResult;
}