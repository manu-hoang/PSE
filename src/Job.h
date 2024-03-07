#pragma once

#include "string"

using namespace std;

class Job {
private:
    int jobNumber;
    int pageCount;
    string userName;

    int start_time;
    bool finished;

public:
    Job(int jobNumber, int pageCount, string userName): jobNumber(jobNumber), pageCount(pageCount), userName(userName){
        finished = false;
    }

    void print_page();

    void set_start_time(int time);

    bool getFinished();

    int getJobNumber() const;
    int getPageCount() const;
    const string &getUserName() const;
};