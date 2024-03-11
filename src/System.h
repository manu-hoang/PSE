#pragma once

#include "vector"

#include "Device.h"
#include "Job.h"

class System {
private:
    vector<Device*> _devices;
    vector<Job*> _jobs;

    int current_time;

public:
    System(){
        _devices = {};
        _jobs = {};
        current_time = 0;
    };

    void link_jobs();

    void automatic_run(int seconds);

    void update_all_devices();

    void process_all_jobs();

    int get_current_time() const;









    void addDevice(Device* &device);
    void addJob(Job* &job);

    const std::vector<Device*>& getDevices() const;
    const vector<Job *> &getJobs() const;


};