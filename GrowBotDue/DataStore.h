// DataStore.h

#ifndef _DATASTORE_h
#define _DATASTORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SD.h>
#include <ArduinoJson.h>

#include "Definitions.h"
#include "CurrentTime.h"
#include "Sensor.h"
#include "Relais.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "UserInterfaceElement.h"

//Time
extern CurrentTime currenttime;
//Sensors
extern Sensor *sensors[SENSNUMBER];
//Relais
extern RelaisBoard *relaisboard;

extern Trigger *trigger[TRIGCAT][TRIGNUMBER];

extern RuleSet *rulesets[RULES];

extern long sensor_cycles;
#define ARDUINOJSON_ENABLE_PROGMEM 1

class DataStore {
public:
	static void serialize();
	static void deserialize();
};


#endif

