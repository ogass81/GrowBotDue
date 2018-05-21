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
		trigger["val"] = threshold;
		trigger["intv"] = static_cast<int>(interval);
	}

	trigger.printTo(json, maxSize);
	LOGDEBUG2(F("[Trigger]"), F("serializeJSON()"), F("OK: Serialized Members for Trigger"), String(getTitle()), String(trigger.measureLength()), String(maxSize));
}

bool TimeTrigger::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		if (data["tit"] != "") title = data["tit"].asString();
		if (data["act"] != "") active = data["act"];
		if (data["start_time"] != "") start_time = data["start_time"];
		if (data["end_time"] != "") end_time = data["end_time"];	
		if (data["val"] != "") threshold = data["val"];

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

	start_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month, internalRTC.defaulttime.Day, 0, 0, 0);
	end_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month + 1, internalRTC.defaulttime.Day, 0, 0, 0);

	interval = ONEMIN;
	relop = EQUAL;
	threshold = 0;
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
	sensor_start = start_time + internalRTC.timezone_offset / SENS_FRQ_SEC;
	sensor_end = end_time + internalRTC.timezone_offset / SENS_FRQ_SEC;

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

	if (active == true) state = sens_ptr->compareWithValue(relop, interval, threshold);
	else state = false;

	LOGMSG(F("[Trigger]"), String("OK: Sensor Trigger Checked " + getTitle()), threshold, interval, state);
	return state;
}

void SensorTrigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize, Scope scope)
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
	trigger["intv"] = static_cast<int>(interval);
	trigger["relop"] = static_cast<int>(relop);
	trigger["val"] = threshold;
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

		if (data["relop"] != "") {
			if (data["relop"] == 0) relop = SMALLER;
			else if (data["relop"] == 1) relop = EQUAL;
			else if (data["relop"] == 2) relop = GREATER;
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
	
	start_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month, internalRTC.defaulttime.Day, 0, 0, 0);
	end_time = RealTimeClock::toEpochTime(internalRTC.defaulttime.Year, internalRTC.defaulttime.Month + 1, internalRTC.defaulttime.Day, 0, 0, 0);

	interval = ONEMIN;
	relop = EQUAL;
	threshold = 0;
}

void TriggerCategory::serializeJSON(Trigger * trigger[TRIGGER_TYPES][TRIGGER_SETS], char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<5000> jsonBuffer;

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
