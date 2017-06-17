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

	//Minutes -> read sensor every 60/SENS_VALUES_MINS Seconds -> Example: 5 Seconds
	if (minute_ptr < SENS_VALUES_MIN - 1) 	minute_ptr++;
	else minute_ptr = 0;

	minute_values[minute_ptr] = readValue();
	
	//Hour -> calculate average every MINUTE / (SENS_VALUES_HOUR /60)  -> Example: 1 Minute
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR ) && sensor_cycles % (SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR ) == 0) {
		if (hour_ptr < SENS_VALUES_HOUR  - 1) hour_ptr++;
		else hour_ptr = 0;

		dividend = 0;
		divisor = 0;
		high_boundery = minute_ptr + 1;
		low_boundery = high_boundery - (SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR );

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (minute_values[i] != -32768) {
				dividend += minute_values[i];
				divisor++;
			}
		}
		hour_values[hour_ptr] = (int)round(dividend / divisor);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new HOUR Value for"), String(getTitle()), String(hour_ptr), String(hour_values[hour_ptr]));
	}

	//Day -> calculate average every HOUR / (SENS_VALUES_DAY/24)  -> Example: 1/4 Hour
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 / SENS_VALUES_DAY) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 / SENS_VALUES_DAY) == 0) {
		if (day_ptr < SENS_VALUES_DAY - 1) 	day_ptr++;
		else {
			day_ptr = 0;
		}

		dividend = 0;
		divisor = 0;
		high_boundery = hour_ptr + 1;
		low_boundery = high_boundery - (SENS_VALUES_HOUR  * 24 / SENS_VALUES_DAY);

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (hour_values[i] != -32768) {
				dividend += hour_values[i];
				divisor++;
			}
		}
		day_values[day_ptr] = (int)round(dividend / divisor);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new DAY Value for"), String(getTitle()), String(day_ptr), String(day_values[day_ptr]));
	}
	
	//Month-> calculate average every DAY / (SENS_VALUES_MONTH/28)  -> Example: 1/2 Day
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 * 28 / SENS_VALUES_MONTH) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 * 28 / SENS_VALUES_MONTH) == 0) {
		if (month_ptr < SENS_VALUES_MONTH - 1) 	month_ptr++;
		else month_ptr = 0;

		dividend = 0;
		divisor = 0;
		high_boundery = day_ptr+1;
		low_boundery = high_boundery - (SENS_VALUES_DAY * 28 / SENS_VALUES_MONTH);

		for (uint8_t i = low_boundery; i < high_boundery; i++) {
			if (day_values[i] != -32768) {
				dividend += day_values[i];
				divisor++;
			}
		}
		month_values[month_ptr] = (int)round(dividend / divisor);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new MONTH Value for"), String(getTitle()), String(month_ptr), String(month_values[month_ptr]));
	}
	//Year-> calculate average once a week -> Example: 7 Days
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 * 7 * 52 / SENS_VALUES_YEAR) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 * 7 * 52 / SENS_VALUES_YEAR) == 0) {
		if (year_ptr < SENS_VALUES_YEAR - 1)	year_ptr++;
		else year_ptr = 0;
		
		dividend = 0;
		divisor = 0;
		high_boundery = day_ptr + 1;
		low_boundery = high_boundery - (SENS_VALUES_MONTH / 4) * (52 / SENS_VALUES_YEAR);

		for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) {
			if (month_values[i] != -32768) {
				dividend += month_values[i];
				divisor++;
			}
		}
		year_values[year_ptr] = (int)round(dividend / divisor);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new YEAR Value for"), String(getTitle()), String(year_ptr), String(year_values[year_ptr]));
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

	interval = 60 / SENS_VALUES_MIN;
	element_count = 10 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;
	
	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {
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

	interval = 60 / SENS_VALUES_MIN;
	element_count = 20 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {
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

	interval = 60 / SENS_VALUES_MIN;
	element_count = 30 / interval;
	low_boundry = minute_ptr - element_count;

	if (low_boundry < -1) low_boundry = -1;

	for (int i = minute_ptr; i > low_boundry; i--) {
		if (minute_values[i] != -32768) {
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

	for (int i = 0; i <  SENS_VALUES_MIN; i++) {
		if (minute_values[i] != -32768) {
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

	interval = SENS_VALUES_HOUR  / 60;
	element_count = 2 * interval;
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

short Sensor::getFiveMinAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = SENS_VALUES_HOUR  / 60;
	element_count = 5 * interval;
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

short Sensor::getQuarterAvg()
{
	uint8_t interval, element_count, low_boundry;

	short dividend = 0;
	short divisor = 0;
	float result;

	interval = SENS_VALUES_HOUR  / 60;
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

	interval = SENS_VALUES_HOUR  / 60;
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

	for (int i = 0; i < SENS_VALUES_HOUR ; i++) {
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

	interval = SENS_VALUES_DAY / 24;
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

	interval = SENS_VALUES_DAY / 24;
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

	interval = SENS_VALUES_DAY / 24;
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

	interval = SENS_VALUES_DAY / 24;
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

	interval = SENS_VALUES_DAY / 24;
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

	for (int i = 0; i < SENS_VALUES_DAY; i++) {
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

	interval = SENS_VALUES_MONTH / 28;
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

	interval = SENS_VALUES_MONTH / 28;
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

	interval = SENS_VALUES_MONTH / 28;
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
	
	for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) minute_values[i] = -32768;
	for (uint8_t i = 0; i < SENS_VALUES_HOUR ; i++) hour_values[i] = -32768;
	for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) day_values[i] = -32768;
	for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) month_values[i] = -32768;
	for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) year_values[i] = -32768;
}

void Sensor::serializeJSON(uint8_t id, char* json, size_t maxSize, DateRange range)
{
	StaticJsonBuffer<5000> jsonBuffer;

	JsonObject& sensor = jsonBuffer.createObject();

	sensor["type"] = "SENSOR";
	sensor["id"] = id;
	sensor["min_ptr"] = minute_ptr;
	sensor["h_ptr"] = hour_ptr;
	sensor["d_ptr"] = day_ptr;
	sensor["m_ptr"] = month_ptr;
	sensor["y_ptr"] = year_ptr;

	if (range == AVG) {
		JsonObject& avg = sensor.createNestedObject("avg");
		avg["last"] = getLastValue();
		avg["tenSec"] = getTenSecAvg();
		avg["twentySec"] = getTwentySecAvg();
		avg["thirtySec"] = getThirtySecAvg();
		avg["oneMin"] = getOneMinAvg();
		avg["twoMin"] = getTwoMinAvg();
		avg["fiveMin"] = getFiveMinAvg();
		avg["quarterHour"] = getQuarterAvg();
		avg["halfHour"] = getHalfAvg();
		avg["lastHour"] = getHourAvg();
		avg["twoHours"] = getTwoHourAvg();
		avg["threeHours"] = getThreeHourAvg();
		avg["fourHours"] = getFourHourAvg();
		avg["sixHours"] = getSixHourAvg();
		avg["twelveHours"] = getTwelveHourAvg();
		avg["lastDay"] = getDayAvg();
		avg["twoDays"] = getTwoDayAvg();
		avg["lastWeek"] = getWeekAvg();
		avg["twoWeeks"] = getTwoWeekAvg();
	}
	if (range == MINUTE || range == ALL) {
		JsonArray& minutes = sensor.createNestedArray("min_vals");
		for (uint8_t j = 0; j < SENS_VALUES_MIN; j++) minutes.add(toNAN(minute_values[j]));
	}

	if (range == MINUTE || range == ALL) {
		JsonArray& hours = sensor.createNestedArray("h_vals");
		for (uint8_t j = 0; j < SENS_VALUES_HOUR ; j++) hours.add(toNAN(hour_values[j]));
	}
	if (range == MINUTE || range == ALL) {
		JsonArray& days = sensor.createNestedArray("d_vals");
		for (uint8_t j = 0; j < SENS_VALUES_DAY; j++) days.add(toNAN(day_values[j]));
	}
	if (range == MONTH || range == ALL) {
		JsonArray& month = sensor.createNestedArray("m_vals");
		for (uint8_t j = 0; j < SENS_VALUES_MONTH; j++) month.add(toNAN(month_values[j]));
	}
	if (range == MONTH || range == ALL) {
		JsonArray& year = sensor.createNestedArray("y_vals");
		for (uint8_t j = 0; j < SENS_VALUES_YEAR; j++) year.add(toNAN(year_values[j]));
	}
	sensor.printTo(json, maxSize);
	LOGDEBUG2(F("[Sensor]"), F("serializeJSON()"), F("OK: Serialized members for Sensor"), String(id), String(sensor.measureLength()), String(maxSize));
}

bool Sensor::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		if (data["min_ptr"] != "") minute_ptr = data["min_ptr"];
		if (data["h_ptr"] != "") hour_ptr = data["h_ptr"];
		if (data["d_ptr"] != "") day_ptr = data["d_ptr"];
		if (data["m_ptr"] != "") month_ptr = data["m_ptr"];
		if (data["y_ptr"] != "") year_ptr = data["y_ptr"];

		for (uint8_t j = 0; j < SENS_VALUES_MIN; j++) if (data["min_vals"][j] != "") minute_values[j] = fromNAN(data["min_vals"][j]);
		for (uint8_t j = 0; j < SENS_VALUES_HOUR ; j++) if (data["h_vals"][j] != "") hour_values[j] = fromNAN(data["h_vals"][j]);
		for (uint8_t j = 0; j < SENS_VALUES_DAY; j++) if (data["d_vals"][j] != "") day_values[j] = fromNAN(data["d_vals"][j]);
		for (uint8_t j = 0; j < SENS_VALUES_MONTH; j++) if (data["m_vals"][j] != "") month_values[j] = fromNAN(data["m_vals"][j]);
		for (uint8_t j = 0; j < SENS_VALUES_YEAR; j++) if (data["y_vals"][j] != "") year_values[j] = fromNAN(data["y_vals"][j]);
		
		LOGDEBUG2(F("[Sensor]"), F("deserializeJSON()"), F("OK: Deserialized members for Sensor"), String(data["id"].asString()), "", "");
	}
	else {
		LOGDEBUG2(F("[Sensor]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize members"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}

Sensor::Sensor()
{
	reset();
}
