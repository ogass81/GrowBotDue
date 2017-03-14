// 
// 
// 

#include "Trigger.h"


Trigger::Trigger() {
	this->reset();
}

bool Trigger::checkState()
{
	return false;
}

void Trigger::incStartHour()
{
	if (this->start_hour < 23) {
		this->start_hour++;
	}
	else this->start_hour = 0;
}

void Trigger::decStartHour()
{
	if (this->start_hour > 0) {
		this->start_hour--;
	}
	else this->start_hour = 23;
}

void Trigger::incStartMinute()
{
	if (this->start_minute < 59) {
		this->start_minute++;
	}
	else this->start_minute = 0;
}

void Trigger::decStartMinute()
{
	if (this->start_minute > 0) {
		this->start_minute--;
	}
	else this->start_minute = 59;
}

void Trigger::incStartDay()
{
	if (this->start_month == 1 || this->start_month == 3 || this->start_month == 5 || this->start_month == 7 || this->start_month == 8 || this->start_month == 10 || this->start_month == 12) {
		if (this->start_day < 31) {
			this->start_day++;
		}
		else this->start_day = 1;
	}
	else if (this->start_month == 4 || this->start_month == 6 || this->start_month == 9 || this->start_month == 11) {
		if (this->start_day < 30) {
			this->start_day++;
		}
		else this->start_day = 1;
	}
	else if (this->start_month == 2 || (this->start_year % 4) == 0) {
		if (this->start_day < 29) {
			this->start_day++;
		}
		else this->start_day = 1;
	}
	else {
		if (this->start_day < 28) {
			this->start_day++;
		}
		else this->start_day = 1;
	}
}

void Trigger::decStartDay()
{
	if (this->start_month == 1 || this->start_month == 3 || this->start_month == 5 || this->start_month == 7 || this->start_month == 8 || this->start_month == 10 || this->start_month == 12) {
		if (this->start_day > 1) {
			this->start_day--;
		}
		else this->start_day = 31;
	}
	else if (this->start_month == 4 || this->start_month == 6 || this->start_month == 9 || this->start_month == 11) {
		if (this->start_day > 1) {
			this->start_day--;
		}
		else this->start_day = 30;
	}
	else if (this->start_month == 2 || (this->start_year % 4) == 0) {
		if (this->start_day > 1) {
			this->start_day--;
		}
		else this->start_day = 29;
	}
	else {
		if (this->start_day > 1) {
			this->start_day--;
		}
		else this->start_day = 28;
	}
}

void Trigger::incStartMonth()
{
	if (this->start_month < 12) {
		this->start_month++;
	}
	else this->start_month = 1;
}

void Trigger::decStartMonth()
{
	if (this->start_month > 1) {
		this->start_month--;
	}
	else this->start_month = 12;
}

void Trigger::incStartYear()
{
	if (this->start_year < 2026) {
		this->start_year++;
	}
	else this->start_year = 2017;
}

void Trigger::decStartYear()
{
	if (this->start_year > 2017) {
		this->start_year--;
	}
	else this->start_year = 2026;
}

void Trigger::incEndDay()
{
	if (this->end_month == 1 || this->end_month == 3 || this->end_month == 5 || this->end_month == 7 || this->end_month == 8 || this->end_month == 10 || this->end_month == 12) {
		if (this->end_day < 31) {
			this->end_day++;
		}
		else this->end_day = 1;
	}
	else if (this->end_month == 4 || this->end_month == 6 || this->end_month == 9 || this->end_month == 11) {
		if (this->end_day < 30) {
			this->end_day++;
		}
		else this->end_day = 1;
	}
	else if (this->end_month == 2 || (this->end_year % 4) == 0) {
		if (this->end_day < 29) {
			this->end_day++;
		}
		else this->end_day = 1;
	}
	else {
		if (this->end_day < 28) {
			this->end_day++;
		}
		else this->end_day = 1;
	}
}

void Trigger::decEndDay()
{
	if (this->end_month == 1 || this->end_month == 3 || this->end_month == 5 || this->end_month == 7 || this->end_month == 8 || this->end_month == 10 || this->end_month == 12) {
		if (this->end_day > 1) {
			this->end_day--;
		}
		else this->end_day = 31;
	}
	else if (this->end_month == 4 || this->end_month == 6 || this->end_month == 9 || this->end_month == 11) {
		if (this->end_day > 1) {
			this->end_day--;
		}
		else this->end_day = 30;
	}
	else if (this->end_month == 2 || (this->end_year % 4) == 0) {
		if (this->end_day > 1) {
			this->end_day--;
		}
		else this->end_day = 29;
	}
	else {
		if (this->end_day > 1) {
			this->end_day--;
		}
		else this->end_day = 28;
	}
}

void Trigger::incEndMonth()
{
	if (this->end_month < 12) {
		this->end_month++;
	}
	else this->end_month = 1;
}

void Trigger::decEndMonth()
{
	if (this->end_month > 1) {
		this->end_month--;
	}
	else this->end_month = 12;
}

void Trigger::incEndYear()
{
	if (this->end_year < 2027) {
		this->end_year++;
	}
	else this->end_year = 2017;
}

void Trigger::decEndYear()
{
	if (this->end_year > 2017) {
		this->end_year--;
	}
	else this->end_year = 2027;
}

void Trigger::incInterval()
{
	switch (this->interval) {

	case REALTIME:
		this->interval = TENSEC;
		break;
	case TENSEC:
		this->interval = TWENTYSEC;
		break;
	case TWENTYSEC:
		this->interval = THIRTYSEC;
		break;
	case THIRTYSEC:
		this->interval = ONEMIN;
		break;
	case ONEMIN:
		this->interval = TWOMIN;
		break;
	case TWOMIN:
		this->interval = FIVEMIN;
		break;
	case FIVEMIN:
		this->interval = QUARTER;
		break;
	case QUARTER:
		this->interval = HALF;
		break;
	case HALF:
		this->interval = ONE;
		break;
	case ONE:
		this->interval = TWO;
		break;
	case TWO:
		this->interval = THREE;
		break;
	case THREE:
		this->interval = FOUR;
		break;
	case FOUR:
		this->interval = SIX;
		break;
	case SIX:
		this->interval = TWELVE;
		break;
	case TWELVE:
		this->interval = DAILY;
		break;
	case DAILY:
		this->interval = BIDAILY;
		break;
	case BIDAILY:
		this->interval = WEEKLY;
		break;
	case WEEKLY:
		this->interval = BIWEEKLY;
		break;
	case BIWEEKLY:
		this->interval = REALTIME;
		break;
	}
}

void Trigger::decInterval()
{
	switch (this->interval) {
	case REALTIME:
		this->interval = BIWEEKLY;
		break;
	case TENSEC:
		this->interval = REALTIME;
		break;
	case TWENTYSEC:
		this->interval = TENSEC;
		break;
	case THIRTYSEC:
		this->interval = TWENTYSEC;
		break;
	case ONEMIN:
		this->interval = THIRTYSEC;
		break;	
	case TWOMIN:
		this->interval = ONEMIN;
		break;
	case FIVEMIN:
		this->interval = TWOMIN;
		break;
	case QUARTER:
		this->interval = FIVEMIN;
		break;
	case HALF:
		this->interval = QUARTER;
		break;
	case ONE:
		this->interval = HALF;
		break;
	case TWO:
		this->interval = ONE;
		break;
	case THREE:
		this->interval = TWO;
		break;
	case FOUR:
		this->interval = THREE;
		break;
	case SIX:
		this->interval = FOUR;
		break;
	case TWELVE:
		this->interval = SIX;
		break;
	case DAILY:
		this->interval = TWELVE;
		break;
	case BIDAILY:
		this->interval = DAILY;
		break;
	case WEEKLY:
		this->interval = BIDAILY;
		break;
	case BIWEEKLY:
		this->interval = WEEKLY;
		break;
	}
}

void Trigger::incRelOp()
{
	switch (this->relop) {

	case GREATER:
		this->relop = SMALLER;
		break;
	case SMALLER:
		this->relop = EQUAL;
		break;
	case EQUAL:
		this->relop = GREATER;
		break;
	}
}

void Trigger::decRelOp()
{
	switch (this->relop) {

	case GREATER:
		this->relop = EQUAL;
		break;
	case SMALLER:
		this->relop = GREATER;
		break;
	case EQUAL:
		this->relop = SMALLER;
		break;
	}
}

void Trigger::incThresh()
{
	this->threshold++;
}

void Trigger::decThresh()
{
	this->threshold--;
}

void Trigger::changeActive()
{
	if (this->active == true) this->active = false;
	else this->active = true;
}

String Trigger::getTitle()
{

	return String();
}

String Trigger::getActive()
{
	if (this->active == true) return String("ON");
	else return String("OFF");
}

String Trigger::getStartDay()
{
	return String(this->start_day);
}

String Trigger::getStartMonth()
{
	return String(this->start_month);
}

String Trigger::getStartYear()
{
	return String(this->start_year);
}

String Trigger::getStartHour()
{
	return String(this->start_hour);
}

String Trigger::getStartMinute()
{
	return String(this->start_minute);
}

String Trigger::getEndDay()
{
	return String(this->end_day);
}

String Trigger::getEndMonth()
{
	return String(this->end_month);
}

String Trigger::getEndYear()
{
	return String(this->end_year);
}

String Trigger::getInterval()
{
	switch (this->interval) {

	case REALTIME:
		return String("RT");
		break;
	case TENSEC:
		return String("10sec");
		break;
	case TWENTYSEC:
		return String("20sec");
		break;
	case THIRTYSEC:
		return String("30sec");
		break;
	case ONEMIN:
		return String("1 min");
		break;
	case TWOMIN:
		return String("2 min");
		break;
	case FIVEMIN:
		return String("5 min");
		break;
	case QUARTER:
		return String("15 min");
		break;
	case HALF:
		return String("30 min");
		break;
	case ONE:
		return String("1h");
		break;
	case TWO:
		return String("2h");
		break;
	case THREE:
		return String("3h");
		break;
	case FOUR:
		return String("4h");
		break;
	case SIX:
		return String("6h");
		break;
	case TWELVE:
		return String("12h");
		break;
	case DAILY:
		return String("daily");
		break;
	case BIDAILY:
		return String("bi-daily");
		break;
	case WEEKLY:
		return String("weekly");
		break;
	case BIWEEKLY:
		return String("bi-weekly");
		break;
	}
}

String Trigger::getRelOp()
{
	if (this->relop == SMALLER) return String("<");
	else if (this->relop == EQUAL) return String("=");
	else if (this->relop == GREATER) return String(">");
	else return ("ND");
}

String Trigger::getThresh()
{
	return String(this->threshold);
}

void Trigger::reset()
{
	this->active = false;

	this->start_day = currenttime.current_day;
	this->start_month = currenttime.current_month;
	this->start_hour = currenttime.current_hour;
	this->start_minute = currenttime.current_minute;
	this->start_year = currenttime.current_year;

	this->end_day = currenttime.current_day;
	this->end_month = currenttime.current_month;
	this->end_hour = currenttime.current_hour;
	this->end_minute = currenttime.current_minute;
	this->end_year = this->start_year + 1;

	this->interval = TWOMIN;
	this->relop = EQUAL;
	this->threshold = 0;
}

void Trigger::serializeJSON(uint8_t cat, uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& trigger = jsonBuffer.createObject();
	
	trigger["type"] = "TRIGGER";
	trigger["cat"] = cat;
	trigger["id"] = id;

	trigger["active"] = this->active;
	trigger["start_minute"] = this->start_minute;
	trigger["start_hour"] = this->start_hour;
	trigger["start_day"] = this->start_day;
	trigger["start_month"] = this->start_month;
	trigger["start_year"] = this->start_year;
	trigger["end_minute"] = this->end_minute;
	trigger["end_hour"] = this->end_hour;
	trigger["end_day"] = this->end_day;
	trigger["end_month"] = this->end_month;
	trigger["end_year"] = this->end_year;
	trigger["relop"] = static_cast<int>(this->relop);
	trigger["threshold"] = this->threshold;
	trigger["interval"] = static_cast<int>(this->interval);

	trigger.printTo(json, maxSize);
}

bool Trigger::deserializeJSON(JsonObject& data)
{
	if (data.success() == true) {
		this->active = data["active"];
		this->start_minute = data["start_minute"];
		this->start_hour = data["start_hour"];
		this->start_day = data["start_day"];
		this->start_month = data["start_month"];
		this->start_year = data["start_year"];
		this->end_minute = data["end_minute"];
		this->end_hour = data["end_hour"];
		this->end_day = data["end_day"];
		this->end_month = data["end_month"];
		this->end_year = data["end_year"];
		this->threshold = data["threshold"];

		if (data["relop"] == 0) this->relop = SMALLER;
		else if (data["relop"] == 1) this->relop = EQUAL;
		else if (data["relop"] == 2) this->relop = GREATER;
		else {
			this->relop = EQUAL;
			this->active = false;
		}

		if (data["interval"] == 0) this->interval = REALTIME;
		else if (data["interval"] == 1) this->interval = TENSEC;
		else if (data["interval"] == 2) this->interval = TWENTYSEC;
		else if (data["interval"] == 3) this->interval = THIRTYSEC;
		else if (data["interval"] == 4) this->interval = ONEMIN;
		else if (data["interval"] == 5) this->interval = TWOMIN;
		else if (data["interval"] == 6) this->interval = FIVEMIN;
		else if (data["interval"] == 7) this->interval = QUARTER;
		else if (data["interval"] == 8) this->interval = HALF;
		else if (data["interval"] == 9) this->interval = ONE;
		else if (data["interval"] == 10) this->interval = TWO;
		else if (data["interval"] == 11) this->interval = THREE;
		else if (data["interval"] == 12) this->interval = FOUR;
		else if (data["interval"] == 13) this->interval = SIX;
		else if (data["interval"] == 14) this->interval = TWELVE;
		else if (data["interval"] == 15) this->interval = DAILY;
		else if (data["interval"] == 16) this->interval = BIDAILY;
		else if (data["interval"] == 17) this->interval = WEEKLY;
		else if (data["interval"] == 18) this->interval = BIWEEKLY;
		else {
			this->interval = FIVEMIN;
			this->active = false;
		}
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
	long epoch_current =  0;
	long epoch_start = 0;
	long epoch_end = 0;
	
	bool state = false;
	
	epoch_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, currenttime.current_second);
	epoch_start = CurrentTime::epochTime(this->start_year, this->start_month, this->start_day, this->start_hour, this->start_minute, 0);
	epoch_end = CurrentTime::epochTime(this->end_year, this->end_month, this->end_day, this->end_hour, this->end_minute, 0);

	if (active == true) {
		Serial.println("Trigger active");
		if (epoch_current > epoch_start && epoch_current < epoch_end) {
			Serial.println("Current Date > Start Date");
			if (this->interval == REALTIME) state = true;
			else if (this->interval == TENSEC && (sensor_cycles % (10 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == TWENTYSEC && (sensor_cycles % (20 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == THIRTYSEC && (sensor_cycles % (30 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == ONEMIN && (sensor_cycles % (60 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == TWOMIN && (sensor_cycles % (120 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == FIVEMIN && (sensor_cycles % (300 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == QUARTER && (sensor_cycles % (900 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == HALF && (sensor_cycles % (1800 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == ONE && (sensor_cycles % (3600 / CLOCKFRQ)) == 0)  state = true;
			else if (this->interval == TWO && (sensor_cycles % (7200 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == THREE && (sensor_cycles % (10800 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == FOUR && (sensor_cycles % (14400 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == SIX && (sensor_cycles % (21600 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == TWELVE && (sensor_cycles % (43200 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == DAILY && (sensor_cycles % (86400 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == BIDAILY && (sensor_cycles % (172800 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == WEEKLY && (sensor_cycles % (604800 / CLOCKFRQ)) == 0) state = true;
			else if (this->interval == BIWEEKLY && (sensor_cycles % (1209600 / CLOCKFRQ)) == 0) state = true;
		}
	}
	return state;
}

String TimeTrigger::getTitle()
{
	String name;

	name = String(this->id) + ':';
	name += currenttime.getTitle();
	name += '(';
	name += (String)this->start_hour;
	name += ':';
	name += (String)this->start_minute;
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
	long epoch_current, epoch_start;
	short current_value;

	epoch_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, currenttime.current_second);
	epoch_start = CurrentTime::epochTime(this->start_year, this->start_month, this->start_day, this->start_hour, this->start_minute, 0);
	
	if (this->active == true) {
		if (epoch_current > epoch_start) {
			
			if (this->interval == REALTIME) current_value = sens_ptr->getLastValue();
			else if (this->interval == TENSEC && (sensor_cycles % (10 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTenSecAvg();
			else if (this->interval == TWENTYSEC && (sensor_cycles % (20 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwentySecAvg();
			else if (this->interval == THIRTYSEC && (sensor_cycles % (30 / CLOCKFRQ)) == 0) current_value = sens_ptr->getThirtySecAvg();
			else if (this->interval == ONEMIN && (sensor_cycles % (60 / CLOCKFRQ)) == 0) current_value = sens_ptr->getOneMinAvg();
			else if (this->interval == TWOMIN && (sensor_cycles % (120 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwoMinAvg();
			else if (this->interval == FIVEMIN && (sensor_cycles % (300 / CLOCKFRQ)) == 0) current_value = sens_ptr->getFiveMinAvg();
			else if (this->interval == QUARTER && (sensor_cycles % (900 / CLOCKFRQ)) == 0) current_value = sens_ptr->getQuarterAvg();
			else if (this->interval == HALF && (sensor_cycles % (1800 / CLOCKFRQ)) == 0) current_value = sens_ptr->getHalfAvg();
			else if (this->interval == ONE && (sensor_cycles % (3600 / CLOCKFRQ)) == 0)  current_value = sens_ptr->getHourAvg();
			else if (this->interval == TWO && (sensor_cycles % (7200 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwoHourAvg();
			else if (this->interval == THREE && (sensor_cycles % (10800 / CLOCKFRQ)) == 0) current_value = sens_ptr->getThreeHourAvg();
			else if (this->interval == FOUR && (sensor_cycles % (14400 / CLOCKFRQ)) == 0) current_value = sens_ptr->getFourHourAvg();
			else if (this->interval == SIX && (sensor_cycles % (21600 / CLOCKFRQ)) == 0) current_value = sens_ptr->getSixHourAvg();
			else if (this->interval == TWELVE && (sensor_cycles % (43200 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwelveHourAvg();
			else if (this->interval == DAILY && (sensor_cycles % (86400 / CLOCKFRQ)) == 0) current_value = sens_ptr->getDayAvg();
			else if (this->interval == BIDAILY && (sensor_cycles % (172800 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwoDayAvg();
			else if (this->interval == WEEKLY && (sensor_cycles % (604800 / CLOCKFRQ)) == 0) current_value = sens_ptr->getWeekAvg();
			else if (this->interval == BIWEEKLY && (sensor_cycles % (1209600 / CLOCKFRQ)) == 0) current_value = sens_ptr->getTwoWeekAvg();
			else return false;
		}
		else return false;

		Serial.print("Sensor:");
		Serial.println(current_value);
		Serial.print("Bool:");
		Serial.println(this->relop);
		Serial.print("Threshold:");
		Serial.println(this->threshold);

		if (this->relop == EQUAL && current_value == this->threshold) return true;
		else if (this->relop == GREATER && current_value > this->threshold) return true;
		else if (this->relop == SMALLER && current_value < this->threshold) return true;
		else return false;
	}
	else return false;
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