#pragma once

#include "string"

using namespace std;

class Job {
private:
    int jobNumber;
    int pageCount;
    int pagesToPrint;
    string userName;

    int start_time;
    bool finished;

public:
    Job(int jobNumber, int pageCount, string userName): jobNumber(jobNumber), pageCount(pageCount), userName(userName){
        finished = false;
        pagesToPrint = pageCount;
    }

    void print_page();

    void setStartTime(int time);
    int getStartTime();
    bool getFinished();
    int getJobNumber() const;
    int getPageCount() const;
    const string &getUserName() const;
};