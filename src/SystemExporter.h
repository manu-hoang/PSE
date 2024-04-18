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
    SystemExporter ();

    bool properlyInitialized();

    bool documentStarted();

    virtual void documentStart (std::ostream& onStream);

    virtual void documentEnd (std::ostream& onStream);

    void exportOn (std::ostream& onStream, System &system);

protected:
    virtual void sectionStart (std::ostream& onStream, const std::string sectionTitle);
    virtual void sectionEnd (std::ostream& onStream);
    virtual void boardStart (std::ostream& onStream);
    virtual void boardEnd (std::ostream& onStream);
    virtual void rowStart (std::ostream& onStream, const int row);
    virtual void rowEnd (std::ostream& onStream);
    virtual void cell (std::ostream& onStream, const char cellMarker);
    virtual void announceWinner (std::ostream& onStream, const char winnerMarker);

private:
    SystemExporter * _initCheck; //! use pointer to myself to verify whether I am properly initialized
    bool _documentStarted;

};

// Closing of the ``header guard''.
#endif