#include "System.h"
#include "iostream"

void link_jobs(System* system){

    // TODO: Change later, dont know how jobs are divided yet
    Device* device = system->getDevices()[0];
    vector<Job*> jobs = system->getJobs();

    while(!jobs.empty()){
        device->add_job(jobs[0]);
        jobs.erase(jobs.begin());
    }

    device->update_current_job(system->get_current_time());
}

void System::automatic_run(int seconds) {

    // divide jobs to their respective printers
    // (currently just printers[0])
    link_jobs(this);

    while (current_time <= seconds){

        update_all_devices();

        process_all_jobs();

        current_time++;
    }

}

void System::update_all_devices() {
    for(auto device : _devices) {
        device->update_current_job(current_time);
    }
}


void System::process_all_jobs() {

    for(auto device : _devices){

        if(!device->getBusy()){
            return;
        }

        auto current_job = device->getCurrentJob();

        // job finish time
        double finish_time = current_job->getStartTime() + device->get_printing_time();


        if(current_time >= finish_time){

            while(!current_job->getFinished()) {
                device->print_page();
            }
        }

    }
}




















void System::addDevice(Device* &device) {
    this->_devices.push_back(device);
}

void System::addJob(Job* &job) {
    this->_jobs.push_back(job);
}

const std::vector<Device *> &System::getDevices() const{
    return _devices;
}

const vector<Job *> &System::getJobs() const {
    return _jobs;
}

int System::get_current_time() const {
    return this->current_time;
}