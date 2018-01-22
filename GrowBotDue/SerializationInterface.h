// SerializationInterface.h

#ifndef _SERIALIZATIONINTERFACE_h
#define _SERIALIZATIONINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>

class SerializationInterface {
public:
	SerializationInterface();
	virtual void serializeJSON(uint8_t id, char* json, size_t maxSize, Scope scope);
	virtual bool deserializeJSON(JsonObject& data);

};

#endif

