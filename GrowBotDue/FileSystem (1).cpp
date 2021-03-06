// 
// 
// 

#include "FileSystem.h"

FileSystem::FileSystem()
{
	
}

void FileSystem::init()
{
	if (!sd.begin(SD_CONTROL_PIN, SPI_EIGHTH_SPEED)) {
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

	char json[2500];
	int bytes;
	bool complete;
	bool success = true;

	if (file.open(filename, O_CREAT | O_TRUNC | O_WRITE)) {
		//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("File Open"), "", "", "");
		led[2]->turnOn();
		//Settings
		Setting::serializeJSON(json, 2500);
		file.println(json);
		LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Overall Settings"), "", "", "");

		for (uint8_t i = 0; i < TRIGGER_TYPES; i++) {
			for (uint8_t j = 0; j < TRIGGER_SETS; j++) {
				trigger[i][j]->serializeJSON(i, j, json, 2500, DETAILS);
				led[2]->switchState();
				file.println(json);
				//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Trigger"), F("Cat | Id"), String(i), String(j));
			}
		}
		for (uint8_t i = 0; i < RULESETS_NUM; i++) {
			rulesets[i]->serializeJSON(i, json, 2500, DETAILS);
			led[2]->switchState();
			file.println(json);
			//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Rule"), F("Id"), String(i), "");
		}
		for (uint8_t i = 0; i < ACTIONCHAINS_NUM; i++) {
			actionchains[i]->serializeJSON(i, json, 2500, DETAILS);
			led[2]->switchState();
			file.println(json);
			//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Actionschain"), F("Id"), String(i), "");
		}
		for (uint8_t i = 0; i < SENS_NUM; i++) {
			sensors[i]->serializeJSON(i, json, 5000, DETAILS);
			led[2]->switchState();
			file.println(json);
			//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Sensor"), F("Id"), String(i), "");
		}
		for (uint8_t i = 0; i < RC_SOCKETS; i++) {
			rcsocketcontroller->serializeJSON(i, json, 2500, DETAILS);
			led[2]->switchState();
			file.println(json);
			//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("OK: Saved Remote Socket"), F("Id"), String(i), "");
		}
		LOGMSG(F("[FileSystem]"), F("OK: Saved Settings to file:"), String(filename), "", "");
		led[2]->turnOff();
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
	int cat = 0;
	int id = 0;
	int j = 0;
	bool success = true;

	if (file.open(filename, O_READ)) {
		
		while (file.available()) {
			//Buffer Needs to be here ...
			StaticJsonBuffer<6000> jsonBuffer;
		
			json = file.readStringUntil('\n');

			JsonObject& node = jsonBuffer.parseObject(json);

			cat = 0;
			id = 0;

			if (node.success()) {
				if (node["obj"] == "SETTING") {
					success = Setting::deserializeJSON(node);
				}
				else if (node["obj"] == "SENSOR") {
					id = (int)node["id"];
					if (id < SENS_NUM) {
						success = sensors[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Sensor"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Sensor"), F("Id"), String(id), "");
						success = false;
					}
				}
				else if (node["obj"] == "TRIGGER") {
					id = (int)node["id"];
					cat = (int)node["cat"];

					if (id <= TRIGGER_SETS && cat <= TRIGGER_TYPES) {
						success = trigger[cat][id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Trigger"), F("Cat | Id"), String(id), String(cat));
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Trigger"), F("Cat | Id"), String(cat), String(id));
						success = false;
					}
				}
				else if (node["obj"] == "RULESET") {
					id = (int)node["id"];
					if (id < RULESETS_NUM) {
						success = rulesets[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Ruleset"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Ruleset"), F("Id"), String(id), "");
						success = false;
					}
				}
				else if (node["obj"] == "ACTIONCHAIN") {
					id = (int)node["id"];
					if (id < ACTIONCHAINS_NUM) {
						success = actionchains[id]->deserializeJSON(node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Actionchain"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Invalid Actionchain"), F("Id"), String(id), "");
						success = false;
					}
				}
				else if (node["obj"] == "RCSOCKET") {
					id = (int)node["id"];
					if (id < RC_SOCKETS) {
						success = rcsocketcontroller->deserializeJSON(id, node);
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("OK: Loaded Remote Controlled Socket"), F("Id"), String(id), "");
					}
					else {
						LOGDEBUG(F("[FileSystem]"), F("loadSettings()"), F("ERROR: Remote Controlled Socket"), F("Id"), String(id), "");
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

			led[2]->turnOn();
			while ((current_file.read(buf, sizeof(buf))) > 0) {
				led[2]->switchState();
				backup_file.write(buf, sizeof(buf));
				i++;
			}
			led[2]->turnOff();

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
