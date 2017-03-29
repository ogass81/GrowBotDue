// Definitions.h

#ifndef _DEFINITIONS_h
#define _DEFINITIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define SERIAL_BUFFER_SIZE 256
//User Interface
#define BACKGROUNDCOLOR VGA_BLACK

#define PADDING 3
#define COLUMN_WIDTH 22
#define ROW_HEIGHT 21
#define MENUE_HEIGHT 42
#define X_DIVIDER 74
#define Y_DIVIDER 20

//SD Card Control Pin
#define SDCS  52

//Wifi Control Pin
#define ESPPIN 17

//FS1000A
#define FSAPIN 16

//Arduino JSON
#define ARDUINOJSON_ENABLE_PROGMEM 1

//Settings
#define HARDRESET false

//Tact
#define TASKFRQ 1
#define SENSORFRQ 5
//Log
#define NUMMINUTE (60 / SENSORFRQ) //every 5 sec
#define NUMHOUR 60 //every Minute
#define NUMDAY 96 // every 15 Minutes
#define NUMMONTH 56// every 12 Hours
#define NUMYEAR 52 // every week

//Sensors
#define SENSNUMBER 10

//Rules Enginge
//Trigger Categories and number for each category
#define TRIGCAT 11
#define TRIGNUMBER 8

//Number of Rulesssets
#define RULES 32

//Number of Actions
#define ACTIONS 16
#define ACTIONCHAINS 16
//Task Manager
#define TASKBUFFER 120 //MAX 255!!!
#define TASKSINCHAIN 6
#define MAXTASKSECONDS (TASKBUFFER / TASKSINCHAIN)
#define PARALLELTASKS 6

//Internal Temperatur Sensor
#define DHTPIN 53
#define DHTTYPE DHT22

//Relais
#define RELAY1 2 
#define RELAY2 3 
#define RELAY3 4 
#define RELAY4 5 

//Front Panel
#define MOS1 A0
#define MOS2 A1
#define MOS3 A2
#define MOS4 A3
#define FOD1 10
#define FOD2 11
#define FOD3 12
#define FOD4 13

//Top Panel
#define TOP1 6
#define TOP2 7
#define TOP3 8
#define TOP4 9

enum RelOp { SMALLER, EQUAL, GREATER };
enum BoolOp { AND, OR, NOT };
enum Interval { REALTIME, TENSEC, TWENTYSEC, THIRTYSEC, ONEMIN, TWOMIN, FIVEMIN, QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY };
enum DateRange { MINUTE, HOUR, DAY, MONTH, YEAR};

#endif

