// 
// 
// 

#include "RFController.h"
RFSocketCodeSet::RFSocketCodeSet(String name, int repeat)
{
	this->name = name;
	this->repeat = repeat;
}

RFController::RFController(uint8_t transmitter, uint8_t receiver)
{
	receiver_pin = receiver;
	transmitter_pin = transmitter;

	enableReceive(receiver_pin);
	enableTransmit(transmitter_pin);

	bool on = true;
	String set_name;

	for (uint8_t i = 0; i < 2 * RC_SOCKETS; i++) {
		set_name = "Set " + String(i+1);
		if (on == true) {
			set_name += " ON";
			on = false;
		}
		else {
			set_name += " OFF";
			on = true;
		}
		socketcode[i] = new RFSocketCodeSet(String(set_name), RC_REPEAT);
	}
	LOGMSG(F("[RFController]"), F("OK: Started 433Mhz Controller."), F("Supported Sockets"), String(RC_SOCKETS), "");
}

void RFController::receiver_on()
{
	enableReceive(receiver_pin);
}

void RFController::receiver_off()
{
	disableReceive();
}

void RFController::transmitter_on()
{
	enableTransmit(transmitter_pin);
}

void RFController::transmitter_off()
{
	disableTransmit();
}

void RFController::learnPattern()
{
	learnPattern(code_set_ptr);
}

void RFController::learnPattern(uint8_t set)
{
	socketcode[set]->nReceivedDelay = getReceivedDelay();
	socketcode[set]->nReceivedProtocol = getReceivedProtocol();
	socketcode[set]->nReceivedValue = getReceivedValue();
	socketcode[set]->nReceivedBitlength = getReceivedBitlength();
	LOGDEBUG(F("[RFController]"), F("learnPattern()"), F("OK: Received data"), String(socketcode[set]->nReceivedValue), String(socketcode[set]->nReceivedDelay), String(socketcode[set]->nReceivedBitlength));
}

void RFController::testSettings()
{
	learning = false;
	socketcode[code_set_ptr]->active = true;
	for (uint8_t i = 0; i < 5; i++) {
		sendCode(code_set_ptr);
		delay(1000);
		LOGDEBUG(F("[RFController]"), F("testSettings()"), F("OK: Sending Test Pattern"), String(socketcode[code_set_ptr]->nReceivedValue), String(socketcode[code_set_ptr]->nReceivedDelay), String(socketcode[code_set_ptr]->nReceivedBitlength));
	}
	socketcode[code_set_ptr]->active = false;
}

void RFController::switchLearningMode()
{
	if (learning == true) learning = false;
	else learning = true;
}

void RFController::switchActive()
{
	learning = false;
	if (socketcode[code_set_ptr]->active == true) socketcode[code_set_ptr]->active = false;
	else socketcode[code_set_ptr]->active = true;
}

void RFController::resetSettings()
{
	socketcode[code_set_ptr]->nReceivedDelay = 0;
	socketcode[code_set_ptr]->nReceivedProtocol = 0;
	socketcode[code_set_ptr]->nReceivedValue = 0;
	socketcode[code_set_ptr]->nReceivedBitlength = 0;

	socketcode[code_set_ptr]->active = false;
}

String RFController::getDecimalKey()
{
	return String(socketcode[code_set_ptr]->nReceivedValue);
}

String RFController::getBinaryKey()
{
	return String(dec2binWzerofill(socketcode[code_set_ptr]->nReceivedValue, socketcode[code_set_ptr]->nReceivedBitlength));
}

String RFController::getBitLength()
{
	return String(socketcode[code_set_ptr]->nReceivedBitlength);
}

String RFController::getProtocol()
{
	return String(socketcode[code_set_ptr]->nReceivedProtocol);
}

String RFController::getActive()
{
	if (socketcode[code_set_ptr]->active == true) return String("ON");
	else return String("OFF");
}

String RFController::getName()
{
	return String(socketcode[code_set_ptr]->name);
}

String RFController::getLearningMode()
{
	if (learning == true) return String(" Stop Learning");
	else return String(" Start Learning");
}

void RFController::incCodeSet_Ptr()
{
	learning = false;
	if (code_set_ptr < (RC_SOCKETS * 2) - 1) code_set_ptr++;
	else code_set_ptr = 0;
}

void RFController::decCodeSet_Ptr()
{
	learning = false;
	if (code_set_ptr > 0) code_set_ptr--;
	else code_set_ptr = RC_SOCKETS - 1;
}

void RFController::sendCode(int set)
{
	if (learning != true) {
		
		if (socketcode[set]->active == true) {

			setPulseLength(320);
			setProtocol(socketcode[set]->nReceivedProtocol);
			setRepeatTransmit(socketcode[set]->repeat);
			

			send(socketcode[set]->nReceivedValue, socketcode[set]->nReceivedBitlength);
		}
	}
}

const char* RFController::bin2tristate(const char* bin) {
	static char returnValue[50];
	int pos = 0;
	int pos2 = 0;
	while (bin[pos] != '\0' && bin[pos + 1] != '\0') {
		if (bin[pos] == '0' && bin[pos + 1] == '0') {
			returnValue[pos2] = '0';
		}
		else if (bin[pos] == '1' && bin[pos + 1] == '1') {
			returnValue[pos2] = '1';
		}
		else if (bin[pos] == '0' && bin[pos + 1] == '1') {
			returnValue[pos2] = 'F';
		}
		else {
			return "not applicable";
		}
		pos = pos + 2;
		pos2++;
	}
	returnValue[pos2] = '\0';
	return returnValue;
}

String RFController::dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
	static char bin[64];
	unsigned int i = 0;

	while (Dec > 0) {
		bin[32 + i++] = ((Dec & 1) > 0) ? '1' : '0';
		Dec = Dec >> 1;
	}

	for (unsigned int j = 0; j< bitLength; j++) {
		if (j >= bitLength - i) {
			bin[j] = bin[31 + i - (j - (bitLength - i))];
		}
		else {
			bin[j] = '0';
		}
	}
	
	bin[bitLength] = '\0';
	

	return String(bin);
}