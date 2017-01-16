// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DHT_U.h>
#include <DHT.h>

extern DHT dht;

class Sensor {
public:
	String source;

	char unit;

	bool active;
	int pin;
	String getTitle();

	virtual float readValue();
	virtual String getValue();
};

class AnalogSensor : public Sensor {
public:
	AnalogSensor(String source, int pin, char unit, bool active);
	float readValue();
	String getValue();
};

class DigitalSensor : public Sensor {
public:
	DigitalSensor(String source, int pin, char unit, bool active);
	float readValue();
	String getValue();
};

class DHTTemperature : public Sensor {
public:
	DHTTemperature(String source, char unit, bool active);
	float readValue();
	String getValue();
};

class DHTHumidity : public Sensor {
public:
	DHTHumidity(String source, char unit, bool active);
	float readValue();
	String getValue();
};

#endif

