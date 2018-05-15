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
#include "Led.h"


extern long sensor_cycles;
extern Led *led[3];


class FileSystem {
	SdFat sd;
	// Log file.

public:
	FileSystem();

	void init();

	bool copyFile(const char* source, const char* destination);

	bool appendLinesToFile(const char * filename, String data[], uint8_t size);
	void readLinesFromFile(const char* filename, int counter, int start, int end, char * json, int size);
	int fileLength(const char* filename);
	bool resetFile(const char* filename);
};

#endif

