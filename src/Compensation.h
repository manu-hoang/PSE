#pragma once
#include "string"

using namespace std;


class Compensation {
public:
    /**
     Compensation Initializer
    */
    Compensation(int compNumber, string name);

    bool properlyInitialized();

    /**
     \n REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getCompNumber");
     \n ENSURE(compNumber >= 0, "Compensation number must be a positive integer");
    */
    int getCompNumber();

    /**
     \n REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getName");
    */
    string getName();

    /**
     \n REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling increaseCount");
     \n ENSURE(counter >= 0, "Compensation counter must be a positive integer");
    */
    void increaseCount();

    /**
     \n REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getCounter");
     \n ENSURE(counter >= 0, "Compensation counter must be a positive integer");
    */
    int getCounter();

private:
    Compensation *_initCheck; //!use pointer to myself to verify whether I am properly initialized

    int compNumber;
    string name;

    int counter;
};