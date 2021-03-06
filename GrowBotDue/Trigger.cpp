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

String Trigger::getTitle()
{

	return String(title);
}

String Trigger::getSource()
{
	return String(source);
}

void Trigger::reset()
{
	
}

void Trigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize, Scope scope)
{
}

bool Trigger::deserializeJSON(JsonObject & data)
{
	return false;
}

void TimeTrigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& trigger = jsonBuffer.createObject();
	
	if (scope == LIST || scope == DETAILS) {
		trigger["tit"] = title;
		trigger["act"] = active;
		trigger["src"] = source;
		trigger["typ"] = static_cast<int>(type);
	}

	if (scope == DETAILS) {
		trigger["obj"] = "TRIGGER";
		trigger["cat"] = cat;
		trigger["id"] = id;
		trigger["start_time"] = start_time;
		trigger["end_time"] = end_time;
		trigger["relop"] = static_cast<int>(relop);
		trigger["fire"] = fired;
		trigger["val"] = threshold;
		trigger["intv"] = static_cast<int>(interval);
		trigger["tol"] = tolerance;
	}

	trigger.printTo(json, maxSize);
	LOGDEBUG2(F("[Trigger]"), F("serializeJSON()"), F("OK: Serialized Members for Trigger"), String(getTitle()), String(trigger.measureLength()), String(maxSize));
}

bool TimeTrigger::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		if (data["tit"] != "") title = data["tit"].asString();
		if (data["act"] != "") active = data["act"];
		if (data["fire"] != "") fired = data["fire"];
		if (data["start_time"] != "") start_time = data["start_time"];
		if (data["end_time"] != "") end_time = data["end_time"];	
		if (data["val"] != "") threshold = data["val"];
		if (data["tol"] != "") tolerance = data["tol"];

		if (data["typ"] != "") {
			if (data["typ"] == 0) type = TIME;
			else if (data["typ"] == 1) type = SENSOR;
			else {
				relop = EQUAL;
				active = false;
			}
		}

		if (data["relop"] != "") {
			if (data["relop"] == 0) relop = SMALLER;
			else if (data["relop"] == 1) relop = EQUAL;
			else if (data["relop"] == 2) relop = GREATER;
			else if (data["relop"] == 3) relop = NOTEQUAL;
			else {
				relop = EQUAL;
				active = false;
			}
		}

		if (data["intv"] != "") {
			if (data["intv"] == 0) interval = REALTIME;
			else if (data["intv"] == 1) interval = TENSEC;
			else if (data["intv"] == 2) interval = TWENTYSEC;
			else if (data["intv"] == 3) interval = THIRTYSEC;
			else if (data["intv"] == 4) interval = ONEMIN;
			else if (data["intv"] == 5) interval = TWOMIN;
			else if (data["intv"] == 6) interval = FIVEMIN;
			else if (data["intv"] == 7) interval = QUARTER;
			else if (data["intv"] == 8) interval = HALF;
			else if (data["intv"] == 9) interval = ONE;
			else if (data["intv"] == 10) interval = TWO;
			else if (data["intv"] == 11) interval = THREE;
			else if (data["intv"] == 12) interval = FOUR;
			else if (data["intv"] == 13) interval = SIX;
			else if (data["intv"] == 14) interval = TWELVE;
			else if (data["intv"] == 15) interval = DAILY;
			else if (data["intv"] == 16) interval = BIDAILY;
			else if (data["intv"] == 17) interval = WEEKLY;
			else if (data["intv"] == 18) interval = BIWEEKLY;
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

void TimeTrigger::reset()
{
	title = "Timer ";
	title += String(id);

	active = false;
	fired = false;

	start_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month, internalRTC.defaulttime.Day, 0, 0, 0);
	end_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month + 1, internalRTC.defaulttime.Day, 0, 0, 0);

	interval = ONEMIN;
	relop = EQUAL;
	threshold = 0;
	tolerance = 0;
}


TimeTrigger::TimeTrigger(int id)
	: Trigger()
{
	this->id = id;
	this->title = "Timer " + String(id);
	this->type = TIME;
	this->source = String(F("RTC"));
}

bool TimeTrigger::checkState()
{
	long sensor_start = 0;
	long sensor_end = 0;
	
	bool state = false;
	
	//Transform Timestamp in Sensor Cycles as common base
	sensor_start = (start_time + internalRTC.timezone_offset) / SENS_FRQ_SEC;
	sensor_end = (end_time + internalRTC.timezone_offset) / SENS_FRQ_SEC;

	if (active == true) {
		if (sensor_cycles > sensor_start && sensor_cycles < sensor_end) {
			switch (interval) {
			case REALTIME:
				state = true;
				break;
			case TENSEC:
				if (checkStateInterval(sensor_start, 10)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 15)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case TWENTYSEC:
				if (checkStateInterval(sensor_start, 20))	{
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 25)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case THIRTYSEC:
				if (checkStateInterval(sensor_start, 30)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 40)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case ONEMIN:
				if (checkStateInterval(sensor_start, 60)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 75)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case TWOMIN:
				if (checkStateInterval(sensor_start, 120)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 150)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case FIVEMIN:
				if (checkStateInterval(sensor_start, 300)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 375)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case QUARTER:
				if (checkStateInterval(sensor_start, 900)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 1125)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case HALF:
				if (checkStateInterval(sensor_start, 1800)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 2250)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case ONE:
				if (checkStateInterval(sensor_start, 3600)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 4500)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case TWO:
				if (checkStateInterval(sensor_start, 7200)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 8100)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case THREE:
				if (checkStateInterval(sensor_start, 10800)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 11700)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case FOUR:
				if (checkStateInterval(sensor_start, 14400)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 15300)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case SIX:
				if (checkStateInterval(sensor_start, 21600)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 22500)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case TWELVE:
				if (checkStateInterval(sensor_start, 43200)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 44100)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case DAILY:
				if (checkStateInterval(sensor_start, 86400)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 90000)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case BIDAILY:
				if (checkStateInterval(sensor_start, 172800)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 176400)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case WEEKLY:
				if (checkStateInterval(sensor_start, 604800)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 608400)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			case BIWEEKLY:
				if (checkStateInterval(sensor_start, 1209600)) {
					fired = true;
					state = true;
				}
				else if (checkStateInterval(sensor_start, 1213200)) {
					if (fired != true) state = true;
					else fired = false;
				}
				break;
			}
		}
	}
	return state;
}

bool TimeTrigger::checkStateInterval(long sensor_start, uint8_t length)
{
	return 	((sensor_cycles - sensor_start) % (length / SENS_FRQ_SEC) == 0);
}


SensorTrigger::SensorTrigger(int id, Sensor *ptr)
	: Trigger()
{
	this->id = id;
	this->sens_ptr = ptr;
	this->title += "Comparator ";
	this->title += String(id);
	this->type = SENSOR;
	this->source = sens_ptr->getTitle();
}

bool SensorTrigger::checkState()
{
	bool state = false;

	if (active == true) state = sens_ptr->compareWithValue(relop, interval, threshold, tolerance);
	else state = false;

	LOGMSG(F("[Trigger]"), String("OK: Sensor Trigger Checked " + getTitle()), threshold, interval, state);
	return state;
}

void SensorTrigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<JSONBUFFER_SIZE> jsonBuffer;

	JsonObject& trigger = jsonBuffer.createObject();

if (scope == LIST || scope == DETAILS) {
	trigger["tit"] = title;
	trigger["act"] = active;
	trigger["src"] = source;
	trigger["typ"] = static_cast<int>(type);
}

if (scope == DETAILS) {
	trigger["obj"] = "TRIGGER";
	trigger["cat"] = cat;
	trigger["id"] = id;
	trigger["start_time"] = start_time;
	trigger["end_time"] = end_time;
	trigger["intv"] = static_cast<int>(interval);
	trigger["relop"] = static_cast<int>(relop);
	trigger["val"] = threshold;
	trigger["tol"] = tolerance;
}

trigger.printTo(json, maxSize);
LOGDEBUG2(F("[Trigger]"), F("serializeJSON()"), F("OK: Serialized Members for Trigger"), String(getTitle()), String(trigger.measureLength()), String(maxSize));
}

bool SensorTrigger::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		if (data["tit"] != "") title = data["tit"].asString();
		if (data["act"] != "") active = data["act"];
		if (data["start_time"] != "") start_time = data["start_time"];
		if (data["end_time"] != "") end_time = data["end_time"];
		if (data["val"] != "") threshold = data["val"];
		if (data["tol"] != "") tolerance = data["tol"];

		if (data["relop"] != "") {
			if (data["relop"] == 0) relop = SMALLER;
			else if (data["relop"] == 1) relop = EQUAL;
			else if (data["relop"] == 2) relop = GREATER;
			else if (data["relop"] == 3) relop = NOTEQUAL;
			else {
				relop = EQUAL;
				active = false;
			}
		}

		if (data["intv"] != "") {
			if (data["intv"] == 0) interval = REALTIME;
			else if (data["intv"] == 1) interval = TENSEC;
			else if (data["intv"] == 2) interval = TWENTYSEC;
			else if (data["intv"] == 3) interval = THIRTYSEC;
			else if (data["intv"] == 4) interval = ONEMIN;
			else if (data["intv"] == 5) interval = TWOMIN;
			else if (data["intv"] == 6) interval = FIVEMIN;
			else if (data["intv"] == 7) interval = QUARTER;
			else if (data["intv"] == 8) interval = HALF;
			else if (data["intv"] == 9) interval = ONE;
			else if (data["intv"] == 10) interval = TWO;
			else if (data["intv"] == 11) interval = THREE;
			else if (data["intv"] == 12) interval = FOUR;
			else if (data["intv"] == 13) interval = SIX;
			else if (data["intv"] == 14) interval = TWELVE;
			else if (data["intv"] == 15) interval = DAILY;
			else if (data["intv"] == 16) interval = BIDAILY;
			else if (data["intv"] == 17) interval = WEEKLY;
			else if (data["intv"] == 18) interval = BIWEEKLY;
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

void SensorTrigger::reset()
{
	title = "Comparator ";
	title += String(id);

	active = false;
	fired = false;
	
	start_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month, internalRTC.defaulttime.Day, 0, 0, 0);
	end_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month + 1, internalRTC.defaulttime.Day, 0, 0, 0);

	interval = ONEMIN;
	relop = EQUAL;
	threshold = 0;
	tolerance = 0;
}

void TriggerCategory::serializeJSON(Trigger * trigger[TRIGGER_TYPES][TRIGGER_SETS], char * json, size_t maxSize, Scope scope)
{
	DynamicJsonBuffer jsonBuffer;

	JsonObject& container = jsonBuffer.createObject();
	container["obj"] = "TCAT";
	JsonArray& categories = container.createNestedArray("list");

		if (scope == LIST) {
			for (uint8_t i = 0; i < TRIGGER_TYPES; i++) {
				if (trigger[i][0] != NULL) {
					JsonObject& item = jsonBuffer.createObject();
					item["typ"] = static_cast<int>(trigger[i][0]->type);

					if (trigger[i][0]->type == 0) {
						item["tit"] = "Timer";
					}
					else {
						item["tit"] = "Comparator";
					}
					item["src"] = trigger[i][0]->getSource();
					categories.add(item);
				}
			}
		}
		else {
			for (uint8_t i = 0; i < TRIGGER_TYPES; i++) {
				JsonObject& cat = jsonBuffer.createObject();
				cat["src"] = trigger[i][0]->getSource();
				cat["typ"] = static_cast<int>(trigger[i][0]->type);
				JsonArray& trig = cat.createNestedArray("trig");
				for (uint8_t j = 0; j < TRIGGER_SETS; j++) {
					JsonObject& item = jsonBuffer.createObject();
					item["tit"] = trigger[i][j]->getTitle();
					item["act"] = trigger[i][j]->active;
					trig.add(item);
				}
				categories.add(cat);
			}
		}
	
	container.printTo(json, maxSize);
	LOGDEBUG2(F("[Trigger]"), F("serializeJSON()"), F("OK: Serialized Trigger Categories"), "", "", "");
}
