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
#define TOP1 14
#define TOP2 15
#define TOP3 16
#define TOP4 17

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

//Number of Rulesssets
#define RULES 32

//Number of Actions
#define ACTIONS 8

enum BoolOp { SMALLER, EQUAL, GREATER };
enum Interval { QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY };

#endif

