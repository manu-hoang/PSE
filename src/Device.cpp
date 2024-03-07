#include "Device.h"
#include <sstream>
#include "iostream"

void Device::print_message(Job* &job){
    string printer_name = this->getName();

    int job_number = job->getJobNumber();
    string job_username = job->getUserName();
    int job_pagecount = job->getPageCount();

    cout << "Printer " << printer_name << " finished job:" << endl;
    cout << "Number: " << job_number << endl;
    cout << "Submitted by: " << job_username << endl;
    cout << job_pagecount << " pages" << endl;
}

void Device::print_page() {

    if(jobs.empty()) {
        cout << "yo device jobs queue is empty" << endl;
        return;
    }

    jobs[0]->print_page();

    if(jobs[0]->getFinished()){

        // output message Use Case 3.1
        print_message(jobs[0]);

        jobs.erase(jobs.begin());
    }
}


const string &Device::getName() const {
    return name;
}

int Device::getEmissions() const {
    return emissions;
}

string Device::getQueueInfo() {
    string queueinfo;
    return queueinfo;
}

string Device::getCurrentInfo() {
    string currentinfo;
    Job* currentjob = this->jobs[0];
    int jobnummer = currentjob->getJobNumber();
    string user = currentjob->getUserName();
    currentinfo = "[#" + to_string(jobnummer) + "|" + user + "]";
    return currentinfo;
}

void Device::setBusy(bool boolean) {
    this->busy = boolean;
}

bool Device::getBusy() {
    return busy;
}

void Device::add_job(Job *&job) {
    this->jobs.push_back(job);

                          //amount of pages     // pages per second
    this->printing_time = job->getPageCount() * (this->speed/60);
}

double Device::get_printing_time() {
    return printing_time;
}
