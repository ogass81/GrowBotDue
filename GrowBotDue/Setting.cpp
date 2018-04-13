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

	//Initialize Sensors
	for (uint8_t j = 0; j < SENS_NUM; j++) {
		sensors[j]->reset();
	}

	//Initialize Actionchains
	for (uint8_t j = 0; j < ACTIONCHAINS_NUM; j++) {
		actionchains[j]->reset();
	}

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
	settings["api_secret"] = api_secret;
	settings["cycles"] = sensor_cycles;
	settings.printTo(json, maxSize);
	LOGDEBUG(F("[Setting]"), F("serializeJSON()"), F("OK: Serialized Overall Settings"), String(settings.measureLength()), String(maxSize), "");
}

bool Setting::deserializeJSON(JsonObject & data)
{

	long stored_time = 0, rtc_time = 0;

	if (data.success() == true) {
		if (data["wifi_SSID"].asString() != "") {
			wifi_ssid = data["wifi_SSID"].asString();
			LOGMSG(F("[Setting]"), F("OK: Wifi SSID loaded"), String(wifi_ssid), "", "");
		}
		else {
			LOGMSG(F("[Setting]"), F("ERROR: No Wifi SSID loaded"), "", "", "");
		}

		if (data["wifi_pw"].asString() != "") {
			wifi_pw = data["wifi_pw"].asString();
			LOGMSG(F("[Setting]"), F("OK: Wifi SSID loaded"), String(wifi_pw.substring(0, 3)) + "*****", "", "");
		}
		else {
			LOGMSG(F("[Setting]"), F("ERROR: No Wifi password loaded"), "", "", "");
		}

		if (data["api_secret"].asString() != "") {
			api_secret = data["api_secret"].asString();
			LOGMSG(F("[Setting]"), F("OK: Loaded API secret"), String(api_secret.substring(0, 3)) + "*****", "", "");
		}
		else {
			LOGMSG(F("[Setting]"), F("WARNING: No API secret loaded"), "", "", "");
		}

		if (data["cycles"] != "") {
			//Set RTC
			unsigned long cycles = data["cycles"];
			internalRTC.updateTime(SENS_FRQ_SEC*cycles);

			LOGMSG(F("[Setting]"), F("OK: Updated Time from Settings"), sensor_cycles, String(RealTimeClock::printDate(SENS_FRQ_SEC*sensor_cycles)), String(RealTimeClock::printTime(SENS_FRQ_SEC*sensor_cycles)));
		}
		else {
			LOGMSG(F("[Setting]"), F("WARNING: No Sensor Cycle loaded"), "", "", "");
		}
	}
	else {
		LOGDEBUG(F("[Setting]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize settings"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}
