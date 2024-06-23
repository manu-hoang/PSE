//============================================================================
//
// Note:    The following code is heavily inspired by the TicTacToe example we received on the Ansymore website.
//
// Source: https://github.com/sergedemeyer/TicTacToe_Git
// Name        : TicTacToeExporter.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef SystemExporter_H
#define SystemExporter_H


#include <iostream>
#include "System.h"


class SystemExporter {
public:

    /**
     \n SystemExporter initializer
    */
    SystemExporter ();

    bool properlyInitialized();

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentStarted");
    */
    bool documentStarted();

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentStart");
     \n ENSURE(documentStarted(), "Failed post condition documentStart");
    */
    virtual void documentStart (std::ostream& onStream);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentEnd");
     \n ENSURE(documentStarted(), "Failed post condition documentEnd");
    */
    virtual void documentEnd (std::ostream& onStream);


    virtual void output(std::ostream& onStream, System &system);

    /**
    \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling statistics_output");
    */
    string advanced_textual_output_string(System &system);

protected:
    void systemStart (std::ostream& onStream, const std::string title);

    void whitespace (std::ostream &onStream);

    void devicesStart (std::ostream& onStream);

    void deviceName (std::ostream& onStream, Device* device);
    void deviceEmissions (std::ostream& onStream, Device* device);
    void deviceSpeed (std::ostream& onStream, Device* device);
    void deviceType (std::ostream& onStream, Device* device);
    void deviceCosts (std::ostream& onStream, Device* device);

    void jobsStart (std::ostream& onStream);

    void jobNumber (std::ostream& onStream, Job* job);
    void jobOwner (std::ostream& onStream, Job* job);
    void jobDevice (std::ostream& onStream, Job* job);
    void jobStatus (std::ostream& onStream, Job* job);
    void jobTotalPages (std::ostream& onStream, Job* job);
    void jobTotalCO2 (std::ostream& onStream, Job* job);
    void jobTotalCost (std::ostream& onStream, Job* job);

    void compensationStart (std::ostream& onStream);

    void systemEnd (std::ostream& onStream);

private:
    SystemExporter * _initCheck; //! use pointer to myself to verify whether I am properly initialized
    bool _documentStarted;

};

/**
 *  Use Case 2.2: Simple output (new)
 \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling simple_output");
*/
class SimpleExporter : public SystemExporter {
public:
    void output(std::ostream& onStream, System &system) override;
};

/**
 *  Use Case 2.3: Advanced textual output
 \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling advanced_textual_output");
*/
class AdvancedTextualExporter : public SystemExporter {
public:
    void output(std::ostream& onStream, System &system) override;
};


/**
 *  Use Case 3.9: Statistical calculations
 \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling statistics_output");
*/
class StatisticsExporter : public SystemExporter {
public:
    void output(std::ostream& onStream, System &system) override;
};

class GraphicsExporter : public SystemExporter {
public:
    void output(std::ostream& onStream, System &system) override;
};

// Closing of the ``header guard''.
#endif