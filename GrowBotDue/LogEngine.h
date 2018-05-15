// LogEngine.h

#ifndef _LOGENGINE_h
#define _LOGENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "FileSystem.h"
#include "RealTimeClock.h"

extern long sensor_cycles;
extern FileSystem filesystem;
extern RealTimeClock internalRTC;

class LogEntry {
private:
	int id;
	long timestamp;
	uint8_t type;
	String origin;

	String message;

	uint8_t para_ptr;
	uint8_t para_size;
	String *keys;
	String *values;

public:
	LogEntry(int id, uint8_t type, String origin, String message, uint8_t para);
	~LogEntry();

	void addParameter(String key, String value);
	String serializeJSON();
};


class LogEngine {
private:
	uint8_t entry_ptr;
	LogEntry *log_buffer[LOGBUFFER_SIZE];

public:
	LogEngine();

	void begin();
	int counter;
	void addLogEntry(uint8_t type, String origin, String message, String keys[], String values[], uint8_t size);
	void serializeJSON(char* json, size_t maxSize, int end, int count);
	void reset();
private:
	void saveToFile();
};

#endif

