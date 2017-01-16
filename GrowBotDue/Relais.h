// Relais.h

#ifndef _RELAIS_h
#define _RELAIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"

class RelaisBoard {
public:
	RelaisBoard();

	void allOff();
	void allOn();
	void switchR1();
	void switchR2();
	void switchR3();
	void switchR4();

	void switchR1R2();
	void switchR1R3();
	void switchR1R4();
	void switchR2R3();
	void switchR2R4();
	void switchR3R4();

	String getStatusR1();
	String getStatusR2();
	String getStatusR3();
	String getStatusR4();
};

#endif

