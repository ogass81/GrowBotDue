/*
 Name:		GrowBotDue.ino
 Created:	13.01.2017 21:11:47
 Author:	ogass
*/

////Helper
#include "Definitions.h"

//Hardware Libaries
#include <memorysaver.h>
#include <SdFat.h>
#include <SPI.h>
#include <RTCDue.h>
#include <DHT_U.h>
#include <DHT.h>
#include "RealTimeClock.h"
#include "Led.h"

//Core Features
#include "Action.h"
#include "LogEngine.h"
#include "TaskManager.h"
#include "Network.h"
#include "Setting.h"

//Controller Objects
#include "Sensor.h"
#include "Trigger.h"
#include "ActionChain.h"
#include "Ruleset.h"
#include "RCSocketController.h"


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

//Status LED
Led *led[3];


//DHT Hardware
DHT dht(DHT_DATA_PIN, DHT_TYPE);
//RealTimeClock
RealTimeClock internalRTC(RC);

//433Mhz
RCSocketController *rcsocketcontroller;

//Wifi
WebServer *webserver;
WebTimeClient *ntpclient;

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
SdFat sd;

LogEngine logengine;


void setup() {
	// initialize serial for debugging
	Serial.begin(115200);

	//Initialize FileSystem / SD Card
	if (!sd.begin(SD_CONTROL_PIN, SPI_EIGHTH_SPEED)) {
		sd.initErrorHalt();
	}

	// initialize RTC
	internalRTC.begin();
	internalRTC.setDefaultTime();

	//Status Led
	led[0] = new Led(LED1, false);
	led[1] = new Led(LED2, false);
	led[2] = new Led(LED3, false);

	//LogEngine
	logengine.begin();

	String keys[] = { "" };
	String values[] = { "" };
	logengine.addLogEntry(0, "Main", "Starting Bot", keys, values, 0);

	//Start Temp/Humidity Sensor
	dht.begin();

	//433Mhz
	rcsocketcontroller = new RCSocketController(TX_DATA_PIN, RX_DATA_PIN);
			
	//Initialize Sensors
	sensors[0] = new	DHTTemperature(&dht, true, F("Temperature"), F("C"), -127, -50, 100);
	sensors[1] = new 	DHTHumidity(&dht, true, F("Humidity"), F("%"), -127, 0, 100);
	sensors[2] = new 	AnalogMoistureSensor<short>(IN_MOS_1, OUT_MOS_1, true, F("Soil 1"), F("%"), -1, 0, 1000, 150, 600);
	sensors[3] = new 	AnalogMoistureSensor<short>(IN_MOS_2, OUT_MOS_2, true, F("Soil 2"), F("%"), -1, 0, 1000, 150, 600);

	//Intialize Actions
	actions[0] = new ParameterizedSimpleAction<RCSocketController>("RC1 On", rcsocketcontroller, &RCSocketController::sendCode, 0, true);
	actions[1] = new ParameterizedSimpleAction<RCSocketController>("RC1 Off", rcsocketcontroller, &RCSocketController::sendCode, 1, true);
	actions[2] = new ParameterizedSimpleAction<RCSocketController>("RC2 On", rcsocketcontroller, &RCSocketController::sendCode, 2, true);
	actions[3] = new ParameterizedSimpleAction<RCSocketController>("RC2 Off", rcsocketcontroller, &RCSocketController::sendCode, 3, true);
	actions[4] = new ParameterizedSimpleAction<RCSocketController>("RC3 On", rcsocketcontroller, &RCSocketController::sendCode, 4, true);
	actions[5] = new ParameterizedSimpleAction<RCSocketController>("RC3 Off", rcsocketcontroller, &RCSocketController::sendCode, 5, true);
	actions[6] = new ParameterizedSimpleAction<RCSocketController>("RC4 On", rcsocketcontroller, &RCSocketController::sendCode, 6, true);
	actions[7] = new ParameterizedSimpleAction<RCSocketController>("RC4 Off", rcsocketcontroller, &RCSocketController::sendCode, 7, true);
	
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
	
	if (DEBUG_RESET == false) {
		if (Setting::loadSettings("_CURRENTCONFIG.JSON") == false) {
			LOGMSG(F("[Setup]"), F("WARNING: Did not load primary config file"), F("Hardreset"), DEBUG_RESET, "");
			String keys[] = { "" };
			String values[] = { "" };
			logengine.addLogEntry(0, "Main", "WARNING: Did not load primary config file", keys, values, 0);

			if (Setting::loadSettings("BACKUPCONFIG.JSON") == false) {
				LOGMSG(F("[Setup]"), F("WARNING: Did not load backup config file"), F("Hardreset"), DEBUG_RESET, "");
				String keys[] = { "" };
				String values[] = { "" };
				logengine.addLogEntry(0, "Main", "WARNING: Did not load backup config file", keys, values, 0);

				if (Setting::loadSettings("DEFAULTCONFIG.JSON") == false) {
					LOGMSG(F("[Setup]"), F("WARNING: Did not load default config file"), F("Hardreset"), DEBUG_RESET, "");
					String keys[] = { "" };
					String values[] = { "" };
					logengine.addLogEntry(0, "Main", "WARNING: Did not load default config file. Setting hard coded values", keys, values, 0);

					Setting::reset();
				}
			}
		}
	}
	else {
		LOGMSG(F("[Setup]"), F("WARNING: Hard Reset Flag set. Setting hard coded values"), F("Hardreset"), DEBUG_RESET, "");
		String keys[] = { "" };
		String values[] = { "" };
		logengine.addLogEntry(0, "Main", "WARNING: Hard Reset Flag set. Setting hard coded values", keys, values, 0);

		Setting::reset();
	}
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

	//Sync with Internet
	ntpclient = new WebTimeClient();
	long timestamp = ntpclient->getWebTime();

	if (timestamp > 0) {
		String keys[] = { "" };
		String values[] = { "" };
		logengine.addLogEntry(0, "Main", "Received Internet Time", keys, values, 0);

		internalRTC.updateTime(timestamp, true);
	}


	//Start Webserver
	webserver = new WebServer();
	webserver->begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Get Current CPU tact
	cpu_current = millis();
	
	//Webserver
	webserver->checkConnection();
	
	//Freeze Sensor, Logic and Taskmanager
	if (haltstate == true) {
		//Led
		led[1]->turnOn();
		//RC Socket Learning
		if (rcsocketcontroller->learning == true) {
			if (rcsocketcontroller->available()) {
				rcsocketcontroller->learnPattern();
				rcsocketcontroller->resetAvailable();
			}
		}
		//more Hardware
	}
	//Regular Cycle
	else {
		led[1]->turnOff();
		//Sensor
		if (cpu_current - sensor_last >= (SENS_FRQ_SEC * 1000)) {
			led[0]->switchState();

			sensor_last = cpu_current;

			//Cycles
			sensor_cycles++;

			LOGMSG(F("[Loop]"), F("INFO: Sensor Cycle"), String(sensor_cycles), "@", String(RealTimeClock::printTime(SENS_FRQ_SEC*sensor_cycles)));

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
				
				LOGMSG(F("[Loop]"), F("SaveActive"), "", "", "");
				String keys[] = { "" };
				String values[] = { "" };
				logengine.addLogEntry(0, "Main", "Saved Active Configuration", keys, values, 0);

				Setting::saveSettings("_CURRENTCONFIG.JSON");
			}

			//Backup
			if ((sensor_cycles % (15 * SENS_VALUES_MIN)) == 0) {
				LOGMSG(F("[Loop]"), F("SaveActive"), "", "", "");
				String keys[] = { "" };
				String values[] = { "" };
				logengine.addLogEntry(0, "Main", "Backup Configuration", keys, values, 0);

				Setting::copyFile("_CURRENTCONFIG.JSON", "BACKUPCONFIG.JSON");
			}		
		}

		//Task Manager
		if (cpu_current - task_last >= (TASK_FRQ_SEC * 1000)) {
			task_last = cpu_current;
			taskmanager->execute();
		}
	}
}