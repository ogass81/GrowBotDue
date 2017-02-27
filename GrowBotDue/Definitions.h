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
#define RELAY1 19 
#define RELAY2 18 
#define RELAY3 17 
#define RELAY4 16 

#define SDCS  52


//Front Panel
#define MOS1 A0
#define MOS2 A1
#define MOS3 A2
#define MOS4 A3
#define FOD1 9
#define FOD2 10
#define FOD3 11
#define FOD4 12


//Top Panel
#define TOP1 5
#define TOP2 6
#define TOP3 7
#define TOP4 8

#define BACKGROUNDCOLOR VGA_BLACK

#define PADDING 3
#define COLUMN_WIDTH 22
#define ROW_HEIGHT 21
#define MENUE_HEIGHT 42
#define X_DIVIDER 74
#define Y_DIVIDER 20

//Sensors
#define SENSNUMBER 10

#define NUMMINUTE 12 //every 5 sec
#define NUMHOUR 60 //every Minute
#define NUMDAY 96 // every 15 Minutes
#define NUMMONTH 112// every 6 Hours
#define NUMYEAR 52 // every week


//Rules Enginge
//Trigger Categories and number for each category
#define TRIGCAT 11
#define TRIGNUMBER 8

//Number of Rulesssets
#define RULES 32

//Number of Actions
#define ACTIONS 8

//Arduino JSON
#define ARDUINOJSON_ENABLE_PROGMEM 1

enum RelOp { SMALLER, EQUAL, GREATER };
enum BoolOp { AND, OR, NOT };
enum Interval { REALTIME, TENSEC, TWENTYSEC, THIRTYSEC, ONEMIN, TWOMIN, FIVEMIN, QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY };
enum DateRange { MINUTE, HOUR, DAY, MONTH, YEAR};

#endif

