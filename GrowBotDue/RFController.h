// RFController.h

#ifndef _RFCONTROLLER_h
#define _RFCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <RCSwitch.h>
#include "TaskManager.h"

class RFSocketCodeSet {
public:
	bool active = false;
	String name;
	
	int nReceiveTolerance = 0;
	unsigned long nReceivedValue = 0;
	unsigned int nReceivedBitlength = 0;
	unsigned int nReceivedDelay = 0;
	unsigned int nReceivedProtocol = 0;
	unsigned int nSeparationLimit = 0;

	int repeat = 0;

	RFSocketCodeSet(String name, int repeat);
};

class RFController : public RCSwitch {
private:
	uint8_t receiver_pin;
	uint8_t transmitter_pin;
	uint8_t code_set_ptr = 0;
public:
	RFSocketCodeSet *socketcode[2*RC_SOCKETS];
	bool learning = false;


	RFController(uint8_t transmitter, uint8_t receiver);
	//Control Hardware
	void receiver_on();
	void receiver_off();
	void transmitter_on();
	void transmitter_off();

	void learnPattern();
	void learnPattern(uint8_t code_set);
	void testSettings();
	void resetSettings();

	void sendCode(int id);

	//UI Output
	String getDecimalKey();
	String getBinaryKey();
	String getBitLength();
	String getProtocol();
	String getActive();
	String getName();
	String getLearningMode();

	//UI Control
	void incCodeSet_Ptr();
	void decCodeSet_Ptr();
	void switchLearningMode();
	void switchActive();

	//Helper
	static const char * bin2tristate(const char * bin);
	static String dec2binWzerofill(unsigned long Dec, unsigned int bitLength);
};

#endif

