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

#define UI_PADDING 3
#define UI_COLUMN_WIDTH 22
#define UI_ROW_HEIGHT 21
#define UI_MENUE_HEIGHT 42
#define UI_X_DIVIDER 74
#define UI_Y_DIVIDER 20

//SD Card Control Pin
#define SD_CONTROL_PIN  52

//Wifi Control Pin
#define ESP_CONTROL_PIN 17

//FS1000A
#define RTX_DATA_PIN 16
#define RTS_DATA_PIN 15
#define RC_SOCKETS 4
#define RC_SIGNALS 5
#define RC_REPEAT 5

//Arduino JSON
#define ARDUINOJSON_ENABLE_PROGMEM 1

//Settings
#define DEBUG_RESET false

//Tact
#define TASK_FRQ_SEC 1
#define SENS_FRQ_SEC 5
#define HALTSTATE 20
//Log
#define SENS_VALUES_MIN (60 / SENS_FRQ_SEC) //every 5 sec
#define SENS_VALUES_HOUR 60 //every Minute
#define SENS_VALUES_DAY 96 // every 15 Minutes
#define SENS_VALUES_MONTH 56// every 12 Hours
#define SENS_VALUES_YEAR 52 // every week

//Sensors
#define SENS_NUM 10

//Rules Enginge
//Trigger Categories and number for each category
#define TRIGGER_TYPES 11
#define TRIGGER_SETS 8

//Number of Rulesssets
#define RULESETS_NUM 32

//Number of Actions
#define ACTIONS_NUM 18
#define ACTIONCHAINS_NUM 16
#define ACTIONCHAIN_LENGTH 6

//Task Manager
#define TASK_QUEUE_LENGTH 120 //MAX 255!!!
#define ACTIONCHAIN_TASK_MAXDURATION (TASK_QUEUE_LENGTH / ACTIONCHAIN_LENGTH)
#define TASK_PARALLEL_SEC 6

//Internal Temperatur Sensor
#define DHT_DATA_PIN 53
#define DHT_TYPE DHT22

//Relais
#define OUT_RELAY_1 2 
#define OUT_RELAY_2 3 
#define OUT_RELAY_3 4 
#define OUT_RELAY_4 5 

//Front Panel
#define IN_MOS_1 A0
#define IN_MOS_2 A1
#define IN_MOS_3 A2
#define IN_MOS_4 A3
#define IN_TOP_1 10
#define IN_TOP_2 11
#define IN_TOP_3 12
#define IN_TOP_4 13

//Top Panel
#define OUT_TOP_1 6
#define OUT_TOP_2 7
#define OUT_TOP_3 8
#define OUT_TOP_4 9

enum RelOp { SMALLER, EQUAL, GREATER };
enum BoolOp { AND, OR, NOT };
enum Interval { REALTIME, TENSEC, TWENTYSEC, THIRTYSEC, ONEMIN, TWOMIN, FIVEMIN, QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY };
enum DateRange { MINUTE, HOUR, DAY, MONTH, YEAR};

#define LOGLEVEL 5

#define LOGMSG(classname, msg, par1, par2, par3)   if(LOGLEVEL >1) { Serial.print(classname); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }
#define LOGMSG2(classname, msg, par1, par2, par3, par4)   if(LOGLEVEL >2) { Serial.print(classname); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.print(par3);  }
#define LOGDEBUG(classname, method, msg, par1, par2, par3)   if(LOGLEVEL >3) { Serial.print(classname); Serial.print(" "); Serial.print(method); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }
#define LOGDEBUG2(classname, method, msg, par1, par2, par3)   if(LOGLEVEL >4) { Serial.print(classname); Serial.print(" "); Serial.print(method); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }

#endif

