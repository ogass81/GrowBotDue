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

	void R1On();
	void R1Off();
	void R2On();
	void R2Off();
	void R3On();
	void R3Off();
	void R4On();
	void R4Off();

	String getStatusR1();
	String getStatusR2();
	String getStatusR3();
	String getStatusR4();
};

#endif

