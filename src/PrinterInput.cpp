
#include "PrinterInput.h"
using namespace std;


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

int load(const char* filename, System &system) {

    // load input file
    TiXmlDocument doc;
    if(!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    // load error file
    std::ofstream outputFile("in_output/inputError.txt"); // create a new output file or overwrite an existing one

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

                        cerr<<"INCORRECT VALUE: "<<attrText<<endl;
                        outputFile<<"INCORRECT VALUE: "<<attrText<<endl;
                    }
                }
                else if (attrValue == "speed"){
                    if(isInteger(attrText)){
                        speed = stoi(attrText);
                    }
                    else{
                        dont_add = true;

                        cerr<<"INCORRECT VALUE: "<<attrText<<endl;
                        outputFile<<"INCORRECT VALUE: "<<attrText<<endl;
                    }
                }
                else{
                    elem = elem->NextSiblingElement();

                    cerr<<"UNRECOGNISED ATTRIBUTE: "<<attrValue<<endl;
                    outputFile<<"UNRECOGNISED ATTRIBUTE: "<<attrValue<<endl;
                }

            }
            if (!dont_add){
                Device *device_to_add = new Device(name,emission,speed);
                system.addDevice(device_to_add);
            }
            else {
                cerr<<"DEVICE not added"<<endl;
                outputFile<<"DEVICE not added"<<endl;
            }

        }

        else if (element == "JOB"){
            // CHECK FOR ERRORS

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

                        cerr<<"INCORRECT VALUE: "<<attrText<<endl;
                        outputFile<<"INCORRECT VALUE: "<<attrText<<endl;
                    }
                }
                else if (attrValue == "pageCount"){
                    if(isInteger(attrText)){
                        pageCount = stoi(attrText);
                    }
                    else{
                        dont_add = true;

                        cerr<<"INCORRECT VALUE: "<<attrText<<endl;
                        outputFile<<"INCORRECT VALUE: "<<attrText<<endl;
                    }
                }
                else if (attrValue == "userName"){
                    userName = attrText;
                }

            }

            if (!dont_add){
                Job *job_to_add = new Job(jobNumber,pageCount,userName);
                system.addJob(job_to_add);
            }
            else {
                cerr<<"DEVICE not added"<<endl;
                outputFile<<"DEVICE not added"<<endl;
            }

        }
        else{
            cerr<<"UNRECOGNISED ELEMENT: "<<element<<endl;
            outputFile<<"UNRECOGNISED ELEMENT: "<<element<<endl;
        }
        elem = elem->NextSiblingElement();
    }

    system.link_jobs();

    // close input file
    doc.Clear();
    return 0;
}
