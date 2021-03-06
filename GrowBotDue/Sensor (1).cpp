// 
// 
// 

#include "Sensor.h"
int Sensor::getAvgInt(Interval interval)
{

}

float Sensor::getAvgFloat(Interval interval)
{
	return 0.0f;
}

bool Sensor::compareWithValue(RelOp relop, Interval interval, int value)
{
	return false;
}

String Sensor::getTitle()
{
	return String();
}

String Sensor::getValue()
{
	return String();
}

int Sensor::getMaxValueInt(Scope scope)
{
	return 0;
}

int Sensor::getMinValueInt(Scope scope)
{
	return 0;
}

int Sensor::getElementValueInt(Scope scope, uint8_t element)
{
	return 0;
}

void Sensor::setUpperThreshold()
{
}

void Sensor::setLowerThreshold()
{
}

void Sensor::update()
{
}

void Sensor::reset()
{
}

void Sensor::serializeJSON(uint8_t id, char * json, size_t maxSize, Scope scope)
{
}

bool Sensor::deserializeJSON(JsonObject & data)
{
	return false;
}

template<class ReturnType>
String BaseSensor<ReturnType>::toNAN(ReturnType i)
{
	if (i == nan_val)	return String("#");
	else return String(i);
}

//Different Template Specification for Variable Types
template<class ReturnType>
ReturnType BaseSensor<ReturnType>::fromNAN(String str)
{
	if (str == "#") return nan_val;
	else return ReturnType(str.toInt());
}

template<>
float BaseSensor<float>::fromNAN(String str)
{
	if (str == "#") return nan_val;
	else return str.toFloat();
}

template<class ReturnType>
BaseSensor<ReturnType>::BaseSensor()
{
	reset();
}

template<class ReturnType>
int BaseSensor<ReturnType>::getAvgInt(Interval interval)
{
	switch (interval) {
	case REALTIME:
		return (int)getLastValue();
		break;
	case TENSEC:
		return (int)getTenSecAvg();
		break;
	case TWENTYSEC:
		return (int)getTwentySecAvg();
		break;
	case THIRTYSEC:
		return (int)getThirtySecAvg();
		break;
	case ONEMIN:
		return (int)getOneMinAvg();
		break;
	case TWOMIN:
		return (int)getTwoMinAvg();
		break;
	case FIVEMIN:
		return (int)getFiveMinAvg();
		break;
	case QUARTER:
		return (int)getQuarterHourAvg();
		break;
	case HALF:
		return (int)getHalfHourAvg();
		break;
	case ONE:
		return (int)getHourAvg();
		break;
	case TWO:
		return (int)getTwoHourAvg();
		break;
	case THREE:
		return (int)getThreeHourAvg();
		break;
	case FOUR:
		return (int)getFourHourAvg();
		break;
	case SIX:
		return (int)getSixHourAvg();
		break;
	case TWELVE:
		return (int)getTwelveHourAvg();
		break;
	case DAILY:
		return (int)getDayAvg();
		break;
	case BIDAILY:
		return (int)getTwoDayAvg();
		break;
	case WEEKLY:
		return (int)getWeekAvg();
		break;
	case BIWEEKLY:
		return (int)getTwoWeekAvg();
		break;
	}
}

template<class ReturnType>
float BaseSensor<ReturnType>::getAvgFloat(Interval interval)
{
	switch (interval) {
	case REALTIME:
		return (float)getLastValue();
		break;
	case TENSEC:
		return (float)getTenSecAvg();
		break;
	case TWENTYSEC:
		return (float)getTwentySecAvg();
		break;
	case THIRTYSEC:
		return (float)getThirtySecAvg();
		break;
	case ONEMIN:
		return (float)getOneMinAvg();
		break;
	case TWOMIN:
		return (float)getTwoMinAvg();
		break;
	case FIVEMIN:
		return (float)getFiveMinAvg();
		break;
	case QUARTER:
		return (float)getQuarterHourAvg();
		break;
	case HALF:
		return (float)getHalfHourAvg();
		break;
	case ONE:
		return (float)getHourAvg();
		break;
	case TWO:
		return (float)getTwoHourAvg();
		break;
	case THREE:
		return (float)getThreeHourAvg();
		break;
	case FOUR:
		return (float)getFourHourAvg();
		break;
	case SIX:
		return (float)getSixHourAvg();
		break;
	case TWELVE:
		return (float)getTwelveHourAvg();
		break;
	case DAILY:
		return (float)getDayAvg();
		break;
	case BIDAILY:
		return (float)getTwoDayAvg();
		break;
	case WEEKLY:
		return (float)getWeekAvg();
		break;
	case BIWEEKLY:
		return (float)getTwoWeekAvg();
		break;
	}
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getLastValue()
{
	return minute_values[minute_ptr];
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTenSecAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = 60 / SENS_VALUES_MIN;
	element_count = 10 / interval;

	return ReturnType(average(minute_ptr, element_count, minute_values, SENS_VALUES_MIN));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwentySecAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = 60 / SENS_VALUES_MIN;
	element_count = 20 / interval;

	return ReturnType(average(minute_ptr, element_count, minute_values, SENS_VALUES_MIN));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getThirtySecAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = 60 / SENS_VALUES_MIN;
	element_count = 30 / interval;

	return ReturnType(average(minute_ptr, element_count, minute_values, SENS_VALUES_MIN));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getOneMinAvg()
{
	return ReturnType(average(minute_ptr, SENS_VALUES_MIN, minute_values, SENS_VALUES_MIN));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwoMinAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_HOUR / 60;
	element_count = 2 * interval;

	return ReturnType(average(hour_ptr, element_count, hour_values, SENS_VALUES_HOUR));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getFiveMinAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_HOUR / 60;
	element_count = 5 * interval;

	return ReturnType(average(hour_ptr, element_count, hour_values, SENS_VALUES_HOUR));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getQuarterHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_HOUR / 60;
	element_count = 15 * interval;

	return ReturnType(average(hour_ptr, element_count, hour_values, SENS_VALUES_HOUR));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getHalfHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_HOUR / 60;
	element_count = 30 * interval;

	return ReturnType(average(hour_ptr, element_count, hour_values, SENS_VALUES_HOUR));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getHourAvg()
{
	return ReturnType(average(hour_ptr, SENS_VALUES_HOUR, hour_values, SENS_VALUES_HOUR));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwoHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_DAY / 24;
	element_count = 2 * interval;

	return ReturnType(average(day_ptr, element_count, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getThreeHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_DAY / 24;
	element_count = 3 * interval;

	return ReturnType(average(day_ptr, element_count, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getFourHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_DAY / 24;
	element_count = 4 * interval;

	return ReturnType(average(day_ptr, element_count, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getSixHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_DAY / 24;
	element_count = 6 * interval;

	return ReturnType(average(day_ptr, element_count, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwelveHourAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_DAY / 24;
	element_count = 12 * interval;

	return ReturnType(average(day_ptr, element_count, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getDayAvg()
{
	return ReturnType(average(day_ptr, SENS_VALUES_DAY, day_values, SENS_VALUES_DAY));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwoDayAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_MONTH / 28;
	element_count = 2 * interval;
	
	return ReturnType(average(month_ptr, element_count, month_values, SENS_VALUES_MONTH));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getWeekAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_MONTH / 28;
	element_count = 7 * interval;

	return ReturnType(average(month_ptr, element_count, month_values, SENS_VALUES_MONTH));
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::getTwoWeekAvg()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;

	interval = SENS_VALUES_MONTH / 28;
	element_count = 14 * interval;

	return ReturnType(average(month_ptr, element_count, month_values, SENS_VALUES_MONTH));
}

template<class ReturnType>
String BaseSensor<ReturnType>::getValue()
{
	return String(readValue()) + String(unit);
}

template<class ReturnType>
String BaseSensor<ReturnType>::getTitle()
{
	return String(title);
}

template<class ReturnType>
int BaseSensor<ReturnType>::getMaxValueInt(Scope scope)
{
	int max = 0;

	switch (scope) {

	case DATE_MINUTE:
		max = maxValue(minute_values, SENS_VALUES_MIN);
		break;

	case DATE_HOUR:
		max = maxValue(hour_values, SENS_VALUES_HOUR);
		break;

	case DATE_DAY:
		max = maxValue(day_values, SENS_VALUES_DAY);
		break;

	case DATE_MONTH:
		max = maxValue(month_values, SENS_VALUES_MONTH);
		break;

	case DATE_YEAR:
		max = maxValue(year_values, SENS_VALUES_YEAR);
		break;
	}
	return int(max);
}

template<class ReturnType>
int BaseSensor<ReturnType>::getMinValueInt(Scope scope)
{
	int min = 0;

	switch (scope) {

	case DATE_MINUTE:
		min = minValue(minute_values, SENS_VALUES_MIN);
		break;

	case DATE_HOUR:
		min = minValue(hour_values, SENS_VALUES_HOUR);
		break;

	case DATE_DAY:
		min = minValue(day_values, SENS_VALUES_DAY);
		break;

	case DATE_MONTH:
		min = minValue(month_values, SENS_VALUES_MONTH);
		break;

	case DATE_YEAR:
		min = minValue(year_values, SENS_VALUES_YEAR);
		break;
	}
	return int(min);
}

template<class ReturnType>
int BaseSensor<ReturnType>::getElementValueInt(Scope scope, uint8_t element)
{
	int element_val = 0;

	switch (scope) {

	case DATE_MINUTE:
		if (element >= 0 && element < SENS_VALUES_MIN) element_val = minute_values[element];
		else element_val = nan_val;
		break;

	case DATE_HOUR:
		if (element >= 0 && element < SENS_VALUES_HOUR) element_val = hour_values[element];
		else element_val = nan_val;
		break;

	case DATE_DAY:
		if (element >= 0 && element < SENS_VALUES_DAY) element_val = day_values[element];
		else element_val = nan_val;
		break;

	case DATE_MONTH:
		if (element >= 0 && element < SENS_VALUES_MONTH) element_val = month_values[element];
		else element_val = nan_val;
		break;

	case DATE_YEAR:
		if (element >= 0 && element < SENS_VALUES_YEAR) element_val = year_values[element];
		else element_val = nan_val;
		break;
	}
	return int(element_val);
}

template<class ReturnType>
void BaseSensor<ReturnType>::setUpperThreshold()
{

}

template<class ReturnType>
void BaseSensor<ReturnType>::setLowerThreshold()
{

}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::readRaw()
{
	return ReturnType();
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::readValue()
{
	return ReturnType();
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::average(uint8_t start, uint8_t num_elements, ReturnType * values, uint8_t max)
{
	//LOGDEBUG2(F("[Sensor]"), F("average()"), String(title), String(start), String(num_elements), String(max));
	
	int dividend = 0;
	int divisor = 0;
	ReturnType avg = nan_val;

	uint8_t counter = 0;
	short element_ptr = start;

	while (counter <= num_elements)
	{
		if (values[element_ptr] != nan_val) {
			dividend += values[element_ptr];
			divisor++;
			//LOGDEBUG2(F("[Sensor]"), F("average()"), String(title), String(element_ptr), String(dividend), String(divisor));
		}
		else break;

		//Raise counter
		counter++;
		//Move pointer to previous element
		element_ptr--;
		if (element_ptr < 0) {
			element_ptr = max - 1; //-1 because MAX is NaN value
		}
	}

	if (divisor != 0) {
		avg = (int)round(dividend / divisor);
	}
	else {
		avg = nan_val;
		LOGDEBUG(F("[Sensor]"), F("average()"), F("Warning: Division by Zero. Returning NaN Value"), String(dividend), String(divisor), String(nan_val));
		
	}

	return ReturnType(avg);
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::minValue(ReturnType * values, uint8_t max)
{
	ReturnType min_val = this->min_val;
	for (uint8_t i = 0; i < max; i++) {
		if (values[i] < min_val) min_val = values[i];
	}
	LOGDEBUG(F("[SensorGraph]"), F("minValue()"), F("OK: Minimum value in Sensor data"), String(min_val), "", "");
	return ReturnType(min_val);
}

template<class ReturnType>
ReturnType BaseSensor<ReturnType>::maxValue(ReturnType * values, uint8_t max)
{
	ReturnType max_val = this->max_val;
	for (uint8_t i = 0; i < max; i++) {
		if (values[i] > max_val) max_val = values[i];
	}
	LOGDEBUG(F("[SensorGraph]"), F("maxValue()"), F("OK: Maximum value in Sensor data"), String(max_val), "", "");
	return ReturnType(max_val);
}

template<>
float BaseSensor<float>::average(uint8_t start, uint8_t num_elements, float * values, uint8_t max)
{
	//LOGDEBUG2(F("[Sensor]"), F("average()"), String(title), String(start), String(num_elements), String(max));
	
	float dividend = 0;
	int divisor = 0;
	float avg = nan_val;

	uint8_t counter = 0;
	short element_ptr = start;

	while (counter <= num_elements)
	{
		if (values[element_ptr] != nan_val) {
			dividend += values[element_ptr];
			divisor++;
		}
		else break;

		//Raise counter
		counter++;
		//Move pointer to previous element
		element_ptr--;
		if (element_ptr < 0) {
			element_ptr = max - 1; //-1 because MAX is NaN value
		}
	}

	if (divisor != 0) {
		avg = dividend / divisor;
	}
	else {
		avg = nan_val;
		LOGDEBUG(F("[Sensor]"), F("average()"), F("Warning: Division by Zero. Returning NaN Value"), String(dividend), String(divisor), String(nan_val));
	}

	return float(avg);
}

template<class ReturnType>
void BaseSensor<ReturnType>::update()
{
	uint8_t interval = 0;
	uint8_t element_count = 0;
	
	//Minutes -> read sensor every 60/SENS_VALUES_MINS Seconds -> Example: 5 Seconds
	if (minute_ptr < SENS_VALUES_MIN - 1) 	minute_ptr++;
	else minute_ptr = 0;
	
	minute_values[minute_ptr] = readValue();

	//Hour -> calculate average every MINUTE / (SENS_VALUES_HOUR /60)  -> Example: 1 Minute
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR) && sensor_cycles % (SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR) == 0) {
		if (hour_ptr < SENS_VALUES_HOUR - 1) hour_ptr++;
		else hour_ptr = 0;

		element_count = SENS_VALUES_MIN * 60 / SENS_VALUES_HOUR;
		hour_values[hour_ptr] = average(minute_ptr, element_count, minute_values, SENS_VALUES_MIN);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new HOUR Value for"), String(getTitle()), String(hour_ptr), String(hour_values[hour_ptr]));
	}

	//Day -> calculate average every HOUR / (SENS_VALUES_DAY/24)  -> Example: 1/4 Hour
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 / SENS_VALUES_DAY) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 / SENS_VALUES_DAY) == 0) {
		if (day_ptr < SENS_VALUES_DAY - 1) 	day_ptr++;
		else day_ptr = 0;

		element_count = SENS_VALUES_HOUR * 24 / SENS_VALUES_DAY;
		day_values[day_ptr] = average(hour_ptr, element_count, hour_values, SENS_VALUES_HOUR);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new DAY Value for"), String(getTitle()), String(day_ptr), String(day_values[day_ptr]));
	}

	//Month-> calculate average every DAY / (SENS_VALUES_MONTH/28)  -> Example: 1/2 Day
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 * 28 / SENS_VALUES_MONTH) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 * 28 / SENS_VALUES_MONTH) == 0) {
		if (month_ptr < SENS_VALUES_MONTH - 1) 	month_ptr++;
		else month_ptr = 0;
			
		element_count = SENS_VALUES_DAY * 28 / SENS_VALUES_MONTH;
		month_values[month_ptr] = average(day_ptr, element_count, day_values, SENS_VALUES_DAY);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new MONTH Value for"), String(getTitle()), String(month_ptr), String(month_values[month_ptr]));
	}
	//Year-> calculate average once a week -> Example: 7 Days
	if (sensor_cycles >= (SENS_VALUES_MIN * 60 * 24 * 7 * 52 / SENS_VALUES_YEAR) && sensor_cycles % (SENS_VALUES_MIN * 60 * 24 * 7 * 52 / SENS_VALUES_YEAR) == 0) {
		if (year_ptr < SENS_VALUES_YEAR - 1)	year_ptr++;
		else year_ptr = 0;

		element_count = (SENS_VALUES_MONTH / 4) * (52 / SENS_VALUES_YEAR);
		year_values[year_ptr] = average(month_ptr, element_count, month_values, SENS_VALUES_MONTH);
		LOGDEBUG(F("[Sensor]"), F("update()"), F("OK: Saved new YEAR Value for"), String(getTitle()), String(year_ptr), String(year_values[year_ptr]));
	}
}

template<class ReturnType>
void BaseSensor<ReturnType>::reset()
{
	lower_threshold = 0;
	upper_threshold = 0;
	
	minute_ptr = SENS_VALUES_MIN;
	hour_ptr = SENS_VALUES_HOUR;
	day_ptr = SENS_VALUES_DAY;
	month_ptr = SENS_VALUES_MONTH;
	year_ptr = SENS_VALUES_YEAR;

	for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) minute_values[i] = nan_val;
	for (uint8_t i = 0; i < SENS_VALUES_HOUR; i++) hour_values[i] = nan_val;
	for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) day_values[i] = -5 + (rand() % static_cast<int>(35 - (-5) + 1));
	for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) month_values[i] = -5 + (rand() % static_cast<int>(35 - (-5) + 1));
	for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) year_values[i] = -5 + (rand() % static_cast<int>(35 - (-5) + 1));
}

template<class ReturnType>
void BaseSensor<ReturnType>::serializeJSON(uint8_t id, char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<8000> jsonBuffer;

	JsonObject& sensor = jsonBuffer.createObject();


	//List View
	if (scope == LIST) {

		sensor["tit"] = title;
		sensor["unit"] = unit;
	}

	//Sensor View
	//Header
	if (scope == HEADER || scope == DETAILS || scope == AVG || scope == DATE_MINUTE || scope == DATE_HOUR || scope == DATE_DAY || scope == DATE_MONTH || scope == DATE_YEAR || scope == DATE_ALL) {
		sensor["obj"] = "SENSOR";
		
		//Too much data for AT Interface => different scopes
		switch (scope) {
		case Scope::HEADER:
			sensor["scp"] = "HEADER";
			break;
		case Scope::DETAILS:
			sensor["scp"] = "DETAILS";
			break;
		case Scope::AVG:
			sensor["scp"] = "AVG";
			break;
		case Scope::DATE_MINUTE:
			sensor["scp"] = "MIN";
			break;
		case Scope::DATE_HOUR:
			sensor["scp"] = "HOUR";
			break;
		case Scope::DATE_DAY:
			sensor["scp"] = "DAY";
			break;
		case Scope::DATE_MONTH:
			sensor["scp"] = "MON";
			break;
		case Scope::DATE_YEAR:
			sensor["scp"] = "YEAR";
			break;
		case Scope::DATE_ALL:
			sensor["scp"] = "ALL";
			break;
		}

		sensor["id"] = id;
		sensor["tit"] = title;
		sensor["unit"] = unit;
		sensor["nan"] = nan_val;
		sensor["min"] = min_val;
		sensor["max"] = max_val;
		sensor["low"] = lower_threshold;
		sensor["high"] = upper_threshold;	
	}

	//AVG Values
	if (scope == DETAILS || scope == AVG) {
		JsonObject& avg = sensor.createNestedObject("avg_vals");
		avg["last"] = getLastValue();
		avg["10s"] = getTenSecAvg();
		avg["20s"] = getTwentySecAvg();
		avg["30s"] = getThirtySecAvg();
		avg["1min"] = getOneMinAvg();
		avg["2min"] = getTwoMinAvg();
		avg["5min"] = getFiveMinAvg();
		avg["15min"] = getQuarterHourAvg();
		avg["30min"] = getHalfHourAvg();
		avg["1h"] = getHourAvg();
		avg["2h"] = getTwoHourAvg();
		avg["3h"] = getThreeHourAvg();
		avg["4h"] = getFourHourAvg();
		avg["6h"] = getSixHourAvg();
		avg["12h"] = getTwelveHourAvg();
		avg["1d"] = getDayAvg();
		avg["2d"] = getTwoDayAvg();
		avg["1w"] = getWeekAvg();
		avg["2w"] = getTwoWeekAvg();
	}

	//Min Values
	if (scope == DETAILS || scope == DATE_MINUTE || scope == DATE_ALL) {
		sensor["min_ptr"] = minute_ptr;
		sensor["frq"] = SENS_VALUES_MIN;
		JsonArray& minutes = sensor.createNestedArray("min_vals");
		for (uint8_t j = 0; j < SENS_VALUES_MIN; j++) minutes.add(toNAN(minute_values[j]));
	}

	//Hour Values
	if (scope == DETAILS || scope == DATE_HOUR || scope == DATE_ALL) {
		sensor["h_ptr"] = hour_ptr;
		sensor["frq"] = SENS_VALUES_HOUR;
		JsonArray& hours = sensor.createNestedArray("h_vals");
		for (uint8_t j = 0; j < SENS_VALUES_HOUR; j++) hours.add(toNAN(hour_values[j]));
	}

	//Day Values
	if (scope == DETAILS || scope == DATE_DAY || scope == DATE_ALL) {
		sensor["d_ptr"] = day_ptr;
		sensor["frq"] = SENS_VALUES_DAY;
		JsonArray& days = sensor.createNestedArray("d_vals");
		for (uint8_t j = 0; j < SENS_VALUES_DAY; j++) days.add(toNAN(day_values[j]));
	}

	//Month Values
	if (scope == DETAILS || scope == DATE_MONTH || scope == DATE_ALL) {
		sensor["m_ptr"] = month_ptr;
		sensor["frq"] = SENS_VALUES_MONTH;
		JsonArray& month = sensor.createNestedArray("m_vals");
		for (uint8_t j = 0; j < SENS_VALUES_MONTH; j++) month.add(toNAN(month_values[j]));
	}

	//Year Values
	if (scope == DETAILS || scope == DATE_YEAR || scope == DATE_ALL) {
		sensor["y_ptr"] = year_ptr;
		sensor["frq"] = SENS_VALUES_YEAR;
		JsonArray& year = sensor.createNestedArray("y_vals");
		for (uint8_t j = 0; j < SENS_VALUES_YEAR; j++) year.add(toNAN(year_values[j]));
	}

	sensor.printTo(json, maxSize);
	LOGDEBUG2(F("[Sensor]"), F("serializeJSON()"), F("OK: Serialized members for Sensor"), String(id), String(sensor.measureLength()), String(maxSize));
}

template<class ReturnType>
bool BaseSensor<ReturnType>::deserializeJSON(JsonObject & data)
{
	if (data.success() == true) {
		if (data["low"] != "") lower_threshold = data["low"];
		if (data["high"] != "") upper_threshold = data["high"];

		if (data["min_ptr"] != "") minute_ptr = data["min_ptr"];
		if (data["h_ptr"] != "") hour_ptr = data["h_ptr"];
		if (data["d_ptr"] != "") day_ptr = data["d_ptr"];
		if (data["m_ptr"] != "") month_ptr = data["m_ptr"];
		if (data["y_ptr"] != "") year_ptr = data["y_ptr"];

		for (uint8_t j = 0; j < SENS_VALUES_MIN; j++) if (data["min_vals"][j] != "") minute_values[j] = fromNAN(data["min_vals"][j]);
		for (uint8_t j = 0; j < SENS_VALUES_HOUR; j++) if (data["h_vals"][j] != "") hour_values[j] = fromNAN(data["h_vals"][j]);
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

template<class ReturnType>
AnalogMoistureSensor<ReturnType>::AnalogMoistureSensor(uint8_t pin, uint8_t power_pin, bool active, String title, String unit, ReturnType nan_val, ReturnType min_val, ReturnType max_val, ReturnType lower_threshold, ReturnType upper_threshold)
{
	this->pin = pin;
	this->power_pin = power_pin;
	this->active = active;
	this->title = title;
	this->unit = unit;
	this->nan_val = nan_val;
	this->min_val = min_val;
	this->max_val = max_val;
	
	this->lower_threshold = lower_threshold;
	this->upper_threshold = upper_threshold;


	pinMode(pin, INPUT);
	pinMode(power_pin, OUTPUT);
}

template<class ReturnType>
ReturnType AnalogMoistureSensor<ReturnType>::readRaw()
{
	int dividend = 0;
	int divisor = 0;
	ReturnType adj_val;
	ReturnType current_value;

	//Turn on Power supply
	digitalWrite(power_pin, HIGH);
	//Read 5 times just to make sure
	for (uint8_t i = 0; i < 3; i++) {
		delay(100);
		current_value = analogRead(this->pin);
		//LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Analog Moisture Raw Value"), String(current_value), "", "");
		if (current_value != this->nan_val) {
			dividend += current_value;
			divisor++;
		}
	}

	if (divisor > 0) {
		adj_val = round(dividend / divisor);
		//LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Analog Moisture Average Reading"), String(adj_val), "", "");
	}
	else adj_val = this->nan_val;

	//Turn Power Off
	digitalWrite(power_pin, LOW);
	
	
	return ReturnType(adj_val);
}

template<class ReturnType>
ReturnType AnalogMoistureSensor<ReturnType>::readValue()
{
	ReturnType adj_val;
	
	adj_val = readRaw();

	//Caluclate Percentage if NaN not set
	if (adj_val != this->nan_val) {
		if (adj_val >= this->upper_threshold) {
			adj_val = ReturnType(0);
		}
		else if (adj_val <= this->lower_threshold) {
			adj_val = ReturnType(100);
		}
		else {
			adj_val = ReturnType(round(float(this->upper_threshold - adj_val) / float(this->upper_threshold - this->lower_threshold)*100));
		}
	}
	//LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Moisture Value % "), String(adj_val), String(this->lower_threshold), String(this->upper_threshold));
	return adj_val;
}

template<>
float AnalogMoistureSensor<float>::readRaw() 
{
	float dividend = 0;
	int divisor = 0;
	float adj_val = 0;
	float current_value = 0;

	//Turn on Power supply
	digitalWrite(power_pin, HIGH);

	//Read 5 times just to make sure
	for (uint8_t i = 0; i < 3; i++) {
		delay(150);
		current_value = analogRead(pin);
		//LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Analog Moisture Raw Value"), String(current_value), "", "");
		if (current_value != nan_val) {
			dividend += current_value;
			divisor++;
		}
	}

	if (divisor > 0) {
		adj_val = dividend / divisor;
		//LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Analog Moisture Average Raw"), String(adj_val), "", "");
	}
	else adj_val = nan_val;

	//Turn Power Off
	digitalWrite(power_pin, LOW);
}

template<>
float AnalogMoistureSensor<float>::readValue()
{
	float adj_val = 0;
	
	adj_val = readRaw();

	//Caluclate Percentage if NaN not set
	if (adj_val != nan_val) {
		if (adj_val >= this->upper_threshold) adj_val = float(0);
		else if (adj_val <= this->lower_threshold) adj_val = float(100);
		else {
			adj_val = float(float(adj_val - this->lower_threshold) / float(this->upper_threshold - this->lower_threshold)*100);
		}
	}

	LOGDEBUG(F("[Sensor]"), F("readValue()"), F("Info: Moisture Value % "), String(adj_val), String(this->upper_threshold), String(this->lower_threshold));
	return adj_val;
}


template<class ReturnType>
String AnalogMoistureSensor<ReturnType>::getValue()
{
	return String(readValue()) + String(this->unit);
}

template<class ReturnType>
void AnalogMoistureSensor<ReturnType>::setUpperThreshold()
{
	this->upper_threshold = readRaw();
	LOGDEBUG(F("[Sensor]"), F("setUpperThreshold()"), F("Info: Set Lower Threshold to "), String(this->upper_threshold), "", "");
}

template<class ReturnType>
void AnalogMoistureSensor<ReturnType>::setLowerThreshold()
{
	this->lower_threshold = readRaw();
	LOGDEBUG(F("[Sensor]"), F("setUpperThreshold()"), F("Info: Set Lower Threshold to "), String(this->lower_threshold), "", "");
}

template<class ReturnType>
bool AnalogMoistureSensor<ReturnType>::compareWithValue(RelOp relop, Interval interval, int value)
{
	bool state;
	int current_value = this->getAvgInt(interval);
	
	if (current_value != this->nan_val) {
		if (relop == EQUAL && current_value == value) state = true;
		else if (relop == GREATER && current_value > value) state = true;
		else if (relop == SMALLER && current_value < value) state = true;
		else state = false;
	}
	else false;

	return state;
}

template<>
bool AnalogMoistureSensor<float>::compareWithValue(RelOp relop, Interval interval, int value)
{
	bool state;
	float current_value = getAvgFloat(interval);

	if (current_value != this->nan_val) {
		if (relop == EQUAL && current_value == value) state = true;
		else if (relop == GREATER && current_value > value) state = true;
		else if (relop == SMALLER && current_value < value) state = true;
		else state = false;
	}
	else false;

	return state;
}


template<>
String AnalogMoistureSensor<float>::getValue()
{
	return String(readValue(), 2) + String(this->unit);
}


DHTTemperature::DHTTemperature(DHT *hardware, bool active, String title, String unit, int8_t nan_val, int8_t min_val, int8_t max_val)
{
	this->dht = hardware;

	this->title = title;
	this->active = active;
	this->unit = unit;
	this->nan_val = nan_val;
	this->max_val = max_val;
	this->min_val = min_val;

	this->lower_threshold = 0;
	this->upper_threshold = 0;
}

int8_t DHTTemperature::readRaw()
{
	return int8_t(round(dht->readTemperature()));
}


int8_t DHTTemperature::readValue()
{
	return int8_t(round(dht->readTemperature()));
}

String DHTTemperature::getValue()
{
	return String(dht->readTemperature(), 2) + String(unit);
}

void DHTTemperature::setUpperThreshold()
{
}

void DHTTemperature::setLowerThreshold()
{
}

bool DHTTemperature::compareWithValue(RelOp relop, Interval interval, int value)
{
	bool state;
	int current_value = getAvgInt(interval);

	if (current_value != this->nan_val) {
		if (relop == EQUAL && current_value == value) state = true;
		else if (relop == GREATER && current_value > value) state = true;
		else if (relop == SMALLER && current_value < value) state = true;
		else state = false;
	}
	else false;

	return state;
}

DHTHumidity::DHTHumidity(DHT *hardware, bool active, String title, String unit, int8_t nan_val, int8_t min_val, int8_t max_val)
{
	this->dht = hardware;

	this->title = title;
	this->active = active;
	this->unit = unit;
	this->nan_val = nan_val;
	this->max_val = max_val;
	this->min_val = min_val;

	this->lower_threshold = 0;
	this->upper_threshold = 0;
}

int8_t DHTHumidity::readRaw()
{
	return int8_t(round(dht->readHumidity()));
}

int8_t DHTHumidity::readValue()
{
	return int8_t(round(dht->readHumidity()));
}

String DHTHumidity::getValue()
{
	return String(dht->readHumidity(), 2) + String(unit);
}

void DHTHumidity::setUpperThreshold()
{
}

void DHTHumidity::setLowerThreshold()
{
}

bool DHTHumidity::compareWithValue(RelOp relop, Interval interval, int value)
{
	bool state;
	int current_value = getAvgInt(interval);

	if (current_value != this->nan_val) {
		if (relop == EQUAL && current_value == value) state = true;
		else if (relop == GREATER && current_value > value) state = true;
		else if (relop == SMALLER && current_value < value) state = true;
		else state = false;
	}
	else false;

	return state;
}

template class AnalogMoistureSensor<short>;