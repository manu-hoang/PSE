#include "System.h"
#include "iostream"

void System::link_jobs() {
    // TODO: Change later, dont know how jobs are divided yet
    Device* device = _devices[0];

    while(!_jobs.empty()){
        device->add_job(_jobs[0]);
        _jobs.erase(_jobs.begin());
    }

    device->update_current_job(current_time);
}


void System::automatic_run(int seconds) {
    update_all_devices();

    while (current_time <= seconds){

        process_all_jobs();
        update_all_devices();

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