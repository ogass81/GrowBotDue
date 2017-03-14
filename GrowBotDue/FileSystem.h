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
#include "CurrentTime.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Ruleset.h"


extern long sensor_cycles;
extern CurrentTime currenttime;
extern Sensor *sensors[SENSNUMBER];
extern Trigger *trigger[TRIGCAT][TRIGNUMBER];
extern RuleSet *rulesets[RULES];


class FileSystem {
	SdFat sd;
	// Log file.

public:
	FileSystem();

	void init();
	void saveActiveConfig();
	void saveBackupConfig();
	void saveDefaultConfig();

	void readActiveConfig();
	void readBackupConfig();
	void readDefaultConfig();

	bool readfromCard(const char* filename);
	bool savetoCard(const char* filename);
	bool copy(const char* source, const char* destination);

	void reset();

};



#endif

