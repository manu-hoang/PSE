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

    void automatic_run(int seconds);

    void addDevice(Device* &device);
    void addJob(Job* &job);

    Device* find_available_printer();

    bool process_job(Job* &job);

    void process_all_jobs();

    const std::vector<Device*>& getDevices() const;


};