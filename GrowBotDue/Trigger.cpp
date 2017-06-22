// 
// 
// 

#include "Trigger.h"


Trigger::Trigger() {
	reset();
}

bool Trigger::checkState()
{
	return false;
}

void Trigger::incStartHour()
{
	if (start_hour < 23) {
		start_hour++;
	}
	else start_hour = 0;
}

void Trigger::decStartHour()
{
	if (start_hour > 0) {
		start_hour--;
	}
	else start_hour = 23;
}

void Trigger::incStartMinute()
{
	if (start_minute < 59) {
		start_minute++;
	}
	else start_minute = 0;
}

void Trigger::decStartMinute()
{
	if (start_minute > 0) {
		start_minute--;
	}
	else start_minute = 59;
}

void Trigger::incStartDay()
{
	if (start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12) {
		if (start_day < 31) {
			start_day++;
		}
		else start_day = 1;
	}
	else if (start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) {
		if (start_day < 30) {
			start_day++;
		}
		else start_day = 1;
	}
	else if (start_month == 2 || (start_year % 4) == 0) {
		if (start_day < 29) {
			start_day++;
		}
		else start_day = 1;
	}
	else {
		if (start_day < 28) {
			start_day++;
		}
		else start_day = 1;
	}
}

void Trigger::decStartDay()
{
	if (start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12) {
		if (start_day > 1) {
			start_day--;
		}
		else start_day = 31;
	}
	else if (start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) {
		if (start_day > 1) {
			start_day--;
		}
		else start_day = 30;
	}
	else if (start_month == 2 || (start_year % 4) == 0) {
		if (start_day > 1) {
			start_day--;
		}
		else start_day = 29;
	}
	else {
		if (start_day > 1) {
			start_day--;
		}
		else start_day = 28;
	}
}

void Trigger::incStartMonth()
{
	if (start_month < 12) {
		start_month++;
	}
	else start_month = 1;
}

void Trigger::decStartMonth()
{
	if (start_month > 1) {
		start_month--;
	}
	else start_month = 12;
}

void Trigger::incStartYear()
{
	if (start_year < 2026) {
		start_year++;
	}
	else start_year = 2017;
}

void Trigger::decStartYear()
{
	if (start_year > 2017) {
		start_year--;
	}
	else start_year = 2026;
}

void Trigger::incEndDay()
{
	if (end_month == 1 || end_month == 3 || end_month == 5 || end_month == 7 || end_month == 8 || end_month == 10 || end_month == 12) {
		if (end_day < 31) {
			end_day++;
		}
		else end_day = 1;
	}
	else if (end_month == 4 || end_month == 6 || end_month == 9 || end_month == 11) {
		if (end_day < 30) {
			end_day++;
		}
		else end_day = 1;
	}
	else if (end_month == 2 || (end_year % 4) == 0) {
		if (end_day < 29) {
			end_day++;
		}
		else end_day = 1;
	}
	else {
		if (end_day < 28) {
			end_day++;
		}
		else end_day = 1;
	}
}

void Trigger::decEndDay()
{
	if (end_month == 1 || end_month == 3 || end_month == 5 || end_month == 7 || end_month == 8 || end_month == 10 || end_month == 12) {
		if (end_day > 1) {
			end_day--;
		}
		else end_day = 31;
	}
	else if (end_month == 4 || end_month == 6 || end_month == 9 || end_month == 11) {
		if (end_day > 1) {
			end_day--;
		}
		else end_day = 30;
	}
	else if (end_month == 2 || (end_year % 4) == 0) {
		if (end_day > 1) {
			end_day--;
		}
		else end_day = 29;
	}
	else {
		if (end_day > 1) {
			end_day--;
		}
		else end_day = 28;
	}
}

void Trigger::incEndMonth()
{
	if (end_month < 12) {
		end_month++;
	}
	else end_month = 1;
}

void Trigger::decEndMonth()
{
	if (end_month > 1) {
		end_month--;
	}
	else end_month = 12;
}

void Trigger::incEndYear()
{
	if (end_year < 2027) {
		end_year++;
	}
	else end_year = 2017;
}

void Trigger::decEndYear()
{
	if (end_year > 2017) {
		end_year--;
	}
	else end_year = 2027;
}

void Trigger::incInterval()
{
	switch (interval) {

	case REALTIME:
		interval = TENSEC;
		break;
	case TENSEC:
		interval = TWENTYSEC;
		break;
	case TWENTYSEC:
		interval = THIRTYSEC;
		break;
	case THIRTYSEC:
		interval = ONEMIN;
		break;
	case ONEMIN:
		interval = TWOMIN;
		break;
	case TWOMIN:
		interval = FIVEMIN;
		break;
	case FIVEMIN:
		interval = QUARTER;
		break;
	case QUARTER:
		interval = HALF;
		break;
	case HALF:
		interval = ONE;
		break;
	case ONE:
		interval = TWO;
		break;
	case TWO:
		interval = THREE;
		break;
	case THREE:
		interval = FOUR;
		break;
	case FOUR:
		interval = SIX;
		break;
	case SIX:
		interval = TWELVE;
		break;
	case TWELVE:
		interval = DAILY;
		break;
	case DAILY:
		interval = BIDAILY;
		break;
	case BIDAILY:
		interval = WEEKLY;
		break;
	case WEEKLY:
		interval = BIWEEKLY;
		break;
	case BIWEEKLY:
		interval = REALTIME;
		break;
	}
}

void Trigger::decInterval()
{
	switch (interval) {
	case REALTIME:
		interval = BIWEEKLY;
		break;
	case TENSEC:
		interval = REALTIME;
		break;
	case TWENTYSEC:
		interval = TENSEC;
		break;
	case THIRTYSEC:
		interval = TWENTYSEC;
		break;
	case ONEMIN:
		interval = THIRTYSEC;
		break;	
	case TWOMIN:
		interval = ONEMIN;
		break;
	case FIVEMIN:
		interval = TWOMIN;
		break;
	case QUARTER:
		interval = FIVEMIN;
		break;
	case HALF:
		interval = QUARTER;
		break;
	case ONE:
		interval = HALF;
		break;
	case TWO:
		interval = ONE;
		break;
	case THREE:
		interval = TWO;
		break;
	case FOUR:
		interval = THREE;
		break;
	case SIX:
		interval = FOUR;
		break;
	case TWELVE:
		interval = SIX;
		break;
	case DAILY:
		interval = TWELVE;
		break;
	case BIDAILY:
		interval = DAILY;
		break;
	case WEEKLY:
		interval = BIDAILY;
		break;
	case BIWEEKLY:
		interval = WEEKLY;
		break;
	}
}

void Trigger::incRelOp()
{
	switch (relop) {

	case GREATER:
		relop = SMALLER;
		break;
	case SMALLER:
		relop = EQUAL;
		break;
	case EQUAL:
		relop = GREATER;
		break;
	}
}

void Trigger::decRelOp()
{
	switch (relop) {

	case GREATER:
		relop = EQUAL;
		break;
	case SMALLER:
		relop = GREATER;
		break;
	case EQUAL:
		relop = SMALLER;
		break;
	}
}

void Trigger::incThresh()
{
	threshold++;
}

void Trigger::decThresh()
{
	threshold--;
}

void Trigger::changeActive()
{
	if (active == true) active = false;
	else active = true;
}

String Trigger::getTitle()
{

	return String();
}

String Trigger::getActive()
{
	if (active == true) return String(F("ON"));
	else return String(F("OFF"));
}

String Trigger::getStartDay()
{
	return String(start_day);
}

String Trigger::getStartMonth()
{
	return String(start_month);
}

String Trigger::getStartYear()
{
	return String(start_year);
}

String Trigger::getStartHour()
{
	return String(start_hour);
}

String Trigger::getStartMinute()
{
	return String(start_minute);
}

String Trigger::getEndDay()
{
	return String(end_day);
}

String Trigger::getEndMonth()
{
	return String(end_month);
}

String Trigger::getEndYear()
{
	return String(end_year);
}

String Trigger::getInterval()
{
	switch (this->interval) {

	case REALTIME:
		return String(F("RealTime"));
		break;
	case TENSEC:
		return String(F("10s"));
		break;
	case TWENTYSEC:
		return String(F("20s"));
		break;
	case THIRTYSEC:
		return String(F("30s"));
		break;
	case ONEMIN:
		return String(F("1min"));
		break;
	case TWOMIN:
		return String(F("2min"));
		break;
	case FIVEMIN:
		return String(F("5min"));
		break;
	case QUARTER:
		return String(F("15min"));
		break;
	case HALF:
		return String(F("30min"));
		break;
	case ONE:
		return String(F("1h"));
		break;
	case TWO:
		return String(F("2h"));
		break;
	case THREE:
		return String(F("3h"));
		break;
	case FOUR:
		return String(F("4h"));
		break;
	case SIX:
		return String(F("6h"));
		break;
	case TWELVE:
		return String(F("12h"));
		break;
	case DAILY:
		return String(F("24h"));
		break;
	case BIDAILY:
		return String(F("48h"));
		break;
	case WEEKLY:
		return String(F("7d"));
		break;
	case BIWEEKLY:
		return String(F("14d"));
		break;
	}
}

String Trigger::getRelOp()
{
	if (relop == SMALLER) return String(F("<"));
	else if (relop == EQUAL) return String(F("="));
	else if (relop == GREATER) return String(F(">"));
	else return (F("NULL"));
}

String Trigger::getThresh()
{
	return String(threshold);
}

void Trigger::reset()
{
	active = false;

	start_day = currenttime.current_day;
	start_month = currenttime.current_month;
	start_hour = currenttime.current_hour;
	start_minute = currenttime.current_minute;
	start_year = currenttime.current_year;

	end_day = currenttime.current_day;
	end_month = currenttime.current_month;
	end_hour = currenttime.current_hour;
	end_minute = currenttime.current_minute;
	end_year = start_year + 1;

	interval = ONEMIN;
	relop = EQUAL;
	threshold = 0;
}

void Trigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& trigger = jsonBuffer.createObject();
	
	trigger["type"] = "TRIGGER";
	trigger["cat"] = cat;
	trigger["id"] = id;

	trigger["active"] = active;
	trigger["start_minute"] = start_minute;
	trigger["start_hour"] = start_hour;
	trigger["start_day"] = start_day;
	trigger["start_month"] = start_month;
	trigger["start_year"] = start_year;
	trigger["end_minute"] = end_minute;
	trigger["end_hour"] = end_hour;
	trigger["end_day"] = end_day;
	trigger["end_month"] = end_month;
	trigger["end_year"] = end_year;
	trigger["relop"] = static_cast<int>(relop);
	trigger["threshold"] = threshold;
	trigger["interval"] = static_cast<int>(interval);

	trigger.printTo(json, maxSize);
	LOGDEBUG2(F("[Trigger]"), F("serializeJSON()"), F("OK: Serialized Members for Trigger"), String(getTitle()), String(trigger.measureLength()), String(maxSize));
}

bool Trigger::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		if (data["active"] != "") active = data["active"];
		if (data["start_minute"] != "") start_minute = data["start_minute"];
		if (data["start_hour"] != "") start_hour = data["start_hour"];
		if (data["start_day"] != "") start_day = data["start_day"];
		if (data["start_month"] != "") start_month = data["start_month"];
		if (data["start_year"] != "") start_year = data["start_year"];
		if (data["end_minute"] != "") end_minute = data["end_minute"];
		if (data["end_hour"] != "") end_hour = data["end_hour"];
		if (data["end_day"] != "") end_day = data["end_day"];
		if (data["end_month"] != "") end_month = data["end_month"];
		if (data["end_year"] != "") end_year = data["end_year"];
		if (data["threshold"] != "") threshold = data["threshold"];

		if (data["relop"] != "") {
			if (data["relop"] == 0) relop = SMALLER;
			else if (data["relop"] == 1) relop = EQUAL;
			else if (data["relop"] == 2) relop = GREATER;
			else {
				relop = EQUAL;
				active = false;
			}
		}

		if (data["interval"] != "") {
			if (data["interval"] == 0) interval = REALTIME;
			else if (data["interval"] == 1) interval = TENSEC;
			else if (data["interval"] == 2) interval = TWENTYSEC;
			else if (data["interval"] == 3) interval = THIRTYSEC;
			else if (data["interval"] == 4) interval = ONEMIN;
			else if (data["interval"] == 5) interval = TWOMIN;
			else if (data["interval"] == 6) interval = FIVEMIN;
			else if (data["interval"] == 7) interval = QUARTER;
			else if (data["interval"] == 8) interval = HALF;
			else if (data["interval"] == 9) interval = ONE;
			else if (data["interval"] == 10) interval = TWO;
			else if (data["interval"] == 11) interval = THREE;
			else if (data["interval"] == 12) interval = FOUR;
			else if (data["interval"] == 13) interval = SIX;
			else if (data["interval"] == 14) interval = TWELVE;
			else if (data["interval"] == 15) interval = DAILY;
			else if (data["interval"] == 16) interval = BIDAILY;
			else if (data["interval"] == 17) interval = WEEKLY;
			else if (data["interval"] == 18) interval = BIWEEKLY;
			else {
				interval = ONEMIN;
				active = false;
			}
		}
		LOGDEBUG2(F("[Trigger]"), F("deserializeJSON()"), F("OK: Deserialized members for Trigger"), String(data["cat"].asString()), String(data["id"].asString()), "");
	}
	else {
		LOGDEBUG2(F("[Trigger]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize members of Trigger"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}

TimeTrigger::TimeTrigger(int id)
	: Trigger()
{
	this->id = id;
}

bool TimeTrigger::checkState()
{
	long sensor_start = 0;
	long sensor_end = 0;
	
	bool state = false;
	
	//Transform DateTime in Sensor Cycles as common base
	sensor_start = (CurrentTime::epochTime(start_year, start_month, start_day, start_hour, start_minute, 0)) / SENS_FRQ_SEC;
	sensor_end = (CurrentTime::epochTime(end_year, end_month, end_day, end_hour, end_minute, 0)) / SENS_FRQ_SEC;

	if (active == true) {
		if (sensor_cycles > sensor_start && sensor_cycles < sensor_end) {
			if (interval == REALTIME) state = true;
			else if (interval == TENSEC && ((sensor_cycles - sensor_start) % (10 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == TWENTYSEC && ((sensor_cycles - sensor_start) % (20 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == THIRTYSEC && ((sensor_cycles - sensor_start) % (30 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == ONEMIN && ((sensor_cycles - sensor_start) % (60 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == TWOMIN && ((sensor_cycles - sensor_start) % (120 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == FIVEMIN && ((sensor_cycles - sensor_start) % (300 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == QUARTER && ((sensor_cycles - sensor_start) % (900 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == HALF && ((sensor_cycles - sensor_start) % (1800 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == ONE && ((sensor_cycles - sensor_start) % (3600 / SENS_FRQ_SEC)) == 0)  state = true;
			else if (interval == TWO && ((sensor_cycles - sensor_start) % (7200 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == THREE && ((sensor_cycles - sensor_start) % (10800 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == FOUR && ((sensor_cycles - sensor_start) % (14400 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == SIX && ((sensor_cycles - sensor_start) % (21600 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == TWELVE && ((sensor_cycles - sensor_start) % (43200 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == DAILY && ((sensor_cycles - sensor_start) % (86400 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == BIDAILY && ((sensor_cycles - sensor_start) % (172800 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == WEEKLY && ((sensor_cycles - sensor_start) % (604800 / SENS_FRQ_SEC)) == 0) state = true;
			else if (interval == BIWEEKLY && ((sensor_cycles - sensor_start) % (1209600 / SENS_FRQ_SEC)) == 0) state = true;
			LOGMSG(F("[Trigger]"), F("OK: Time Trigger Checked"), String(getTitle()), F("Time Constraint"), state);
		}
	}
	return state;
}

String TimeTrigger::getTitle()
{
	String name;

	name = String(id) + ':';
	name += currenttime.getTitle();
	name += '(';
	name += (String)start_hour;
	name += ':';
	name += (String)start_minute;
	name += ')';

	return String(name);
}

SensorTrigger::SensorTrigger(int id, Sensor *ptr)
	: Trigger()
{
	this->id = id;
	this->sens_ptr = ptr;
}

bool SensorTrigger::checkState()
{
	long sensor_start;
	short current_value;
	bool state = false;

	//epoch_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, currenttime.current_second);
	sensor_start = (CurrentTime::epochTime(start_year, start_month, start_day, start_hour, start_minute, 0)) / SENS_FRQ_SEC;
	
	if (active == true && interval != NULL) state = sens_ptr->compareWithValue(relop, interval, threshold);
	else state = false;

	LOGMSG(F("[Trigger]"), String("OK: Sensor Trigger Checked " + getTitle()), threshold, current_value, state);
	return state;
}

String SensorTrigger::getTitle()
{
	String name;

	name = String(this->id) + ':';
	name += sens_ptr->getTitle();
	name += "(#";
	name += (String)this->getRelOp();
	name += (String)this->threshold;
	name += ')';

	return String(name);
}