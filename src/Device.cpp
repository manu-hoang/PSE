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

void Device::update_current_job(int time){

    if(current_job == nullptr and jobs.empty()){
        return; // nothing to update
    }

    if(current_job == nullptr and !jobs.empty()){
        current_job = jobs[0];
        jobs.erase(jobs.begin());

        current_job->setStartTime(time);
    }

    if(current_job->getFinished()){

        // output message Use Case 3.1
        print_message(jobs[0]);

        current_job = nullptr;
    }
}

void Device::print_page() {

    if(current_job == nullptr) {
        cout << "yo nothing to print" << endl;
        return;
    }

    current_job->print_page();
}


const string &Device::getName() const {
    return name;
}

int Device::getEmissions() const {
    return emissions;
}

string Device::getQueueInfo() {
    string queueinfo = "";
    int jobsammount = jobs.size();
    for (int i = 1; i < jobsammount ; ++i) {
        Job* currentjobinqueue = jobs[i];
        int  jobnummer = currentjobinqueue->getJobNumber();
        string userinqueue = currentjobinqueue->getUserName();
        queueinfo += "[#" + to_string(jobnummer) + "|" + userinqueue + "]\n";
    }
    return queueinfo;
}

string Device::getCurrentInfo() {
    string currentinfo;
    Job* currentjob = jobs[0];
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

                          //amount of pages     // pages per second
    this->printing_time = job->getPageCount() * (this->speed/60);

    if(current_job == nullptr) {
        current_job = job;
    }
    else {
        this->jobs.push_back(job);
    }

}

double Device::get_printing_time() {
    return printing_time;
}

Job *Device::getCurrentJob() {
    return current_job;
}
