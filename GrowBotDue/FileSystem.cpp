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
	this->saveSettings("DATALOG.TXT");
}

void FileSystem::saveBackupConfig()
{
	this->copyFile("DATALOG.TXT", "BACKUP.TXT"); 
}

void FileSystem::saveDefaultConfig()
{
	this->saveSettings("DEFAULT.TXT");
}

void FileSystem::loadActiveConfig()
{
	this->loadSettings("DATALOG.TXT");
}

void FileSystem::loadBackupConfig()
{
	this->loadSettings("BACKUP.TXT");
}

void FileSystem::loadDefaultConfig()
{
	this->loadSettings("DEFAULT.TXT");
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
		Serial.println("OK: File Open. Writing data to " + String(filename));
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
		
		file.println(json);

		for (uint8_t i = 0; i < TRIGCAT; i++) {
			for (uint8_t j = 0; j < TRIGNUMBER; j++) {
				trigger[i][j]->serializeJSON(i, j, json, 2500);
				file.println(json);
			}
		}
		for (uint8_t i = 0; i < RULES; i++) {
			rulesets[i]->serializeJSON(i, json, 2500);
			file.println(json);
		}
		for (uint8_t i = 0; i < ACTIONCHAINS; i++) {
			actionchains[i]->serializeJSON(i, json, 2500);
			file.println(json);
		}
		for (uint8_t i = 0; i < SENSNUMBER; i++) {
			sensors[i]->serializeJSON(i, json, 2500);
			file.println(json);
		}
		Serial.println("OK: Settings save to file");
		file.close();
	}
	else {
		Serial.println("Error: Could not open file.");
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
		Serial.println("OK: File Open. Reading data from " + String(filename));
		
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
		
					stored_time = CurrentTime::epochTime(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);

					if (stored_time > rtc_time) {
						currenttime.updateRTC(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);
						currenttime.syncTimeObject();
						Serial.println("Ok: Updated Time from SD Card");
					}
					else {
						Serial.println("Ok: RTC newer than stored time. Not update.");
					}
					sensor_cycles = (CurrentTime::epochTime(currenttime.current_year, currenttime.current_month, currenttime.current_day, currenttime.current_hour, currenttime.current_minute, 0)) / SENSORFRQ;
				}
				else if (node["type"] == "SENSOR") {
					id = (int)node["id"];
					if (id < SENSNUMBER) {
						success = sensors[id]->deserializeJSON(node);
						//Serial.println("Ok: Deserialized sensor " + (String)id);
					}
					else {
						Serial.println("Error: Invalid sensor id " + (String)id);
						success = false;
					}
				}
				else if (node["type"] == "TRIGGER") {
					id = (int)node["id"];
					cat = (int)node["cat"];

					if (id <= TRIGNUMBER && cat <= TRIGCAT) {
						success = trigger[cat][id]->deserializeJSON(node);
						//Serial.print("Ok: Deserialized trigger " + (String)cat);
						//Serial.println("|" + (String)id);
					}
					else {
						Serial.println("Error: Invalid trigger cat/id");
						success = false;
					}
				}
				else if (node["type"] == "RULE") {
					id = (int)node["id"];
					if (id < RULES) {
						success = rulesets[id]->deserializeJSON(node);
						//Serial.println("Ok: Deserialized ruleset " + (String)id);
					}
					else {
						Serial.println("Error: Invalid ruleset id " + (String)id);
						success = false;
					}
				}
				else if (node["type"] == "CHAIN") {
					id = (int)node["id"];
					if (id < ACTIONCHAINS) {
						success = actionchains[id]->deserializeJSON(node);
						//Serial.println("Ok: Deserialized actionchain " + (String)id);
					}
					else {
						Serial.println("Error: Invalid actionchain id " + (String)id);
						success = false;
					}
				}
			}
			else {
				Serial.println("Error: Parsing of JSON line " + (String)j);
				success = false;
			}
			j++;
		}
		file.close();
		Serial.println("Summary:");
		Serial.println("Read Lines: " + (String)j);
	}
	else {
		Serial.println("Error: Could not open file.");
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

	Serial.println("OK: Creating Backup");
	if (current_file.open(source, O_READ)) {
		Serial.println("OK: Current File Open.");
		
		if (backup_file.open(destination, O_CREAT | O_TRUNC | O_WRITE)) {
			Serial.println("OK: Back File Open.");
			Serial.print("Copying [");

			while ((current_file.read(buf, sizeof(buf))) > 0) {
				backup_file.write(buf, n);
				Serial.print(".");
				i++;
			}
			output = String(i * 64);
			Serial.println("]");
			Serial.println("Summary: Bytes copied " + output);
			current_file.close();
			backup_file.close();
		}
		else {
			Serial.println("Error: Could not open Destination file.");
			success = false;
		}
	}
	else {
		Serial.println("Error: Could not open Source file.");
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
	
	wifi_ssid = "wgempire";
	wifi_pw = "ert456sdf233sa!!!";
	api_secret = "schnitzel";

	Serial.println("Ok: Factory Reset");
}
