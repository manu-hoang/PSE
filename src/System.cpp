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

}

void System::automatic_run(int seconds) {

    // divide jobs to their respective printers
    // (currently just printers[0])
    link_jobs(this);

    while (current_time <= seconds){

        process_all_jobs();

        current_time++;
    }

}



void System::process_all_jobs() {

    for(auto device : _devices){

        Job* current_job = device->getCurrentJob();

        // job finish time
        double finish_time = current_job->getStartTime() + device->get_printing_time();

        if(current_time >= finish_time){
            while(!current_job->getFinished()) {current_job->print_page();}
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
