// 
// 
// 

#include "Trigger.h"

Trigger::Trigger() {
	this->active = false;

	this->start_day = 1;
	this->start_month = 1;
	this->start_hour = 12;
	this->start_minute = 0;
	this->start_year = 2017;

	this->end_day = 1;
	this->end_month = 1;
	this->end_hour = 0;
	this->end_minute = 0;
	this->end_year = 2018;

	this->interval = DAILY;
	this->boolop = EQUAL;
	this->treshhold = 0;
}

void Trigger::setReference(Sensor * senspt)
{
}

void Trigger::updateAverage()
{
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
		this->interval = QUARTER;
		break;
	}
}

void Trigger::decInterval()
{
	switch (this->interval) {

	case QUARTER:
		this->interval = BIWEEKLY;
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

void Trigger::incBoolOp()
{
	switch (this->boolop) {

	case GREATER:
		this->boolop = SMALLER;
		break;
	case SMALLER:
		this->boolop = EQUAL;
		break;
	case EQUAL:
		this->boolop = GREATER;
		break;
	}
}

void Trigger::decBoolOp()
{
	switch (this->boolop) {

	case GREATER:
		this->boolop = EQUAL;
		break;
	case SMALLER:
		this->boolop = GREATER;
		break;
	case EQUAL:
		this->boolop = SMALLER;
		break;
	}
}

void Trigger::incThresh()
{
	this->treshhold++;
}

void Trigger::decThresh()
{
	this->treshhold--;
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

String Trigger::getBoolOp()
{
	if (this->boolop == SMALLER) return String("<");
	else if (this->boolop == EQUAL) return String("=");
	else if (this->boolop == GREATER) return String(">");
	else return ("ND");
}

String Trigger::getThresh()
{
	return String(this->treshhold);
}

TimeTrigger::TimeTrigger(int id, CurrentTime *timeobject)
	: Trigger()
{
	this->id = id;
	this->currenttime = timeobject;
}

bool TimeTrigger::checkState()
{
	return false;
}

String TimeTrigger::getTitle()
{
	String name;

	name = String(this->id) + ':';
	name += currenttime->getTitle();
	return String(name);
}


SensorTrigger::SensorTrigger(int id, Sensor *ptr)
	: Trigger()
{
	this->id = id;
	this->sens_ptr = ptr;
}


void SensorTrigger::updateAverage()
{
}

bool SensorTrigger::checkState()
{
	return false;
}

String SensorTrigger::getTitle()
{
	String name;

	name = String(this->id) + ':';
	name += sens_ptr->getTitle();

	return String(name);
}