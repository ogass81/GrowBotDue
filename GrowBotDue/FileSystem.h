// FileSystem.h

#ifndef _FILESYSTEM_h
#define _FILESYSTEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "SdFat.h"
#include <SPI.h>
#include <ArduinoJson.h>
#include "RealTimeClock.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "ActionChain.h"
#include "RCSocketController.h"
#include "Setting.h"
#include "Led.h"

extern String wifi_ssid;
extern String wifi_pw;
extern String api_secret;

extern long sensor_cycles;
extern Led *led[3];
extern RealTimeClock internalRTC;
extern Sensor *sensors[SENS_NUM];
extern Trigger *trigger[TRIGGER_TYPES][TRIGGER_SETS];
extern RuleSet *rulesets[RULESETS_NUM];
extern ActionChain *actionchains[ACTIONCHAINS_NUM];
extern RCSocketController *rcsocketcontroller;


class FileSystem {
	SdFat sd;
	// Log file.

public:
	FileSystem();

	void init();
	void saveActiveConfig();
	void saveBackupConfig();
	void saveDefaultConfig();

	void loadActiveConfig();
	void loadBackupConfig();
	void loadDefaultConfig();

	bool loadSettings(const char* filename);
	bool saveSettings(const char* filename);
	bool copyFile(const char* source, const char* destination);
};

#endif

