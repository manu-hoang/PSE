//============================================================================
// Name        : PrinterInput.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================


class PrinterInput {
public:
	PrinterInput();
	bool notDone();
	void doMove();
	int nrOfMoves();

private:
	int _nrOfMoves;
};
