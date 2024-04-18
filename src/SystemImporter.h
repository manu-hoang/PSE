//============================================================================
//
// Note:    The following code is heavily inspired by the TicTacToe example we received on the Ansymore website.
//
// Source: https://github.com/sergedemeyer/TicTacToe_Git
// Name        : TicTacToeImporter.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef SystemImporter_H
#define SystemImporter_H


#include <iostream>
#include "System.h"


enum SuccessEnum {ImportAborted, PartialImport, Success};


class SystemImporter {
public:

/**
// Read an XML description of an input file from inStream and process it into the system.
// If errors occur, report them on errStream.
// Return whether succesful in the errorcode:
//	- ImportAborted = System is unchanged; reason for abortion is reported on errStream
//  - PartialImport = Some semantic errors reported on errStream; state is partially imported and system might have changed
//  - Succes = No importer errors; no errors reported

 TODO: There is the additional requirement that every input file, has to be consistent:
       The attributes emissions, pageCount, cost, speed, compNumber, and jobNumber must not be negative.
        If a job specifies a compNumber, then there must exist a COMPENSATION element with that compNumber.
        Every COMPENSATION element needs to have a unique compNumber.
        Every JOB element needs to have a unique jobNumber.
        Any and all input files that do not conform to the above requirements are not valid.
*/
    static SuccessEnum importSystem(const char * inputfilename, std::ostream& errStream, System& system);

};


// Closing of the ``header guard''.
#endif