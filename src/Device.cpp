#include "Device.h"
#include "PrinterOutput.h"
#include "iostream"

void Device::update_current_job(int time){

    if(current_job == nullptr){

        if(jobs.empty()) {
            return; // nothing to update
        }

        else {
            current_job = jobs[0];
            jobs.erase(jobs.begin());

            current_job->setStartTime(time);

            //amount of pages     // pages per second
            this->printing_time = current_job->getPageCount() / (this->speed/60);

            busy = true;
            return;
        }

    }

    if(current_job->getFinished()){
        current_job = nullptr;
        busy = false;
        update_current_job(time);
    }
}

void Device::print_page() {
    // Use Case 3.1: Manual processing
    current_job->print_page();

    if(current_job->getFinished()){
        device_print_message(*this, current_job);
    }
}


const string &Device::getName() const {
    return name;
}

int Device::getEmissions() const {
    return emissions;
}

void Device::setBusy(bool boolean) {
    this->busy = boolean;
}

bool Device::getBusy() {
    return busy;
}

void Device::add_job(Job *&job) {
    this->busy = true;
    this->jobs.push_back(job);
}

double Device::get_printing_time() {
    return printing_time;
}

Job *Device::getCurrentJob() {
    return current_job;
}

vector<Job *> Device::getJobs() {
    return jobs;
}
