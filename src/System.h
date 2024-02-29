#pragma once

#include "vector"

#include "Device.h"
#include "Job.h"

class System {
private:
    vector<Device*> _devices;
    vector<Job*> _jobs;

public:
    System(){
        _devices = {};
        _jobs = {};
    };

    void addDevice(Device* &device);
    void addJob(Job* &job);

    void process_job();

};