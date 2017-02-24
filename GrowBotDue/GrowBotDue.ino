/*
 Name:		GrowBotDue.ino
 Created:	13.01.2017 21:11:47
 Author:	ogass
*/

// the setup function runs once when you press reset or power the board

//Core Libaries

#include <ArduinoJson.h>
#include "DataStore.h"
#include <memorysaver.h>
#include <UTouchCD.h>
#include <UTouch.h>
#include <UTFT.h>


#include <SD.h>
#include <SPI.h>
#include <RTCDue.h>
#include <DHT_U.h>
#include <DHT.h>

//Modules
#include "UserInterface.h"
#include "Relais.h"
#include "CurrentTime.h"
#include "Definitions.h"
#include "Sensor.h"
#include "Ruleset.h"
#include "Trigger.h"
#include "Action.h"



//Global Variables
int touch_x, touch_y;

extern uint8_t BigFont[];
extern uint8_t SmallFont[];

int color = 0;
word colorlist[] = { VGA_WHITE, VGA_BLACK, VGA_RED, VGA_BLUE, VGA_GREEN, VGA_FUCHSIA, VGA_YELLOW, VGA_AQUA, VGA_GRAY, VGA_SILVER };
int  bsize = 4;
bool unit = true;

//Tact Generator
long sensor_cycles = 0;
int cpu_current = 0;
int cpu_last = 0;

int rtc_current = 0;
int rtc_last = 0;

//Hardware Handles
//LCD, Touchscreen
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);
//Control Pins Touchscreen
UTouch  myTouch(44, 45, 46, 47, 48);
//DHT Hardware
DHT dht(DHTPIN, DHTTYPE);
//RealTimeClock
CurrentTime currenttime(RC);

//SD Card
Sd2Card card;
SdVolume volume;
SdFile root;

//Relaisboard 
RelaisBoard *relaisboard;

//Modules
//Sensors: Abstraction of all Sensors
Sensor *sensors[SENSNUMBER]; 

//Actions: Abstraction of all Actors 
Action *actions[ACTIONS];

//Trigger: Constraints for particular sensors
Trigger *trigger[TRIGCAT][TRIGNUMBER];

//Rulesets: Trigger Action Bundles
RuleSet *rulesets[RULES];

//User Interface: TFT User Interface
UserInterface myUI;

void setup() {
	Serial.begin(9600);

	currenttime.begin(); // initialize RTC
	currenttime.updateRTCdefault();
	currenttime.updateTimeObject();

	relaisboard = new RelaisBoard();
	
	//Initialize Sensors
	sensors[0] = new	DHTTemperature("Temp.", 'C', true);
	sensors[1] = new 	DHTHumidity("Humid.", '%', true);
	sensors[2] = new 	AnalogSensor("Moist.", MOS1, '%', true);
	sensors[3] = new 	AnalogSensor("Moist.", MOS2, '%', true);
	sensors[4] = new 	AnalogSensor("Mosit.", MOS3, '%', true);
	sensors[5] = new 	AnalogSensor("Moist.", MOS4, '%', true);
	sensors[6] = new 	DigitalSensor("TBD", TOP1, 'B', true);
	sensors[7] = new 	DigitalSensor("TBD", TOP2, 'B', true);
	sensors[8] = new 	DigitalSensor("TBD", TOP3, 'B', true);
	sensors[9] = new 	DigitalSensor("TBD", TOP4, 'B', true);

	//Intialize Actors
	actions[0] = new ActionWrapper<RelaisBoard>("Switch R1", relaisboard, &RelaisBoard::switchR1, true);
	actions[1] = new ActionWrapper<RelaisBoard>("Switch R2", relaisboard, &RelaisBoard::switchR2, true);
	actions[2] = new ActionWrapper<RelaisBoard>("Switch R3", relaisboard, &RelaisBoard::switchR3, true);
	actions[3] = new ActionWrapper<RelaisBoard>("Switch R4", relaisboard, &RelaisBoard::switchR4, true);
	actions[4] = new ActionWrapper<RelaisBoard>("Relais All Off", relaisboard, &RelaisBoard::allOff, true);
	actions[5] = new ActionWrapper<RelaisBoard>("Relais All On", relaisboard, &RelaisBoard::allOn, true);

	//Initialize Trigger
	for (int tcategory = 0; tcategory < TRIGCAT; tcategory++) {
		for (int tset = 0; tset < TRIGNUMBER; tset++) {
			if (tcategory == 0) trigger[tcategory][tset] = new TimeTrigger(tset);
			else {
				trigger[tcategory][tset] = new SensorTrigger(tset, sensors[tcategory - 1]);
			}
		}
	}

		//Initialize Rulesets
	for (uint8_t k = 0; k < RULES; k++) {
		rulesets[k] = new RuleSet(k);
	}


	// Initial LCD setup
	myGLCD.InitLCD();
	myGLCD.clrScr();

	myTouch.InitTouch();
	myTouch.setPrecision(PREC_MEDIUM);
	
	//Initialize User Interface (after everything has been initialized)
	myUI.drawBackground();
	myUI.drawMenue(1);
	myUI.drawFrame(1);

	//Test Data
	trigger[1][0]->threshold = 30;
	trigger[1][0]->active = true;
	trigger[1][0]->relop = SMALLER;
	trigger[1][0]->interval = QUARTER;

	trigger[1][1]->threshold = 37;
	trigger[1][1]->active = true;
	trigger[1][1]->relop = GREATER;
	trigger[1][1]->interval = QUARTER;

	for (uint8_t i = 0; i < NUMMINUTE; i++) sensors[0]->minute_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < NUMHOUR; i++) sensors[0]->hour_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < NUMDAY; i++) sensors[0]->day_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < NUMMONTH; i++) sensors[0]->month_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < NUMYEAR; i++) sensors[0]->year_values[i] = random(-25, 25);
	
	//SD Card
	if (!card.init(SPI_HALF_SPEED, SDCS)) {
		Serial.println("Error: Initialization of SD card failed.");
	}
	else {
		Serial.println("OK: SD card found.");
	}

	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		return;
	}
	else {
		Serial.println("OK: Volume found ");
	}
	DataStore::serialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	if (myTouch.dataAvailable())
	{
		myTouch.read();
		touch_x = myTouch.getX();
		touch_y = myTouch.getY();
		myUI.checkEvent(touch_x, touch_y);
	}

	//Refresh Interval of Clock every 5sec
	cpu_current = millis();
	if (cpu_current - cpu_last > 5000) {
		cpu_last = cpu_current;

		currenttime.updateTimeObject();
		rtc_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, currenttime.current_second);


		//Refresh Interval of Sensors, Triggers and Ruleset every 10sec based on RTC
		if (rtc_current - rtc_last >= 10) {
			rtc_last = rtc_current;
			sensor_cycles++;


			for (uint8_t i = 0; i < SENSNUMBER; i++) {
				sensors[i]->update();
			}
			
			for (uint8_t i = 0; i < RULES; i++) {
				rulesets[i]->executeAction();
			}

		}
		//Refresh Interval of Sensors, Triggers and Ruleset every 60sec based on RTC
		if (rtc_current - rtc_last >= 60) {
			myUI.draw();
		}
	}
}
