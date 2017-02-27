// 
// 
// 

#include "FileSystem.h"

FileSystem::FileSystem()
{
	
}



bool FileSystem::init()
{
	//SD Card
	if (!card.init(SPI_HALF_SPEED, SDCS)) {
		Serial.println("Error: Initialization of SD card failed.");
		return false;
	}
	else {
		Serial.println("OK: SD card found.");
	}

	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		return false;
	}
	else {
		Serial.println("OK: Volume found ");
	}
	
	return true;
}

bool FileSystem::savetoCard()
{
	
	
	
	return false;
}
