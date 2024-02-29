#include "Job.h"

void Job::process() {
    while (pageCount >= 0){
        // print page
        pageCount--;
    }

    finished = true;
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
