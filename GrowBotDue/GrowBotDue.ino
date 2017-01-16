/*
 Name:		GrowBotDue.ino
 Created:	13.01.2017 21:11:47
 Author:	ogass
*/

// the setup function runs once when you press reset or power the board
#include <RTCDue.h>
#include <DHT_U.h>
#include <DHT.h>
#include <UTouchCD.h>
#include <UTouch.h>
#include <UTFT.h>
#include <memorysaver.h>
#include "UserInterface.h"
#include "RulesEngine.h"
#include "Relais.h"
#include "CurrentTime.h"
#include "Definitions.h"
#include "Sensor.h"


//Global Variables / Handles
//Define Global Objects
//DHT
DHT dht(DHTPIN, DHTTYPE);
//Current Time Container
CurrentTime currenttime(RC);

//Relaisboard
RelaisBoard relaisboard;

//Sensors
Sensor *sensors[SENSNUMBER]; 

//Trigger
ActionHandler *actionhandler;

//LCD, Touchscreen
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);

//Control Pins Touchscreen
UTouch  myTouch( 46, 47, 48, 49, 50);

int touch_x, touch_y;

extern uint8_t BigFont[];
extern uint8_t SmallFont[];

int color = 0;
word colorlist[] = { VGA_WHITE, VGA_BLACK, VGA_RED, VGA_BLUE, VGA_GREEN, VGA_FUCHSIA, VGA_YELLOW, VGA_AQUA, VGA_GRAY, VGA_SILVER };
int  bsize = 4;
bool unit = true;

String debug = "Debug";

//User Interface
TouchInterface myUI;

//External


void setup() {
	Serial.begin(9600);

	currenttime.begin(); // initialize RTC
	currenttime.updateRTCdefault();
	

	//Initialize Relais
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	//Turn OFF Relais HIGH = OFF
	digitalWrite(RELAY1, HIGH);
	digitalWrite(RELAY2, HIGH);
	digitalWrite(RELAY3, HIGH);
	digitalWrite(RELAY4, HIGH);

	
	sensors[0] = new	DHTTemperature("Temperature", 'C', true);
	sensors[1] = new 	DHTHumidity("Humidity", '%', true);
	sensors[2] = new 	AnalogSensor("Moisture 1", MOS1, '%', true);
	sensors[3] = new 	AnalogSensor("Moisture 2", MOS2, '%', true);
	sensors[4] = new 	AnalogSensor("Moisture 3", MOS3, '%', true);
	sensors[5] = new 	AnalogSensor("Moisture 4", MOS4, '%', true);
	sensors[6] = new 	DigitalSensor("Top 1", TOP1, 'B', true);
	sensors[7] = new 	DigitalSensor("Top 2", TOP2, 'B', true);
	sensors[8] = new 	DigitalSensor("Top 3", TOP3, 'B', true);
	sensors[9] = new 	DigitalSensor("Top 4", TOP4, 'B', true);


	actionhandler = new ActionHandler();


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
