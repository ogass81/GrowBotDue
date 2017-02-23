// 
// 
// 

#include "DataStore.h"

void DataStore::serialize()
{
	StaticJsonBuffer<5000> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();



	root["year"] = currenttime.getYear();
	root["month"] = currenttime.getMonth();
	root["day"] = currenttime.getDay();
	root["hour"] = currenttime.getHours();
	root["minute"] = currenttime.getMinutes();
	root["cycle"] = sensor_cycles;


	JsonObject& trig = root.createNestedObject("Trigger");
	for (uint8_t i = 0; i < TRIGCAT; i++) {
		JsonObject& cat = trig.createNestedObject(String(i));
		for (uint8_t j = 0; j < TRIGNUMBER; j++) {
			JsonObject& number = cat.createNestedObject(String(j));
			number["active"] = trigger[i][j]->active;
			number["start_minute"] = trigger[i][j]->start_minute;
			number["start_hour"] = trigger[i][j]->start_hour;
			number["start_day"] = trigger[i][j]->start_day;
			number["start_month"] = trigger[i][j]->start_month;
			number["start_year"] = trigger[i][j]->start_year;
			number["end_minute"] = trigger[i][j]->end_minute;
			number["end_hour"] = trigger[i][j]->end_hour;
			number["end_day"] = trigger[i][j]->end_day;
			number["end_month"] = trigger[i][j]->end_month;
			number["end_year"] = trigger[i][j]->end_year;
			number["relop"] = trigger[i][j]->relop;
			number["threshold"] = trigger[i][j]->threshold;
			number["interval"] = trigger[i][j]->interval;
		}
	}

	JsonObject& rules= root.createNestedObject("Rules");
	for (uint8_t i = 0; i < RULES; i++) {
		JsonObject& set = rules.createNestedObject(String(i));
		set["active"] = rulesets[i]->active;
		set["triggerset1_ptr"] = rulesets[i]->triggerset1_ptr;
		set["triggercat1_ptr"] = rulesets[i]->triggercat1_ptr;
		set["triggerset2_ptr"] = rulesets[i]->triggerset2_ptr;
		set["triggercat2_ptr"] = rulesets[i]->triggercat2_ptr;
		set["triggerset3_ptr"] = rulesets[i]->triggerset3_ptr;
		set["triggercat3_ptr"] = rulesets[i]->triggercat3_ptr;
		set["action1_ptr"] = rulesets[i]->action1_ptr;
		set["action2_ptr"] = rulesets[i]->action2_ptr;
	}

	JsonObject& sens = root.createNestedObject("Sensors");
	for (uint8_t i = 0; i < SENSNUMBER; i++) {
		JsonObject& senunit = sens.createNestedObject("Sensors");
		senunit["minute_ptr"] = sensors[i]->minute_ptr;
		senunit["hour_ptr"] = sensors[i]->hour_ptr;
		senunit["day_ptr"] = sensors[i]->day_ptr;
		senunit["month_ptr"] = sensors[i]->month_ptr;
		senunit["year_ptr"] = sensors[i]->year_ptr;

		JsonArray& minutes = senunit.createNestedArray("minute_values");
		for (uint8_t j = 0; j < NUMMINUTE; j++) minutes.add(sensors[i]->minute_values[j]);
		JsonArray& hours = senunit.createNestedArray("hour_values");
		for (uint8_t j = 0; j < NUMHOUR; j++) hours.add(sensors[i]->hour_values[j]);
		JsonArray& days = senunit.createNestedArray("day_values");
		for (uint8_t j = 0; j < NUMDAY; j++) days.add(sensors[i]->day_values[j]);
		JsonArray& month = senunit.createNestedArray("month_values");
		for (uint8_t j = 0; j < NUMMONTH; j++) month.add(sensors[i]->month_values[j]);
		JsonArray& year = senunit.createNestedArray("year_values");
		for (uint8_t j = 0; j < NUMYEAR; j++) year.add(sensors[i]->year_values[j]);
	}
	
	root.prettyPrintTo(Serial);
}

void DataStore::deserialize()
{
}
