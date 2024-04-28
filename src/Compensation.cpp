#include "Compensation.h"
#include "contracts/DesignByContract.h"

Compensation::Compensation(int compNumber, string name) : compNumber(compNumber), name(name) {
    REQUIRE(compNumber >= 0, "Compensation number must be a positive integer");

    counter = 0;

    _initCheck = this;
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

bool Compensation::properlyInitialized() {
    return _initCheck == this;
}

int Compensation::getCompNumber() {
    REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getCompNumber");
    ENSURE(compNumber >= 0, "Compensation number must be a positive integer");
    return compNumber;
}

string Compensation::getName() {
    REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getName");
    return name;
}

void Compensation::increaseCount() {
    REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling increaseCount");
    counter++;
    ENSURE(counter >= 0, "Compensation counter must be a positive integer");
}

int Compensation::getCounter() {
    REQUIRE(properlyInitialized(), "Compensation wasn't initialized when calling getCounter");
    ENSURE(counter >= 0, "Compensation counter must be a positive integer");
    return counter;
}
