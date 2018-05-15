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
		LOGDEBUG2(F("[FileSystem]"), F("copyFile()"), F("OK: Source File open"), F("Filename"), String(source), "");
		
		if (backup_file.open(destination, O_CREAT | O_TRUNC | O_WRITE)) {
			LOGDEBUG2(F("[FileSystem]"), F("copyFile()"), F("OK: Target File open"), F("Filename"), String(destination), "");

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

bool FileSystem::appendLinesToFile(const char * filename, String data[], uint8_t size)
{
	File file;

	bool success = true;

	if (file.open(filename, O_CREAT | O_APPEND | O_WRITE)) {
		//LOGDEBUG2(F("[FileSystem]"), F("saveSettings()"), F("File Open"), "", "", "");
		led[2]->turnOn();
		//Settings
		for (uint8_t i = 0; i < size; i++) {
			file.println(data[i]);
		}

		led[2]->turnOff();
		file.close();
		LOGDEBUG2(F("FileSystem"), F("appendLinesToFile()"), F("OK: Saved Log Entries to file"), String(filename), size, "");
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not write to file"), String(filename), "", "");
		success = false;
	}
	return success;
}

void FileSystem::readLinesFromFile(const char* filename, int counter, int end, int count, char * json, int size)
{
	File file;

	DynamicJsonBuffer jsonBuffer;
	JsonObject& container = jsonBuffer.createObject();
	container["num"] = counter;
	JsonArray& list = container.createNestedArray("list");

	int start = 0;
	int line_ptr = 0;
	bool success = true;

	if (end <= 0) {
		end = counter;
	}

	start = end - count; 
	if (start < 0) start = 0;

	if (file.open(filename, O_READ)) {

		while (file.available()) {
			//Buffer Needs to be here ...
			String line = file.readStringUntil('\n');
			
			if (line_ptr < end) {
				if (line_ptr >= start) {
					JsonObject& entry = jsonBuffer.parseObject(line);
					list.add(entry);
				}
			}
			else break;
			line_ptr++;
		}
		file.close();
		LOGDEBUG2(F("FileSystem"), F("readLinesFromFile()"), F("OK: Loading Logentries from File"), String(start), String(end), String(list.size()));
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not read from file"), String(filename), "", "");
		success = false;
	}

	container.printTo(json, size);
}

int FileSystem::fileLength(const char * filename)
{
	File file;
	
	int counter = 0;
	
	if (file.open(filename, O_READ)) {
		while (file.available()) {	
			file.readStringUntil('\n');
			counter++;
		}
		file.close();
		LOGDEBUG2(F("FileSystem"), F("fileLength()"), F("OK: Determining file length"), String(filename), String(counter), "");
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not determine length of file"), String(filename), "", "");
	}
	
	return counter;
}

bool FileSystem::resetFile(const char * filename)
{
	File file;

	if (file.remove()) {
		LOGMSG(F("[FileSystem]"), F("OK: Reset log file"), String(filename), "", "");
		return true;
	}
	else {
		LOGMSG(F("[FileSystem]"), F("ERROR: Could not reset log file"), String(filename), "", "");
		return false;
	}
}
