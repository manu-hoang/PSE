#include "Job.h"

void Job::print_page() {

    pageCount--;

    if(pageCount == 0){
        finished = true;
    }
}

int Job::getJobNumber() const {
    return jobNumber;
}

int Job::getPageCount() const {
    return pageCount;
}

const string &Job::getUserName() const {
    return userName;
}

bool Job::getFinished() {
    return finished;
}

void Job::set_start_time(int time) {
    this->start_time = time;
}
