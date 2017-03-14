// 
// 
// 

#include "Sensor.h"


AnalogSensor::AnalogSensor(String source, uint8_t pin, char unit, bool active) {
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

String Sensor::toNAN(short i)
{
	if(i == -32768)	return String("##");
	else return String(i);
}

short Sensor::fromNAN(String str)
{
	if (str == "##") return -32768;
	else return str.toInt();
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

void Sensor::update()
{
	int dividend = 0, divisor = 0, low_boundery = 0, high_boundery = 0, multiplicator = 0;

	//Minutes -> read sensor every 60/NUMMINUTES Seconds -> Example: 5 Seconds
	if (minute_ptr < NUMMINUTE - 1) 	minute_ptr++;
	else minute_ptr = 0;

	minute_values[minute_ptr] = readValue();
	
	//Hour -> calculate average every MINUTE / (NUMHOUR/60)  -> Example: 1 Minute
	if (sensor_cycles >= (NUMMINUTE * 60 / NUMHOUR) && sensor_cycles % (NUMMINUTE * 60 / NUMHOUR) == 0) {
		if (hour_ptr < NUMHOUR - 1) hour_ptr++;
		else hour_ptr = 0;

		dividend = 0;
		divisor = 0;
		high_boundery = hour_ptr + 1;
		low_boundery = high_boundery - (NUMMINUTE * 60 / NUMHOUR);

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (minute_values[i] != -32768) {
				dividend += minute_values[i];
				divisor++;
			}
		}
		hour_values[hour_ptr] = (int)round(dividend / divisor);
	}

	//Day -> calculate average every HOUR / (NUMDAY/24)  -> Example: 1/4 Hour
	if (sensor_cycles >= (NUMMINUTE * 60 * 24 / NUMDAY) && sensor_cycles % (NUMMINUTE * 60 * 24 / NUMDAY) == 0) {
		if (day_ptr < NUMDAY - 1) 	day_ptr++;
		else {
			day_ptr = 0;
		}

		dividend = 0;
		divisor = 0;
		high_boundery = hour_ptr + 1;
		low_boundery = high_boundery - (NUMHOUR * 24 / NUMDAY);

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (hour_values[i] != -32768) {
				dividend += hour_values[i];
				divisor++;
			}
		}
		day_values[day_ptr] = (int)round(dividend / divisor);
	}
	
	//Month-> calculate average every DAY / (NUMMONTH/28)  -> Example: 1/2 Day
	if (sensor_cycles >= (NUMMINUTE * 60 * 24 * 28 / NUMMONTH) && sensor_cycles % (NUMMINUTE * 60 * 24 * 28 / NUMMONTH) == 0) {
		if (month_ptr < NUMMONTH - 1) 	month_ptr++;
		else month_ptr = 0;

		dividend = 0;
		divisor = 0;
		high_boundery = day_ptr+1;
		low_boundery = high_boundery - (NUMDAY * 28 / NUMMONTH);

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (day_values[i] != -32768) {
				dividend += day_values[i];
				divisor++;
			}
		}
		month_values[month_ptr] = (int)round(dividend / divisor);
	}
	//Year-> calculate average once a week -> Example: 7 Days
	if (sensor_cycles >= (NUMMINUTE * 60 * 24 * 7 * 52 / NUMYEAR) && sensor_cycles % (NUMMINUTE * 60 * 24 * 7 * 52 / NUMYEAR) == 0) {
		if (year_ptr < NUMYEAR - 1) 	year_ptr++;
		else year_ptr = 0;
		
		dividend = 0;
		divisor = 0;
		high_boundery = day_ptr + 1;
		low_boundery = high_boundery - (NUMMONTH / 4) * (52 / NUMYEAR);

		for (uint8_t i = 0; i < NUMMONTH; i++) {
			if (month_values[i] != -32768) {
				dividend += month_values[i];
				divisor++;
			}
		}
		year_values[year_ptr] = (int)round(dividend / divisor);
	}
}

short Sensor::getLastValue()
{
	return minute_values[minute_ptr];
}

short Sensor::getTenSecAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = 60 / NUMMINUTE;
	element_count = 10 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;
	
	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {
			
			//Debug
			Serial.print("TenSec:" + i);
			Serial.println(minute_values[i]);
			
			dividend += (minute_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwentySecAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = 60 / NUMMINUTE;
	element_count = 20 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {

			//Debug
			Serial.print("TwentySec:" + i);
			Serial.println(minute_values[i]);

			dividend += (minute_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getThirtySecAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = 60 / NUMMINUTE;
	element_count = 30 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {

			//Debug
			Serial.print("ThirtySec:" + i);
			Serial.println(minute_values[i]);

			dividend += (minute_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getOneMinAvg()
{
	short dividend = 0;
	short divisor = 0;
	float result;

	for (int i = 0; i <  NUMMINUTE; i++) {
		if (minute_values[i] != -32768) {

			//Debug
			Serial.print("OneMinute:" + i);
			Serial.println(minute_values[i]);

			dividend += (minute_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwoMinAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMHOUR / 60;
	element_count = 2 * interval;
	low_boundry = hour_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = hour_ptr; i > low_boundry; i--) {
		if (hour_values[i] != -32768) {

			//Debug
			Serial.print("TwoMin:" + i);
			Serial.println(hour_values[i]);

			dividend += (hour_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getFiveMinAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMHOUR / 60;
	element_count = 5 * interval;
	low_boundry = hour_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = hour_ptr; i > low_boundry; i--) {
		if (hour_values[i] != -32768) {

			//Debug
			Serial.print("FiveMin:" + i);
			Serial.println(hour_values[i]);

			dividend += (hour_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getQuarterAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMHOUR / 60;
	element_count = 15 * interval;
	low_boundry = hour_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = hour_ptr; i > low_boundry; i--) {
		if (hour_values[i] != -32768) {
			dividend += (hour_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getHalfAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMHOUR / 60;
	element_count = 30 * interval;
	low_boundry = hour_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = hour_ptr; i > low_boundry; i--) {
		if (hour_values[i] != -32768) {
			dividend += (hour_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getHourAvg()
{
	short dividend = 0;
	short divisor = 0;
	float result;

	for (int i = 0; i < NUMHOUR; i++) {
		if (hour_values[i] != -32768) {
			dividend += (hour_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwoHourAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMDAY / 24;
	element_count = 2 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = day_ptr; i > low_boundry; i--) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getThreeHourAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMDAY / 24;
	element_count = 3 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = day_ptr; i > low_boundry; i--) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getFourHourAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMDAY / 24;
	element_count = 4 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = day_ptr; i > low_boundry; i--) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getSixHourAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMDAY / 24;
	element_count = 6 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = day_ptr; i > low_boundry; i--) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwelveHourAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMDAY / 24;
	element_count = 12 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = day_ptr; i > low_boundry; i--) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getDayAvg()
{
	short dividend = 0;
	short divisor = 0;
	float result;

	for (int i = 0; i < NUMDAY; i++) {
		if (day_values[i] != -32768) {
			dividend += (day_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwoDayAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMMONTH / 28;
	element_count = 2 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = month_ptr; i > low_boundry; i--) {
		if (month_values[i] != -32768) {
			dividend += (month_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getWeekAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMMONTH / 28;
	element_count = 7 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = month_ptr; i > low_boundry; i--) {
		if (month_values[i] != -32768) {
			dividend += (month_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

short Sensor::getTwoWeekAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = NUMMONTH / 28;
	element_count = 14 * interval;
	low_boundry = day_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = month_ptr; i > low_boundry; i--) {
		if (month_values[i] != -32768) {
			dividend += (month_values[i]);
			divisor++;
		}
	}
	result = dividend / divisor;


	return round(result);
}

void Sensor::reset()
{
	minute_ptr = -1;
	hour_ptr = -1;
	day_ptr = -1;
	month_ptr = -1;
	year_ptr = -1;
	
	for (uint8_t i = 0; i < NUMMINUTE; i++) this->minute_values[i] = -32768;
	for (uint8_t i = 0; i < NUMHOUR; i++) this->hour_values[i] = -32768;
	for (uint8_t i = 0; i < NUMDAY; i++) this->day_values[i] = -32768;
	for (uint8_t i = 0; i < NUMMONTH; i++) this->month_values[i] = -32768;
	for (uint8_t i = 0; i < NUMYEAR; i++) this->year_values[i] = -32768;
}

void Sensor::serializeJSON(uint8_t id, char* json, size_t maxSize)
{
	StaticJsonBuffer<5000> jsonBuffer;

	JsonObject& sensor = jsonBuffer.createObject();

	sensor["type"] = "SENSOR";
	sensor["id"] = id;
	sensor["minute_ptr"] = this->minute_ptr;
	sensor["hour_ptr"] = this->hour_ptr;
	sensor["day_ptr"] = this->day_ptr;
	sensor["month_ptr"] = this->month_ptr;
	sensor["year_ptr"] = this->year_ptr;

	JsonArray& minutes = sensor.createNestedArray("minute_values");
	for (uint8_t j = 0; j < NUMMINUTE; j++) minutes.add(toNAN(this->minute_values[j]));
	JsonArray& hours = sensor.createNestedArray("hour_values");
	for (uint8_t j = 0; j < NUMHOUR; j++) hours.add(toNAN(this->hour_values[j]));
	JsonArray& days = sensor.createNestedArray("day_values");
	for (uint8_t j = 0; j < NUMDAY; j++) days.add(toNAN(this->day_values[j]));
	JsonArray& month = sensor.createNestedArray("month_values");
	for (uint8_t j = 0; j < NUMMONTH; j++) month.add(toNAN(this->month_values[j]));
	JsonArray& year = sensor.createNestedArray("year_values");
	for (uint8_t j = 0; j < NUMYEAR; j++) year.add(toNAN(this->year_values[j]));
	
	sensor.printTo(json, maxSize);
}

bool Sensor::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		this->minute_ptr = data["minute_ptr"];
		this->hour_ptr = data["hour_ptr"];
		this->day_ptr = data["day_ptr"];
		this->month_ptr = data["month_ptr"];
		this->year_ptr = data["year_ptr"];

		for (uint8_t j = 0; j < NUMMINUTE; j++) this->minute_values[j] = fromNAN(data["minute_values"][j]);
		for (uint8_t j = 0; j < NUMHOUR; j++) this->hour_values[j] = fromNAN(data["hour_values"][j]);
		for (uint8_t j = 0; j < NUMDAY; j++) this->day_values[j] = fromNAN(data["day_values"][j]);
		for (uint8_t j = 0; j < NUMMONTH; j++) this->month_values[j] = fromNAN(data["month_values"][j]);
		for (uint8_t j = 0; j < NUMYEAR; j++) this->year_values[j] = fromNAN(data["year_values"][j]);
	}

	return data.success();
}


Sensor::Sensor()
{
	this->reset();
}
