#pragma once

#include "string"

using namespace std;

class Job {
private:
    int jobNumber;
    int pageCount;
    string userName;

    bool finished;

public:
    Job(int jobNumber, int pageCount, string userName): jobNumber(jobNumber), pageCount(pageCount), userName(userName){
        finished = false;
    }

    void process();

    bool getFinished();

    int getJobNumber() const;
    int getPageCount() const;
    const string &getUserName() const;
};