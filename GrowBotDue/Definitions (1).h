// Definitions.h

#ifndef _DEFINITIONS_h
#define _DEFINITIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define GROWBOT_FIRMWARE 1

#define SERIAL_BUFFER_SIZE 256

//SD Card Control Pin
#define SD_CONTROL_PIN  19

//Wifi Control Pin
#define ESP_CONTROL_PIN 8

//FS1000A
#define TX_DATA_PIN 14
#define RX_DATA_PIN 15
#define RC_SOCKETS 8
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
#define SENS_NUM 4

//Rules Enginge
//Trigger Categories and number for each category
#define TRIGGER_TYPES 5
#define TRIGGER_SETS 8

//Number of Rulesssets
#define RULESETS_NUM 32

//Number of Actions
#define ACTIONS_NUM 8
#define ACTIONCHAINS_NUM 16
#define ACTIONCHAIN_LENGTH 4

//Task Manager
#define TASK_QUEUE_LENGTH 120 //MAX 255!!!
#define ACTIONCHAIN_TASK_MAXDURATION (TASK_QUEUE_LENGTH / ACTIONCHAIN_LENGTH)
#define TASK_PARALLEL_SEC 4

//Internal Temperatur Sensor
#define DHT_DATA_PIN 18
#define DHT_TYPE DHT22

//Front Panel
#define IN_MOS_1 A0
#define IN_MOS_2 A1
#define OUT_MOS_1 9
#define OUT_MOS_2 10

//Top Panel
#define OUT_TOP_1 9
#define OUT_TOP_2 10
#define OUT_TOP_3 51
#define OUT_TOP_4 52

//LED
#define LED1 11
#define LED2 12
#define LED3 13

//NTP
#define NTP_PORT 4241
#define NTP_PACKET_SIZE 48
#define UDP_TIMEOUT 3000

//REST API 
#define REST_URI_DEPTH 4

enum RelOp { SMALLER, EQUAL, GREATER };
enum BoolOp { AND, OR, NOT };
enum Interval { REALTIME, TENSEC, TWENTYSEC, THIRTYSEC, ONEMIN, TWOMIN, FIVEMIN, QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY};
enum Scope { LIST, HEADER, DETAILS, AVG, DATE_MINUTE, DATE_HOUR, DATE_DAY, DATE_MONTH, DATE_YEAR, DATE_ALL};
enum TriggerTypes { TIME, SENSOR };

#define LOGLEVEL 5

#define LOGMSG(classname, msg, par1, par2, par3)   if(LOGLEVEL >1) { Serial.print(classname); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }
#define LOGMSG2(classname, msg, par1, par2, par3, par4)   if(LOGLEVEL >2) { Serial.print(classname); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.print(par3);  }
#define LOGDEBUG(classname, method, msg, par1, par2, par3)   if(LOGLEVEL >3) { Serial.print(classname); Serial.print(" "); Serial.print(method); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }
#define LOGDEBUG2(classname, method, msg, par1, par2, par3)   if(LOGLEVEL >4) { Serial.print(classname); Serial.print(" "); Serial.print(method); Serial.print(" "); Serial.print(msg); Serial.print(" "); Serial.print(par1); Serial.print(" "); Serial.print(par2); Serial.print(" "); Serial.println(par3); }

#endif

