#pragma once
#include "string"

using namespace std;


class Compensation {
public:

    Compensation(int compNumber, string name);

    bool properlyInitialized();

    int getCompNumber();

    string getName();

private:
    Compensation *_initCheck; //!use pointer to myself to verify whether I am properly initialized

    int compNumber;

    string name;
};