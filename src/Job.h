#include "string"

using namespace std;

class Job {
private:
    int jobNumber;
    int pageCount;
    string userName;

public:
    Job(int jobNumber, int pageCount, string userName): jobNumber(jobNumber), pageCount(pageCount), userName(userName){

    }

};