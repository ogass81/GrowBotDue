// 
// 
// 

#include "Trigger.h"


Trigger::Trigger() {
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
	this->end_year = currenttime.current_year+1;

	this->interval = FIVEMIN;
	this->relop = EQUAL;
	this->threshold = 0;
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
		this->interval = ONEMIN;
		break;
	}
}

void Trigger::decInterval()
{
	switch (this->interval) {
	
	case ONEMIN:
		this->interval = BIWEEKLY;
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

TimeTrigger::TimeTrigger(int id)
	: Trigger()
{
	this->id = id;
}

bool TimeTrigger::checkState()
{
	int epoch_current =  0;
	int epoch_start = 0;
	int epoch_end = 0;
	
	bool state = false;
	
	epoch_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0);
	epoch_start = CurrentTime::epochTime(this->start_year, this->start_month, this->start_day, this->start_hour, this->start_minute, 0);
	epoch_end = CurrentTime::epochTime(this->end_year, this->end_month, this->end_day, this->end_hour, this->end_minute, 0);

	if (active == true) {
		if (epoch_current > epoch_start && epoch_current < epoch_end) {
			if (this->interval == ONEMIN) state = true;
			else if (this->interval == TWOMIN && ((epoch_current - epoch_start) % 2 == 0)) state = true;
			else if (this->interval == FIVEMIN && ((epoch_current - epoch_start) % 5 == 0)) state = true;
			else if (this->interval == QUARTER && ((epoch_current - epoch_start) % 15 == 0)) state = true;
			else if (this->interval == HALF && ((epoch_current - epoch_start) % 30 == 0)) state = true;
			else if (this->interval == ONE && ((epoch_current - epoch_start) % 60 == 0)) state = true;
			else if (this->interval == TWO && ((epoch_current - epoch_start) % 120 == 0)) state = true;
			else if (this->interval == THREE && ((epoch_current - epoch_start) % 180 == 0)) state = true;
			else if (this->interval == FOUR && ((epoch_current - epoch_start) % 240 == 0)) state = true;
			else if (this->interval == SIX && ((epoch_current - epoch_start) % 360 == 0)) state = true;
			else if (this->interval == TWELVE && ((epoch_current - epoch_start) % 720 == 0)) state = true;
			else if (this->interval == DAILY && ((epoch_current - epoch_start) % 1440 == 0)) state = true;
			else if (this->interval == BIDAILY && ((epoch_current - epoch_start) % 2880 == 0)) state = true;
			else if (this->interval == WEEKLY && ((epoch_current - epoch_start) % 10080 == 0)) state = true;
			else if (this->interval == BIWEEKLY && ((epoch_current - epoch_start) % 20160 == 0)) state = true;
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
	int epoch_current, epoch_start, current_value;

	epoch_current = CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0);
	epoch_start = CurrentTime::epochTime(this->start_year, this->start_month, this->start_day, this->start_hour, this->start_minute, 0);
	
	if (this->active == true) {
		if (epoch_current > epoch_start) {
			Serial.print("Differenz:");
			Serial.println(long(epoch_current-epoch_start));
			
			if (this->interval == ONEMIN) current_value = sens_ptr->getOneMinAvg();
			else if (this->interval == TWOMIN && ((epoch_current - epoch_start) % 2 == 0)) current_value = sens_ptr->getTwoMinAvg();
			else if (this->interval == FIVEMIN && ((epoch_current - epoch_start) % 5 == 0)) current_value = sens_ptr->getFiveMinAvg();
			else if (this->interval == QUARTER && ((epoch_current - epoch_start) % 5 == 0)) current_value = sens_ptr->getQuarterAvg();
			else if (this->interval == HALF && ((epoch_current - epoch_start) % 30 == 0)) current_value = sens_ptr->getHalfAvg();
			else if (this->interval == ONE && ((epoch_current - epoch_start) % 60 == 0))  current_value = sens_ptr->getHourAvg();
			else if (this->interval == TWO && ((epoch_current - epoch_start) % 120 == 0)) current_value = sens_ptr->getTwoHourAvg();
			else if (this->interval == THREE && ((epoch_current - epoch_start) % 180 == 0)) current_value = sens_ptr->getThreeHourAvg();
			else if (this->interval == FOUR && ((epoch_current - epoch_start) % 240 == 0)) current_value = sens_ptr->getFourHourAvg();
			else if (this->interval == SIX && ((epoch_current - epoch_start) % 360 == 0)) current_value = sens_ptr->getSixHourAvg();
			else if (this->interval == TWELVE && ((epoch_current - epoch_start) % 720 == 0)) current_value = sens_ptr->getTwelveHourAvg();
			else if (this->interval == DAILY && ((epoch_current - epoch_start) % 1440 == 0)) current_value = sens_ptr->getDayAvg();
			else if (this->interval == BIDAILY && ((epoch_current - epoch_start) % 2880 == 0)) current_value = sens_ptr->getTwoDayAvg();
			else if (this->interval == WEEKLY && ((epoch_current - epoch_start) % 10080 == 0)) current_value = sens_ptr->getWeekAvg();
			else if (this->interval == BIWEEKLY && ((epoch_current - epoch_start) % 20160 == 0)) current_value = sens_ptr->getTwoWeekAvg();
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