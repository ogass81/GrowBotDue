// 
// 
// 

#include "LogEngine.h"

LogEntry::LogEntry(int id, uint8_t type, String origin, String message, uint8_t size)
{
	LOGDEBUG2(F("LogEntry"), F("LogEntry()"), F("New LogEntry"), F("Parameters"), String(size), "")

	this->id = id;
	this->type = type;
	this->origin = origin;
	this->message = message;

	this->para_size = size;
	this->para_ptr = 0;

	this->keys = new String[size];
	this->values = new String[size];
}

LogEntry::~LogEntry()
{
	//LOGDEBUG2(F("LogEntry"), F("~LogEntry()"), F("Freed memory for Key->Value"), "", "", "")
	delete[] this->keys;
	delete[] this->values;
}

void LogEntry::addParameter(String key, String value)
{
	//LOGDEBUG2(F("LogEntry"), F("addParameter()"), F("Adding Key->Value Pair"), String(key), String(value), "")
	if (para_ptr < this->para_size) {
		this->keys[para_ptr] = key;
		this->values[para_ptr] = value;
		para_ptr++;
	}
}


String LogEntry::serializeJSON()
{
	StaticJsonBuffer<750> jsonBuffer;
	char json[1500];

	JsonObject& log = jsonBuffer.createObject();
	
	log["id"] = id;
	log["typ"] = type;
	log["time"] = internalRTC.getEpochTime();
	log["src"] = origin;
	log["msg"] = message;


	JsonArray& keys = log.createNestedArray("keys");
	for (uint8_t j = 0; j < this->para_size; j++) {
		if(this->keys[j] != "") keys.add(this->keys[j]);
	}

	JsonArray& values = log.createNestedArray("vals");
	for (uint8_t j = 0; j < this->para_size; j++) {
		if (this->values[j] != "") values.add(this->values[j]);
	}
	log.printTo(json, 1500);
	LOGDEBUG(F("[LogEntry]"), F("serializeJSON()"), F("OK: Serialized LogEntry"), "", "", "");

	return String(json);
}

LogEngine::LogEngine()
{
	this->counter = 0; // filesystem.fileLength("log.json");
}

void LogEngine::begin()
{
	this->counter = filesystem.fileLength("log.json");
}

void LogEngine::addLogEntry(uint8_t type, String origin, String message, String keys[], String values[], uint8_t size)
{
	if (entry_ptr == LOGBUFFER_SIZE) {
		saveToFile();
	}

	log_buffer[entry_ptr] = new LogEntry(counter, type, origin, message, size);
	LOGDEBUG2(F("LogEngine"), F("addLogEntry()"), F("Creating new LogEntry"), String(counter), "", "");
	
	for (uint8_t i = 0; i < size; i++) {
		log_buffer[entry_ptr]->addParameter(keys[i], values[i]);
		//LOGDEBUG2(F("LogEngine"), F("addLogEntry()"), F("Adding Parameter"), String(keys[i]), String(values[i]), "");
	}

	this->entry_ptr++;
	this->counter++;
}

void LogEngine::serializeJSON(char * json, size_t maxSize, int end, int count)
{
	saveToFile();

	if (count == 0) count = LOGBUFFER_SIZE;
	
	filesystem.readLinesFromFile("log.json", counter, end, count, json, JSONCHAR_SIZE);
}

void LogEngine::reset()
{
	saveToFile();
	filesystem.copyFile("log.json", "log.backup");
	filesystem.resetFile("log.json");
	this->counter = 0;
}

void LogEngine::saveToFile()
{
	String output[LOGBUFFER_SIZE]; //MAX

	for (uint8_t i = 0; i < this->entry_ptr; i++) {
		if(log_buffer[i] != nullptr) output[i] = log_buffer[i]->serializeJSON();
	}
	filesystem.appendLinesToFile("log.json", output, this->entry_ptr);


	//Free Memory
	for (uint8_t i = 0; i < this->entry_ptr; i++) if (log_buffer[i] != nullptr) delete this->log_buffer[i];
	this->entry_ptr = 0;

	LOGDEBUG2(F("LogEngine"), F("addLogEntry()"), F("Reset LogBuffer"), String(entry_ptr), "", "")
}
