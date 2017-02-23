/*
 Name:		GrowBotDue.ino
 Created:	13.01.2017 21:11:47
 Author:	ogass
*/

// the setup function runs once when you press reset or power the board

//Core Libaries
#include <memorysaver.h>
#include <UTouchCD.h>
#include <UTouch.h>
#include <UTFT.h>

#include <RTCDue.h>
#include <DHT_U.h>
#include <DHT.h>

//Modules
#include "UserInterface.h"
#include "RulesEngine.h"
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

String debug = "Debug";

//Hardware Handles
//LCD, Touchscreen
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);

//Control Pins Touchscreen
UTouch  myTouch(46, 47, 48, 49, 50);

//DHT Hardware
DHT dht(DHTPIN, DHTTYPE);
//Current Time Container
CurrentTime currenttime(RC);

//Relaisboard 
RelaisBoard relaisboard;


//Modules
//Sensors: Abstraction of all Sensors
Sensor *sensors[SENSNUMBER]; 

//Actions: Abstraction of all Actors 
Action *actions[ACTIONS];

//Trigger: Constraints for particular sensors
Trigger *trigger[TRIGCAT][TRIGNUMBER];

//Rulesets: Trigger Action Bundles
RulesSet *rulesets[RULES];

//RulesEngine: Overall Controller for automized behavior
RulesEngine *rulesengine;

//User Interface: TFT User Interface
TouchInterface myUI;



void setup() {
	Serial.begin(9600);

	currenttime.begin(); // initialize RTC
	currenttime.updateRTCdefault();
	
	relaisboard.allOff();


	//Initialize Sensors
	sensors[0] = new	DHTTemperature("Temp.", 'C', true);
	sensors[1] = new 	DHTHumidity("Humidity", '%', true);
	sensors[2] = new 	AnalogSensor("Moisture", MOS1, '%', true);
	sensors[3] = new 	AnalogSensor("Moisture", MOS2, '%', true);
	sensors[4] = new 	AnalogSensor("Mositure", MOS3, '%', true);
	sensors[5] = new 	AnalogSensor("Moisture", MOS4, '%', true);
	sensors[6] = new 	DigitalSensor("TBD", TOP1, 'B', true);
	sensors[7] = new 	DigitalSensor("TBD", TOP2, 'B', true);
	sensors[8] = new 	DigitalSensor("TBD", TOP3, 'B', true);
	sensors[9] = new 	DigitalSensor("TBD", TOP4, 'B', true);

	//Intialize Actors
	actions[0] = new ActionWrapper<RelaisBoard>("Switch R1", &relaisboard, &RelaisBoard::switchR1, true);
	actions[1] = new ActionWrapper<RelaisBoard>("Switch R2", &relaisboard, &RelaisBoard::switchR2, true);
	actions[2] = new ActionWrapper<RelaisBoard>("Switch R3", &relaisboard, &RelaisBoard::switchR3, true);
	actions[3] = new ActionWrapper<RelaisBoard>("Switch R4", &relaisboard, &RelaisBoard::switchR4, true);
	actions[4] = new ActionWrapper<RelaisBoard>("Relais All Off", &relaisboard, &RelaisBoard::allOff, true);
	actions[5] = new ActionWrapper<RelaisBoard>("Relais All Off", &relaisboard, &RelaisBoard::allOn, true);

	//Initialize Trigger
	for (int tcategory = 0; tcategory < TRIGCAT; tcategory++) {
		Serial.println(tcategory);
		for (int tset = 0; tset < TRIGNUMBER; tset++) {
			if (tcategory == 0) trigger[tcategory][tset] = new TimeTrigger(tset, &currenttime);
			else {
				trigger[tcategory][tset] = new SensorTrigger(tset, sensors[tcategory - 1]);
			}
		}
	}

	//Initialize Rulesets
	for (uint8_t k = 0; k < RULES; k++) {
		rulesets[k] = new RulesSet();
	}



	rulesengine = new RulesEngine();


	// Initial LCD setup
	myGLCD.InitLCD();
	myGLCD.clrScr();

	myTouch.InitTouch();
	myTouch.setPrecision(PREC_MEDIUM);

	Serial.println(F("Hardware initialized."));
	
	
	//Initialize User Interface (after everything has been initialized)
	myUI.drawBackground();
	myUI.drawMenue(1);
	myUI.drawFrame(1);
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
}
