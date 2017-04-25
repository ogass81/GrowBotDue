// RCSocketController.h

#ifndef _RCSOCKETCONTROLLER_h
#define _RCSOCKETCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>
#include <RCSwitch.h>

class RCSocketCodeSet {
public:
	bool active = false;
	String name;
	
	int nReceiveTolerance = 0;
	unsigned long nReceivedValue[RC_SIGNALS];
	unsigned int nReceivedDelay[RC_SIGNALS];
	unsigned int nReceivedProtocol[RC_SIGNALS];
	unsigned int nReceivedBitlength[RC_SIGNALS];
	int repeat = 0;
	uint8_t signal_ptr = 0;

	RCSocketCodeSet(String name, int repeat);
	void incSignalPtr();
	void decSignalPtr();

	unsigned long getCurrentValue();
	unsigned int getCurrentDelay();
	unsigned int getCurrentBitlength();
	unsigned int getCurrentProtocol();

	unsigned long getValueFrom(uint8_t set);
	unsigned int getDelayFrom(uint8_t set);
	unsigned int getBitlengthFrom(uint8_t set);
	unsigned int getProtocolFrom(uint8_t set);

	void setCurrentValue(unsigned long value);
	void setCurrentDelay(unsigned int delay);
	void setCurrentBitlength(unsigned int bitlength);
	void setCurrentProtocol(unsigned int protocol);

	void switchCurrentProtocol();
	void switchSignalPtr();

	bool isNewSignal(long dec_val);
	uint8_t numberSignals();

	void serializeJSON(JsonObject & codeset, uint8_t id);
	bool deserializeJSON(JsonObject& data);
};

class RCSocketController : public RCSwitch {
private:
	uint8_t receiver_pin;
	uint8_t transmitter_pin;
	uint8_t code_set_ptr = 0;
public:
	RCSocketCodeSet *socketcode[2*RC_SOCKETS];
	bool learning = false;


	RCSocketController(uint8_t transmitter, uint8_t receiver);
	//Control Hardware
	void receiver_on();
	void receiver_off();
	void transmitter_on();
	void transmitter_off();

	void learningmode_on();
	void learningmode_off();

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
	String getSignalPointer();
	String getSwitchSignalText();
	String getSwitchProtocolText();
	String getLearningMode();

	//UI Control
	void incCodeSet_Ptr();
	void decCodeSet_Ptr();
	void switchLearningMode();
	void switchSignal();
	void switchProtocol();
	void switchActive();

	//Helper
	static const char * bin2tristate(const char * bin);
	static String dec2binWzerofill(unsigned long Dec, unsigned int bitLength);

	//Serialize
	void serializeJSON(char* json, size_t maxSize);
	bool deserializeJSON(JsonObject& data);
};

#endif

