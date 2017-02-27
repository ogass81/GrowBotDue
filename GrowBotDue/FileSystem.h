// FileSystem.h

#ifndef _FILESYSTEM_h
#define _FILESYSTEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <SD.h>
#include <SPI.h>

extern long sensor_cycles;


class FileSystem {
	//SD Card
	Sd2Card card;
	SdVolume volume;
	SdFile root;

public:
	FileSystem();

	bool init();
	bool savetoCard();


};



#endif

