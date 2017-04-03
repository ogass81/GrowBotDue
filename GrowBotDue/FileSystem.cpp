// 
// 
// 

#include "FileSystem.h"

FileSystem::FileSystem()
{
	
}

void FileSystem::init()
{
	if (!sd.begin(SDCS, SPI_HALF_SPEED)) {
		sd.initErrorHalt();
	}
}

void FileSystem::saveActiveConfig()
{
	this->saveSettings("_CURRENTCONFIG.JSON");
}

void FileSystem::saveBackupConfig()
{
	this->copyFile("_CURRENTCONFIG.JSON", "BACKUPCONFIG.JSON"); 
}

void FileSystem::saveDefaultConfig()
{
	this->saveSettings("DEFAULTCONFIG.JSON");
}

void FileSystem::loadActiveConfig()
{
	this->loadSettings("_CURRENTCONFIG.JSON");
}

void FileSystem::loadBackupConfig()
{
	this->loadSettings("BACKUPCONFIG.JSON");
}

void FileSystem::loadDefaultConfig()
{
	this->loadSettings("DEFAULTCONFIG.JSON");
}

bool FileSystem::saveSettings(const char* filename)
{
	File file;

	StaticJsonBuffer<500> jsonBuffer;
	char json[2500];
	int bytes;
	bool complete;
	bool success = true;
		
	if (file.open(filename, O_CREAT | O_TRUNC | O_WRITE)) {
		JsonObject& root = jsonBuffer.createObject();
		root["type"] = "SETTING";
		root["wifi_SSID"] = wifi_ssid;
		root["wifi_pw"] = wifi_pw;
		root["api_secret"] = api_secret;
		root["second"] = currenttime.current_second;
		root["minute"] = currenttime.current_minute;
		root["hour"] = currenttime.current_hour;
		root["day"] = currenttime.current_day;
		root["month"] = currenttime.current_month;
		root["year"] = currenttime.current_year;
		root.printTo(json);
		
		//One Line One JSON
		file.println(json);

		for (uint8_t i = 0; i < TRIGCAT; i++) {
			for (uint8_t j = 0; j < TRIGNUMBER; j++) {
				trigger[i][j]->serializeJSON(i, j, json, 2500);
				file.println(json);
				LOGDEBUG(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Trigger"), F("Cat | Id"), String(i), String(j));
			}
		}
		for (uint8_t i = 0; i < RULES; i++) {
			rulesets[i]->serializeJSON(i, json, 2500);
			file.println(json);
			LOGDEBUG(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Rule"), F("Id"), String(i), "");
		}
		for (uint8_t i = 0; i < ACTIONCHAINS; i++) {
			actionchains[i]->serializeJSON(i, json, 2500);
			file.println(json);
			LOGDEBUG(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Actionschain"), F("Id"), String(i), "");
		}
		for (uint8_t i = 0; i < SENSNUMBER; i++) {
			sensors[i]->serializeJSON(i, json, 2500);
			file.println(json);
			LOGDEBUG(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Sensor"), F("Id"), String(i), "");
		}
		LOGMSG(F("[FileSystem]"), F("OK: Saved Settings to file:"), String(filename), "", "");
		file.close();
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not write to file:"), String(filename), "", "");
	}
	return success;
}

bool FileSystem::loadSettings(const char* filename)
{
	File file;
	
	String json;
	long stored_time, rtc_time;
	int cat = 0;
	int id = 0;
	int j = 0;
	bool success = true;
	
	rtc_time = currenttime.epochTime();

		if (file.open(filename, O_READ)) {
		
		while (file.available()) {
			//Buffer Needs to be here ...
			StaticJsonBuffer<5000> jsonBuffer;
		
			json = file.readStringUntil('\n');

			JsonObject& node = jsonBuffer.parseObject(json);

			cat = 0;
			id = 0;
			stored_time = 0;

			if (node.success()) {
				if (node["type"] == "SETTING") {
					wifi_ssid = node["wifi_SSID"].asString();
					wifi_pw = node["wifi_pw"].asString();
					api_secret = node["api_secret"].asString();

					if (wifi_ssid != "" && wifi_pw != "") {
						LOGMSG(F("[FileSystem]"), F("OK: Loaded Wifi Settings"), String(wifi_ssid), String(wifi_pw.substring(0, 2)) + "*****","");
					}
					else {
						LOGMSG(F("[FileSystem]"), F("ERROR: No Wifi Settings loaded"), "", "", "");
					}
					if (api_secret != "") {
						LOGMSG(F("[FileSystem]"), F("OK: Loaded API secret"), String(api_secret.substring(0, 2)) + "*****", "", "");
					}
					else {
						LOGMSG(F("[FileSystem]"), F("WARNING: No API secret loaded"), F("> Check Settings / Config"), "", "");
					}
							
					stored_time = CurrentTime::epochTime(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);

					if (stored_time > rtc_time) {
						currenttime.updateRTC(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);
						currenttime.syncTimeObject();
						LOGMSG(F("[FileSystem]"), F("OK: Updated Time from Settings"), String(currenttime.createDate()), String(currenttime.createTime()), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("Info: RTC Time is newer than saved time. No update."), "", "", "");
					}
					sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENSORFRQ;
				}
				else if (node["type"] == "SENSOR") {
					id = (int)node["id"];
					if (id < SENSNUMBER) {
						success = sensors[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Sensor"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Sensor"), F("Id"), String(id), "");
						success = false;
					}
				}
				else if (node["type"] == "TRIGGER") {
					id = (int)node["id"];
					cat = (int)node["cat"];

					if (id <= TRIGNUMBER && cat <= TRIGCAT) {
						success = trigger[cat][id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Trigger"), F("Cat | Id"), String(id), String(cat));
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Trigger"), F("Cat | Id"), String(cat), String(id));
						success = false;
					}
				}
				else if (node["type"] == "RULE") {
					id = (int)node["id"];
					if (id < RULES) {
						success = rulesets[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Ruleset"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Ruleset"), F("Id"), String(id), "");
						success = false;
					}
				}
				else if (node["type"] == "CHAIN") {
					id = (int)node["id"];
					if (id < ACTIONCHAINS) {
						success = actionchains[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Actionchain"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Actionchain"), F("Id"), String(id), "");
						success = false;
					}
				}
			}
			else {
				LOGMSG(F("[FileSystem]"), F("ERROR: Parsing JSON @"), F("Line"), String(j), "");
				success = false;
			}
			j++;
		}
		file.close();
		LOGMSG(F("[FileSystem]"), F("OK: Loaded Settings from file"), String(filename), "Lines", String(j));
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not read from file:"), String(filename), "", "");
		success = false;
	}
	return success;
}

bool FileSystem::copyFile(const char* source, const char* destination)
{
	File backup_file;
	File current_file;

	size_t n;
	uint8_t buf[64];

	short i = 0;
	String output;
	bool success = true;

	if (current_file.open(source, O_READ)) {
		LOGDEBUG(F("[FileSystem]"), F("copyFile()"), F("OK: Source File open"), F("Filename"), String(source), "");
		
		if (backup_file.open(destination, O_CREAT | O_TRUNC | O_WRITE)) {
			LOGDEBUG(F("[FileSystem]"), F("copyFile()"), F("OK: Target File open"), F("Filename"), String(destination), "");

			while ((current_file.read(buf, sizeof(buf))) > 0) {
				backup_file.write(buf, n);
				i++;
			}
			output = String(i * 64);
			current_file.close();
			backup_file.close();
			LOGMSG(F("[FileSystem]"), F("OK: Copied settings to backup file"), String(destination), "Filesize", String(output));
		}
		else {
			LOGMSG(F("[FileSystem]"), F("ERROR: Could not open destination file"), String(destination), "" ,"");
			success = false;
		}
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not open target file"), String(source), "", "");
		success = false;
	}

	return success;
}

void FileSystem::reset()
{
	//Initialize Trigger
	for (int tcategory = 0; tcategory < TRIGCAT; tcategory++) {
		for (int tset = 0; tset < TRIGNUMBER; tset++) {
				trigger[tcategory][tset]->reset();
			}
		}
	//Initialize Rulesets
	for (uint8_t k = 0; k < RULES; k++) {
		rulesets[k]->reset();
	}

	//Initialize Rulesets
	for (uint8_t j = 0; j < SENSNUMBER; j++) {
		sensors[j]->reset();
	}

	//Initialize Rulesets
	for (uint8_t j = 0; j < ACTIONCHAINS; j++) {
		actionchains[j]->reset();
	}

	currenttime.updateRTCdefault();
	sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENSORFRQ;
	
	//Default Values
	
	wifi_ssid = "wgempire";
	wifi_pw = "ert456sdf233sa!!!";
	api_secret = "schnitzel";

	LOGMSG(F("[FileSystem]"), F("OK: Factory Reset to Default Settings (SSID | Password | API_secret)"), String(wifi_ssid), String(wifi_pw), String(api_secret));
}
