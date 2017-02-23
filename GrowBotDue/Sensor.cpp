// 
// 
// 

#include "Sensor.h"


AnalogSensor::AnalogSensor(String source, int pin, char unit, bool active) {
	this->source = source;
	this->unit = unit;
	this->pin = pin;
	this->active = active;

	pinMode(pin, INPUT_PULLUP);
}

float AnalogSensor::readValue() {
	return analogRead(pin);
}

String AnalogSensor::getValue()
{
	return String(readValue(), 2) + String(unit);
}


DigitalSensor::DigitalSensor(String source, int pin, char unit, bool active) {
	this->source = source;
	this->unit = unit;
	this->pin = pin;
	this->active = active;

	pinMode(pin, INPUT);
}

float DigitalSensor::readValue() {
	
	return digitalRead(pin);
}

String DigitalSensor::getValue()
{
	return String(readValue(), 0) + String(unit);
}


DHTTemperature::DHTTemperature(String source, char unit, bool active)
{
	this->source = source;
	this->unit = unit;
	this->active = active;

	dht.begin();
}

float DHTTemperature::readValue()
{
	return dht.readTemperature();
}

String DHTTemperature::getValue()
{
	return String(dht.readTemperature(), 2) + String(unit);
}

DHTHumidity::DHTHumidity(String source, char unit, bool active)
{
	this->source = source;
	this->unit = unit;
	this->active = active;

	dht.begin();
}

float DHTHumidity::readValue()
{
	return dht.readHumidity();
}

String DHTHumidity::getValue()
{
	return String(readValue(), 2) + String(unit);
}

String Sensor::getTitle()
{
	return String(this->source);
}


float Sensor::readValue()
{
	return 0.0f;
}

String Sensor::getValue()
{
	return String(readValue()) + String(unit);
}
