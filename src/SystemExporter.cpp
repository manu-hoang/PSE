//============================================================================
// Name        : TicTacToeExporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "contracts/DesignByContract.h"
#include "SystemExporter.h"

using namespace std;


SystemExporter::SystemExporter() {
    _initCheck = this;
    _documentStarted = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}


bool SystemExporter::properlyInitialized() {
    return _initCheck == this;
}

bool SystemExporter::documentStarted() {
    return _documentStarted;
}


void SystemExporter::exportOn (std::ostream& onStream, System &system) {
 /*   char col, row;

    // section start
    if (game.nrOfMoves() == 1) {
        this->sectionStart(onStream, "TicTacToe (1 move)");
    } else {
        this->sectionStart(onStream, "TicTacToe (" + std::to_string(game.nrOfMoves()) + " moves)");
    }


    if (game.getWinner() != ' ') {this->announceWinner(onStream, game.getWinner());}

    this->boardStart(onStream);
    for (row = minRow; row <= maxRow; row++) {
        this->rowStart(onStream, row - minRow + 1);
        for (col = minCol; col <= maxCol; col++) {
            this->cell(onStream, game.getMark(col, row));
        }
        this->rowEnd(onStream);
    };
    this->boardEnd(onStream);
    this->sectionEnd(onStream);*/
}


// Following are the hook methods to be overridden in subclasses

void SystemExporter::documentStart (std::ostream& onStream) {_documentStarted = true;}
void SystemExporter::documentEnd (std::ostream& onStream) {_documentStarted = false;}

void SystemExporter::sectionStart (std::ostream& onStream, const string sectionTitle) {
    onStream << sectionTitle << std::endl;}
void SystemExporter::sectionEnd (std::ostream& onStream) {}

void SystemExporter::boardStart (std::ostream& onStream) {
    onStream 	<< "    a   b   c   " << std::endl
                << "  ------------- " << std::endl;
}
void SystemExporter::boardEnd (std::ostream& onStream) {
    onStream << "  ------------- " << std::endl;
}

void SystemExporter::rowStart (std::ostream& onStream, const int row) {
    onStream << row;
}
void SystemExporter::rowEnd (std::ostream& onStream) {
    onStream << " |" << std::endl;
}

void SystemExporter::cell (std::ostream& onStream, char const cellMarker) {
    onStream << " | " << cellMarker;}

void SystemExporter::announceWinner (std::ostream& onStream, const char winnerMarker) {
    onStream << "   And the winner is '" << winnerMarker << "'" <<std::endl;}