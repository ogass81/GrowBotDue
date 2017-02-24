// 
// 
// 

#include "DataStore.h"

void DataStore::serialize()
{
	char json[2000];

	for (uint8_t i = 0; i < TRIGCAT; i++) {
		for (uint8_t j = 0; j < TRIGNUMBER; j++) {
			trigger[i][j]->serializeJSON(i, j, json, 2000);
			Serial.println(json);
		}
	}


	for (uint8_t i = 0; i < RULES; i++) {
		rulesets[i]->serializeJSON(i, json, 2000);
		Serial.println(json);
	}

	for (uint8_t i = 0; i < SENSNUMBER; i++) {
		sensors[i]->serializeJSON(i, json, 2000);
		Serial.println(json);
	}
}

void DataStore::deserialize()
{
}
