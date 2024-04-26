#include "Compensation.h"
#include "contracts/DesignByContract.h"

Compensation::Compensation(int compNumber, string name) : compNumber(compNumber), name(name) {
    _initCheck = this;
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

bool Compensation::properlyInitialized() {
    return _initCheck == this;
}