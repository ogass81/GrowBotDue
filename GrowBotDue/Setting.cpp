// 
// 
// 

#include "Setting.h"

void Setting::reset()
{
	//Initialize Trigger
	for (int tcategory = 0; tcategory < TRIGGER_TYPES; tcategory++) {
		for (int tset = 0; tset < TRIGGER_SETS; tset++) {
			trigger[tcategory][tset]->reset();
		}
	}
	//Initialize Rulesets
	for (uint8_t k = 0; k < RULESETS_NUM; k++) {
		rulesets[k]->reset();
	}

	//Initialize Rulesets
	for (uint8_t j = 0; j < SENS_NUM; j++) {
		sensors[j]->reset();
	}

	//Initialize Rulesets
	for (uint8_t j = 0; j < ACTIONCHAINS_NUM; j++) {
		actionchains[j]->reset();
	}

	currenttime.updateRTCdefault();
	sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENS_FRQ_SEC;

	//Default Values

	wifi_ssid = "wgempire";
	wifi_pw = "ert456sdf233sa!!!";
	api_secret = "schnitzel";

	LOGMSG(F("[FileSystem]"), F("OK: Factory Reset to Default Settings (SSID | Password | API_secret)"), String(wifi_ssid), String(wifi_pw), String(api_secret));
}

void Setting::serializeJSON(char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& settings = jsonBuffer.createObject();
	settings["obj"] = "SETTING";
	//Constants
	settings["firm_version"] = GROWBOT_FIRMWARE;
	settings["firm_date"] = __DATE__;
	settings["firm_time"] = __TIME__;
	settings["actions_num"] = ACTIONS_NUM;
	settings["actionschains_num"] = ACTIONCHAINS_NUM;
	settings["actionschains_length"] = ACTIONCHAIN_LENGTH;
	settings["rulesets_num"] = RULESETS_NUM;
	settings["trigger_sets"] = TRIGGER_SETS;
	settings["trigger_types"] = TRIGGER_TYPES;
	settings["sensor_num"] = SENS_NUM;
	settings["task_queue_length"] = TASK_QUEUE_LENGTH;
	settings["actionchain_task_maxduration"] = ACTIONCHAIN_TASK_MAXDURATION;
	settings["task_parallel_sec"] = TASK_PARALLEL_SEC;
	settings["rc_sockets_num"] = RC_SOCKETS;
	settings["rc_signals_num"] = RC_SIGNALS;
	
	//Variable Settings	
	settings["wifi_SSID"] = wifi_ssid;
	settings["wifi_pw"] = wifi_pw;
	LOGDEBUG(F("[Setting]"), F("serializeJSON()"), F("OK: Serialized Overall Settings"), String(api_secret), "", "");
	settings["api_secret"] = api_secret;
	settings["second"] = currenttime.current_second;
	settings["minute"] = currenttime.current_minute;
	settings["hour"] = currenttime.current_hour;
	settings["day"] = currenttime.current_day;
	settings["month"] = currenttime.current_month;
	settings["year"] = currenttime.current_year;
	settings.printTo(json, maxSize);
	LOGDEBUG(F("[Setting]"), F("serializeJSON()"), F("OK: Serialized Overall Settings"), String(settings.measureLength()), String(maxSize), "");
}

bool Setting::deserializeJSON(JsonObject & data)
{

	long stored_time = 0, rtc_time = 0;
	rtc_time = currenttime.epochTime();

	if (data.success() == true) {
		if(data["wifi_SSID"].asString() != "") wifi_ssid = data["wifi_SSID"].asString();
		if (data["wifi_pw"].asString() != "") wifi_pw = data["wifi_pw"].asString();
		
		if (wifi_ssid != "" && wifi_pw != "") {
			LOGMSG(F("[Setting]"), F("OK: Loaded Wifi Settings"), String(wifi_ssid), String(wifi_pw.substring(0, 2)) + "*****", "");
		}
		else {
			LOGMSG(F("[Setting]"), F("ERROR: No Wifi Settings loaded"), "", "", "");
		}
	
		if (data["api_secret"].asString() != "") api_secret = data["api_secret"].asString();

		if (api_secret != "") {
			LOGMSG(F("[Setting]"), F("OK: Loaded API secret"), String(api_secret.substring(0, 2)) + "*****", "", "");
		}
		else {
			LOGMSG(F("[Setting]"), F("WARNING: No API secret loaded"), F("> Check Settings / Config"), "", "");
		}

		if (data["year"] != "" && data["month"] != "" && data["day"] != "" && data["hour"] != "" && data["minute"] != "" && data["second"] != "") {

			stored_time = CurrentTime::epochTime(data["year"], data["month"], data["day"], data["hour"], data["minute"], data["second"]);

			if (stored_time > rtc_time) {
				currenttime.updateRTC(data["year"], data["month"], data["day"], data["hour"], data["minute"], data["second"]);
				currenttime.syncTimeObject();
				LOGMSG(F("[Setting]"), F("OK: Updated Time from Settings"), String(currenttime.createDate()), String(currenttime.createTime()), "");
			}
			else {
				LOGDEBUG(F("[Setting]"), F("loadSettings()"), F("Info: RTC Time is newer than saved time. No update."), "", "", "");
			}
			sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENS_FRQ_SEC;
		}
	}
	else {
		LOGDEBUG(F("[Setting]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize settings"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}

void Setting::serializeConstantsJSON(char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& settings = jsonBuffer.createObject();
	settings["firm_version"] = GROWBOT_FIRMWARE;
	settings["firm_date"] = __DATE__;
	settings["firm_time"] = __TIME__;
	settings["actions_num"] = ACTIONS_NUM;
	settings["actionschains_num"] = ACTIONCHAINS_NUM;
	settings["actionschains_length"] = ACTIONCHAIN_LENGTH;
	settings["rulesets_num"] = RULESETS_NUM;
	settings["trigger_sets"] = TRIGGER_SETS;
	settings["trigger_types"] = TRIGGER_TYPES;
	settings["sensor_num"] = SENS_NUM;
	settings["task_queue_length"] = TASK_QUEUE_LENGTH;
	settings["actionchain_task_maxduration"] = ACTIONCHAIN_TASK_MAXDURATION;
	settings["task_parallel_sec"] = TASK_PARALLEL_SEC;
	settings["rc_sockets_num"] = RC_SOCKETS;
	settings["rc_signals_num"] = RC_SIGNALS;
	
	settings.printTo(json, maxSize);
	LOGDEBUG(F("[Setting]"), F("serializeJSONConstants()"), F("OK: Serialized Constants"), String(settings.measureLength()), String(maxSize), "");
}
