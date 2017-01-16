// Definitions.h

#ifndef _DEFINITIONS_h
#define _DEFINITIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define DHTPIN 13
#define DHTTYPE DHT22

//Relais
#define RELAY1 4 
#define RELAY2 3 
#define RELAY3 5 
#define RELAY4 2 

//Front Panel
#define MOS1 A0
#define MOS2 A1
#define MOS3 A2
#define MOS4 A3

//Top Panel
#define TOP1 15
#define TOP2 16
#define TOP3 17
#define TOP4 18

#define BACKGROUNDCOLOR VGA_BLACK

#define PADDING 3
#define COLUMN_WIDTH 22
#define ROW_HEIGHT 21
#define MENUE_HEIGHT 42
#define X_DIVIDER 74
#define Y_DIVIDER 20

//Sensors
#define SENSNUMBER 10

//Rules Enginge
//Trigger Categories and number for each category
#define TRIGCAT 11
#define TRIGNUMBER 16

//Index of each Category
#define TIMETRIGGER 0
#define INTTEMPTRIGGER 1
#define INTHUMTRIGGER 2
#define ANALOGTRIGGER1 3
#define ANALOGTRIGGER2 4
#define ANALOGTRIGGER3 5
#define ANALOGTRIGGER4 6
#define DIGITALTRIGGER1 7
#define DIGITALTRIGGER2 8
#define DIGITALTRIGGER3 9
#define DIGITALTRIGGER4 10

//Number of Rulesssets
#define RULES 32

//Number of Actions
#define ACTIONS 8

#endif

