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

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling output");
     \n REQUIRE(documentStarted(), "Document was not started when calling output");
    */
    virtual void output(std::ostream& onStream, System &system);

    /**
    \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling statistics_output");
    */
    string advanced_textual_output_string(System &system);

protected:
    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling systemStart");
     \n REQUIRE(documentStarted(), "Document was not started when calling systemStart");
    */
    void systemStart (std::ostream& onStream, const std::string title);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling whitespace");
     \n REQUIRE(documentStarted(), "Document was not started when calling whitespace");
    */
    void whitespace (std::ostream &onStream);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling devicesStart");
     \n REQUIRE(documentStarted(), "Document was not started when calling devicesStart");
    */
    void devicesStart (std::ostream& onStream);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceName");
     \n REQUIRE(documentStarted(), "Document was not started when calling deviceName");
    */
    void deviceName (std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceEmissions");
     \n REQUIRE(documentStarted(), "Document was not started when calling deviceEmissions");
    */
    void deviceEmissions (std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceSpeed");
     \n REQUIRE(documentStarted(), "Document was not started when calling deviceSpeed");
    */
    void deviceSpeed (std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceType");
     \n REQUIRE(documentStarted(), "Document was not started when calling deviceType");
    */
    void deviceType (std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceCosts");
     \n REQUIRE(documentStarted(), "Document was not started when calling deviceCosts");
    */
    void deviceCosts (std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobsStart");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobsStart");
    */
    void jobsStart (std::ostream& onStream);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobNumber");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobNumber");
    */
    void jobNumber (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobOwner");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobOwner");
    */
    void jobOwner (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobDevice");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobDevice");
    */
    void jobDevice (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobStatus");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobStatus");
    */
    void jobStatus (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalPages");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobTotalPages");
    */
    void jobTotalPages (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalCO2");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobTotalCO2");
    */
    void jobTotalCO2 (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalCost");
     \n REQUIRE(documentStarted(), "Document was not started when calling jobTotalCost");
    */
    void jobTotalCost (std::ostream& onStream, Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling compensationStart");
     \n REQUIRE(documentStarted(), "Document was not started when calling compensationStart");
    */
    void compensationStart (std::ostream& onStream);

    /**
     \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling systemEnd");
     \n REQUIRE(documentStarted(), "Document was not started when calling systemEnd");
    */
    void systemEnd (std::ostream& onStream);

private:
    SystemExporter * _initCheck; //! use pointer to myself to verify whether I am properly initialized
    bool _documentStarted;

};


class SimpleExporter : public SystemExporter {
public:
    /**
     *  Use Case 2.2: Simple output (new)
     *  \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling simple_output");
     *  \n REQUIRE(documentStarted(), "Document was not started when calling simple_output");
    */
    void output(std::ostream& onStream, System &system) override;
};


class AdvancedTextualExporter : public SystemExporter {
public:
    /**
     *  Use Case 2.3: Advanced textual output
     *  \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling advanced_textual_output");
     *  \n REQUIRE(documentStarted(), "Document was not started when calling advanced_textual_output");
    */
    void output(std::ostream& onStream, System &system) override;
};


class StatisticsExporter : public SystemExporter {
public:
    /**
     * Use Case 3.9: Statistical calculations
     * \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling statistics_output");
     * \n REQUIRE(documentStarted(), "Document was not started when calling statistics_output");
    */
    void output(std::ostream& onStream, System &system) override;
};

class GraphicsExporter : public SystemExporter {
public:
    /**
     * \n REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling graphics_output");
     * \n REQUIRE(documentStarted(), "Document was not started when calling graphics_output");
    */
    void output(std::ostream& onStream, System &system) override;
};

#endif
