// Setting.h

#ifndef _SETTING_h
#define _SETTING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>
#include "RealTimeClock.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "ActionChain.h"
#include "LogEngine.h"

extern String wifi_ssid;
extern String wifi_pw;
extern String api_secret;

extern long sensor_cycles;
extern RealTimeClock internalRTC;
extern Sensor *sensors[SENS_NUM];
extern Trigger *trigger[TRIGGER_TYPES][TRIGGER_SETS];
extern RuleSet *rulesets[RULESETS_NUM];
extern ActionChain *actionchains[ACTIONCHAINS_NUM];
extern LogEngine logengine;



class Setting {
public:

	static void reset();

	static void serializeJSON(char* json, size_t maxSize);
	static bool deserializeJSON(JsonObject& data);
};


#endif

