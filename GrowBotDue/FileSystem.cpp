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

void FileSystem::savetoCard()
{
	StaticJsonBuffer<500> jsonBuffer;
	char json[2000];
	int bytes;
	bool complete;
	
	if (file.open("DATALOG.TXT", O_CREAT | O_TRUNC | O_WRITE)) {
		Serial.println("OK: File Open. Writing data ...");
		JsonObject& root = jsonBuffer.createObject();
		root["type"] = "SETTING";
		root["cycles"] = sensor_cycles;
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
				trigger[i][j]->serializeJSON(i, j, json, 2000);
				file.println(json);
			}
		}
		for (uint8_t i = 0; i < RULES; i++) {
			rulesets[i]->serializeJSON(i, json, 2000);
			file.println(json);
		}
		for (uint8_t i = 0; i < SENSNUMBER; i++) {
			sensors[i]->serializeJSON(i, json, 2000);
			file.println(json);
		}
		Serial.println("OK: Settings save to file");
		file.close();
	}
	else {
		Serial.println("Error: Could not open file.");
	}
}

void FileSystem::readfromCard()
{
	String json;
	long stored_time, rtc_time;
	int cat = 0;
	int id = 0;
	int j = 0;
	bool complete = false;

	rtc_time = currenttime.epochTime();

		if (file.open("DATALOG.TXT", O_READ)) {
		Serial.println("OK: File Open. Reading data ...");
		
		while (file.available()) {
			//Buffer Needs to be here ...
			StaticJsonBuffer<2000> jsonBuffer;
			
			
			json = file.readStringUntil('\n');

			JsonObject& node = jsonBuffer.parseObject(json);

			cat = 0;
			id = 0;
			stored_time = 0;

			if (node.success()) {
				if (node["type"] == "SETTING") {
					sensor_cycles = (long)node["cycles"];

					stored_time = CurrentTime::epochTime(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);

					if (stored_time > rtc_time) {
						currenttime.updateRTC(node["year"], node["month"], node["day"], node["hour"], node["minute"], node["second"]);
						currenttime.updateTimeObject();
						Serial.println("Ok: Updated Time from SD Card");
						complete = true;
					}
					else {
						Serial.println("Ok: RTC newer than stored time. Not update.");
					}
				}
				else if (node["type"] == "SENSOR") {
					id = (int)node["id"];
					if (id < SENSNUMBER) {
						sensors[id]->deserializeJSON(node);
						Serial.println("Ok: Deserialized sensor " + (String)id);
						complete = true;
					}
					else Serial.println("Error: Invalid sensor id " + (String)id);
				}
				else if (node["type"] == "TRIGGER") {
					id = (int)node["id"];
					cat = (int)node["cat"];

					if (id <= TRIGNUMBER && cat <= TRIGCAT) {
						trigger[cat][id]->deserializeJSON(node);
						Serial.print("Ok: Deserialized trigger " + (String)cat);
						Serial.println("|" + (String)id);
						complete = true;
					}
					else Serial.println("Error: Invalid trigger cat/id");
				}
				else if (node["type"] == "RULE") {
					id = (int)node["id"];
					if (id < RULES) {
						rulesets[id]->deserializeJSON(node);
						Serial.println("Ok: Deserialized ruleset " + (String)id);
						complete = true;
					}
					else Serial.println("Error: Invalid ruleset id " + (String)id);
				}
			}
			else Serial.println("Error: Parsing of JSON line " + (String)j);
			
			j++;
		}
		file.close();
		Serial.println("Summary:");
		Serial.println("Read Lines: " + (String)j);
		Serial.println("Parsed JSON: " + (String)complete);
	}
	else {
		Serial.println("Error: Could not open file.");
	}
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

	sensor_cycles = 0;
	currenttime.updateRTCdefault();
}
