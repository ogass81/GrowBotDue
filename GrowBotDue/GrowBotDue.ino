/*
 Name:		GrowBotDue.ino
 Created:	13.01.2017 21:11:47
 Author:	ogass
*/

//Contants

#include "Definitions.h"

//Hardware Libaries
#include <memorysaver.h>
#include <UTouchCD.h>
#include <UTouch.h>
#include <UTFT.h>
#include <RTCDue.h>
#include <DHT_U.h>
#include <DHT.h>

//Modules
#include "CurrentTime.h"
#include "FileSystem.h"
#include "Network.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Action.h"
#include "ActionChain.h"
#include "Ruleset.h"
#include "TaskManager.h"
#include "UserInterface.h"
/*
#include "DigitalSwitch.h"
*/
#include "Relais.h"



#include "RCSocketController.h"
#include "Setting.h"


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
long cpu_current = 0;
long sensor_last = 0;
long task_last = 0;
bool haltstate = false;
long haltstate_start;

//Wifi and Auth
String wifi_ssid;
String wifi_pw;
String api_secret;


//Hardware Handles
//LCD, Touchscreen
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);
//Control Pins Touchscreen
UTouch  myTouch(44, 45, 46, 47, 48);

//Relaisboard
RelaisBoard *relaisboard;

/*
//Digital Switches
DigitalSwitch *digitalswitches;
*/

//DHT Hardware
DHT dht(DHT_DATA_PIN, DHT_TYPE);
//RealTimeClock
CurrentTime currenttime(RC);

//433Mhz
RCSocketController *rcsocketcontroller;

//Wifi
WebServer *webserver;

//Modules
//Sensors: Abstraction of all Sensors
Sensor *sensors[SENS_NUM]; 

//Actions: Abstraction of all Actors 
Action *actions[ACTIONS_NUM];
ActionChain *actionchains[ACTIONCHAINS_NUM];

//Task Manager
TaskManager *taskmanager;

//Trigger: Constraints for particular sensors
Trigger *trigger[TRIGGER_TYPES][TRIGGER_SETS];

//Rulesets: Trigger Action Bundles
RuleSet *rulesets[RULESETS_NUM];

//FileSystem
FileSystem filesystem;


//User Interface: TFT User Interface
UserInterface myUI;



void setup() {
	// initialize serial for debugging
	Serial.begin(115200);

	// initialize RTC
	currenttime.begin(); 
	currenttime.syncTimeObject();
	//Initialize Tact Generator
	sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENS_FRQ_SEC;

	/*
	//Initialize Relais Board
	relaisboard = new RelaisBoard();
	//Initialize Digital Switches
	digitalswitches = new DigitalSwitch();
	*/
	
	//433Mhz
	rcsocketcontroller = new RCSocketController(TX_DATA_PIN, RX_DATA_PIN);
			
	//Initialize Sensors
	sensors[0] = new	DHTTemperature("Temp.", 'C', true);
	sensors[1] = new 	DHTHumidity("Humid.", '%', true);
	sensors[2] = new 	AnalogSensor("Moist.", IN_MOS_1, '%', true);
	sensors[3] = new 	AnalogSensor("Moist.", IN_MOS_2, '%', true);
	/*
	sensors[4] = new 	AnalogSensor("Mosit.", IN_MOS_3, '%', true);
	sensors[5] = new 	AnalogSensor("Moist.", IN_MOS_4, '%', true);
	sensors[6] = new 	DigitalSensor("TBD", OUT_TOP_1, 'B', true);
	sensors[7] = new 	DigitalSensor("TBD", OUT_TOP_2, 'B', true);
	sensors[8] = new 	DigitalSensor("TBD", OUT_TOP_3, 'B', true);
	sensors[9] = new 	DigitalSensor("TBD", OUT_TOP_4, 'B', true);
	*/

	//Intialize Actions
	actions[0] = new ParameterizedSimpleAction<RCSocketController>("RC1 On", rcsocketcontroller, &RCSocketController::sendCode, 0, true);
	actions[1] = new ParameterizedSimpleAction<RCSocketController>("RC1 Off", rcsocketcontroller, &RCSocketController::sendCode, 1, true);
	actions[2] = new ParameterizedSimpleAction<RCSocketController>("RC2 On", rcsocketcontroller, &RCSocketController::sendCode, 2, true);
	actions[3] = new ParameterizedSimpleAction<RCSocketController>("RC2 Off", rcsocketcontroller, &RCSocketController::sendCode, 3, true);
	actions[4] = new ParameterizedSimpleAction<RCSocketController>("RC3 On", rcsocketcontroller, &RCSocketController::sendCode, 4, true);
	actions[5] = new ParameterizedSimpleAction<RCSocketController>("RC3 Off", rcsocketcontroller, &RCSocketController::sendCode, 5, true);
	actions[6] = new ParameterizedSimpleAction<RCSocketController>("RC4 On", rcsocketcontroller, &RCSocketController::sendCode, 6, true);
	actions[7] = new ParameterizedSimpleAction<RCSocketController>("RC4 Off", rcsocketcontroller, &RCSocketController::sendCode, 7, true);
	
	/*
	actions[8] = new SimpleAction<RelaisBoard>("R1 On", relaisboard, &RelaisBoard::R1On, true);
	actions[9] = new SimpleAction<RelaisBoard>("R1 Off", relaisboard, &RelaisBoard::R1Off, true);
	actions[10] = new SimpleAction<RelaisBoard>("R2 On", relaisboard, &RelaisBoard::R2On, true);
	actions[11] = new SimpleAction<RelaisBoard>("R2 Off", relaisboard, &RelaisBoard::R2Off, true);
	actions[12] = new SimpleAction<RelaisBoard>("R3 On", relaisboard, &RelaisBoard::R3On, true);
	actions[13] = new SimpleAction<RelaisBoard>("R3 Off", relaisboard, &RelaisBoard::R3Off, true);
	actions[14] = new SimpleAction<RelaisBoard>("R4 On", relaisboard, &RelaisBoard::R4On, true);
	actions[15] = new SimpleAction<RelaisBoard>("R4 Off", relaisboard, &RelaisBoard::R4Off, true);
	*/


	//Define Opposite Action / Antagonist
	//R1
	actions[0]->setAntagonist(actions[1]);
	actions[1]->setAntagonist(actions[0]);
	//R2
	actions[2]->setAntagonist(actions[3]);
	actions[3]->setAntagonist(actions[2]);
	//R3
	actions[4]->setAntagonist(actions[5]);
	actions[5]->setAntagonist(actions[4]);
	//R4
	actions[6]->setAntagonist(actions[7]);
	actions[7]->setAntagonist(actions[6]);
	//RC1
	actions[8]->setAntagonist(actions[9]);
	actions[9]->setAntagonist(actions[8]);
	//RC2
	actions[10]->setAntagonist(actions[11]);
	actions[11]->setAntagonist(actions[10]);
	//RC3
	actions[12]->setAntagonist(actions[13]);
	actions[13]->setAntagonist(actions[12]);
	//RC4
	actions[14]->setAntagonist(actions[15]);
	actions[15]->setAntagonist(actions[14]);
	//Learning Mode
	actions[16]->setAntagonist(actions[17]);
	actions[17]->setAntagonist(actions[16]);

	//Initialize ActionChains
	for (uint8_t i = 0; i < ACTIONCHAINS_NUM; i++) {
		actionchains[i] = new ActionChain(i);
	}

	//Start Taskmanager
	taskmanager = new TaskManager();

	//Initialize Trigger
	for (int tcategory = 0; tcategory < TRIGGER_TYPES; tcategory++) {
		for (int tset = 0; tset < TRIGGER_SETS; tset++) {
			if (tcategory == 0) trigger[tcategory][tset] = new TimeTrigger(tset);
			else {
				trigger[tcategory][tset] = new SensorTrigger(tset, sensors[tcategory - 1]);
			}
		}
	}

	//Initialize Rulesets
	for (uint8_t k = 0; k < RULESETS_NUM; k++) {
		rulesets[k] = new RuleSet(k);
	}

	//Initialize FileSystem / SD Card
	filesystem.init();
	
	if (DEBUG_RESET == false) {
		if (filesystem.loadSettings("_CURRENTCONFIG.JSON") == false) {
			LOGMSG(F("[Setup]"), F("WARNING: Did not load primary config file"), F("Hardreset"), DEBUG_RESET, "");
			if (filesystem.loadSettings("BACKUPCONFIG.JSON") == false) {
				LOGMSG(F("[Setup]"), F("WARNING: Did not load backup config file"), F("Hardreset"), DEBUG_RESET, "");
				if (filesystem.loadSettings("DEFAULTCONFIG.JSON") == false) {
					LOGMSG(F("[Setup]"), F("WARNING: Did not load default config file"), F("Hardreset"), DEBUG_RESET, "");
					Setting::reset();
				}
			}
		}
	}
	else Setting::reset();


	//Wifi ESP2866
	pinMode(ESP_CONTROL_PIN, OUTPUT);
	digitalWrite(ESP_CONTROL_PIN, HIGH);
	Serial2.begin(115200);
	WiFi.init(&Serial2);

	//Convert SSID and PW to char[]
	char ssid[wifi_ssid.length()+1];
	wifi_ssid.toCharArray(ssid, wifi_ssid.length()+1);

	char pw[wifi_pw.length()+1];
	wifi_pw.toCharArray(pw, wifi_pw.length()+1);

	int status = WL_IDLE_STATUS;
	uint8_t failed = 0;
	while (status != WL_CONNECTED && failed < 5) {
		LOGMSG(F("[Setup]"), F("Info: Attempting to connect to WPA SSID: "), String(wifi_ssid), "", "");
		// Connect to WPA/WPA2 network
		status = WiFi.begin(ssid, pw);
		failed++;
	}

	//Start Webserver
	webserver = new WebServer();
	webserver->begin();
	

	// Initial LCD setup
	myGLCD.InitLCD();
	myGLCD.clrScr();

	myTouch.InitTouch();
	myTouch.setPrecision(PREC_MEDIUM);
	
	//Initialize User Interface (after everything has been initialized)
	myUI.drawBackground();
	myUI.drawMenue(1);
	myUI.drawFrame(1);

	/*
	//Test Data

	for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) sensors[0]->minute_values[i] = random(-25, 30);
	for (uint8_t i = 0; i < SENS_VALUES_HOUR; i++) sensors[0]->hour_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) sensors[0]->day_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) sensors[0]->month_values[i] = random(-25, 25);
	for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) sensors[0]->year_values[i] = random(-25, 25);
	*/
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Get Current CPU tact
	cpu_current = millis();

	//Constantly check for control input
	//Touch
		
	if (myTouch.dataAvailable())
	{
		myTouch.read();
		touch_x = myTouch.getX();
		touch_y = myTouch.getY();
		myUI.checkEvent(touch_x, touch_y);
	}

	//Webserver
	webserver->checkConnection();
	
	//Freeze Sensor, Logic and Taskmanager
	if (haltstate == true) {
		//RC Socket Learning
		if (rcsocketcontroller->learning == true) {
			if (rcsocketcontroller->available()) {
				rcsocketcontroller->learnPattern();
				rcsocketcontroller->resetAvailable();
				//myUI.draw();
			}
		}
		//more Hardware
	}
	//Regular Cycle
	else {
		//Sensor
		if (cpu_current - sensor_last >= (SENS_FRQ_SEC * 1000)) {
			sensor_last = cpu_current;

			//Cycles
			sensor_cycles++;
			LOGMSG(F("[Loop]"), F("INFO: Sensor Cycle"), String(sensor_cycles), "@", String(currenttime.createTime()));

			//Update Sensors
			for (uint8_t i = 0; i < SENS_NUM; i++) {
				sensors[i]->update();
			}

			//Check RuleSets
			for (uint8_t i = 0; i < RULESETS_NUM; i++) {
				rulesets[i]->execute();
			}

			//Save Settings to SD Card
			if ((sensor_cycles % (5 * SENS_VALUES_MIN)) == 0) {
				filesystem.saveActiveConfig();
			}

			//Backup
			if ((sensor_cycles % (15 * SENS_VALUES_MIN)) == 0) {
				filesystem.copyFile("_CURRENTCONFIG.JSON", "BACKUPCONFIG.JSON");
			}
			
			//Refresh UI
			if ((sensor_cycles % SENS_VALUES_MIN) == 0) {
				//Update Clock
				currenttime.syncTimeObject();
				//Draw UI
				myUI.draw();
			}
		}

		//Task Manager
		if (cpu_current - task_last >= (TASK_FRQ_SEC * 1000)) {
			task_last = cpu_current;
			taskmanager->execute();
		}
	}
}