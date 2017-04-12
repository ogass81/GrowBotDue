// 
// 
// 

#include "RCSocketController.h"
RCSocketCodeSet::RCSocketCodeSet(String name, int repeat)
{
	this->name = name;
	this->repeat = repeat;

	for (uint8_t i = 0; i < RC_SIGNALS; i++) {
		nReceivedValue[i] = 0;
		nReceivedDelay[i] = 0;
		nReceivedBitlength[i] = 0;
		nReceivedProtocol[i] = 0;
	}
}

void RCSocketCodeSet::incSignalPtr()
{
	if (signal_ptr < RC_SIGNALS - 1) signal_ptr++;
	else signal_ptr = 0;
}

void RCSocketCodeSet::decSignalPtr()
{
	if (signal_ptr > 0 ) signal_ptr--;
	else signal_ptr = RC_SIGNALS - 1;
}

unsigned long RCSocketCodeSet::getCurrentValue()
{
	return nReceivedValue[signal_ptr];
}

unsigned int RCSocketCodeSet::getCurrentDelay()
{
	return nReceivedDelay[signal_ptr];
}

unsigned int RCSocketCodeSet::getCurrentBitlength()
{
	return nReceivedBitlength[signal_ptr];
}

unsigned int RCSocketCodeSet::getCurrentProtocol()
{
	return nReceivedProtocol[signal_ptr];
}

void RCSocketCodeSet::setCurrentValue(unsigned long value)
{
	nReceivedValue[signal_ptr] = value;
}

void RCSocketCodeSet::setCurrentDelay(unsigned int delay)
{
	nReceivedDelay[signal_ptr] = delay;
}

void RCSocketCodeSet::setCurrentBitlength(unsigned int bitlength)
{
	nReceivedBitlength[signal_ptr] = bitlength;
}

void RCSocketCodeSet::setCurrentProtocol(unsigned int protocol)
{
	nReceivedProtocol[signal_ptr] = protocol;
}

void RCSocketCodeSet::switchCurrentProtocol()
{
	if (nReceivedValue[signal_ptr] != 0) {
		if (nReceivedProtocol[signal_ptr] < 6) nReceivedProtocol[signal_ptr]++;
		else nReceivedProtocol[signal_ptr] = 1;
	}
}

void RCSocketCodeSet::switchSignalPtr()
{
	if (signal_ptr < numberSignals() - 1) signal_ptr++;
	else signal_ptr = 0;
}

bool RCSocketCodeSet::isNewSignal(long dec_val)
{
	bool isnew = true;
	for (uint8_t i = 0; i < RC_SIGNALS; i++) {
		if (dec_val == nReceivedValue[i]) isnew = false;
	}
	return isnew;
}

uint8_t RCSocketCodeSet::numberSignals()
{
	for (uint8_t i = 0; i < RC_SIGNALS; i++) {
		if (nReceivedValue[i] == 0) {
			return i;
		}
	}
	return RC_SIGNALS;
}

RCSocketController::RCSocketController(uint8_t transmitter, uint8_t receiver)
{
	receiver_pin = receiver;
	transmitter_pin = transmitter;


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
		socketcode[i] = new RCSocketCodeSet(String(set_name), RC_REPEAT);
	}
	LOGMSG(F("[RCSocketController]"), F("OK: Started 433Mhz Controller."), F("Supported Sockets"), String(RC_SOCKETS), "");
}

void RCSocketController::receiver_on()
{
	enableReceive(receiver_pin);
	LOGDEBUG(F("[RCSocketController]"), F("receiver_on()"), F("OK: Turning on Receiver"), F("Pin"), String(receiver_pin), "");
}

void RCSocketController::receiver_off()
{
	disableReceive();
	LOGDEBUG(F("[RCSocketController]"), F("receiver_on()"), F("OK: Turning off Receiver"), F("Pin"), String(receiver_pin), "");
}

void RCSocketController::transmitter_on()
{
	enableTransmit(transmitter_pin);
	LOGDEBUG(F("[RCSocketController]"), F("receiver_on()"), F("OK: Turning on Transmitter"), F("Pin"), String(transmitter_pin), "");
}

void RCSocketController::transmitter_off()
{
	disableTransmit();
	LOGDEBUG(F("[RCSocketController]"), F("receiver_on()"), F("OK: Turning off Transmitter"), F("Pin"), String(transmitter_pin), "");
}

void RCSocketController::learningmode_on()
{
	receiver_on();
	learning = true;
}

void RCSocketController::learningmode_off()
{
	receiver_off();
	learning = false;
	socketcode[code_set_ptr]->signal_ptr = 0;
}

void RCSocketController::learnPattern()
{
	learnPattern(code_set_ptr);
}

void RCSocketController::learnPattern(uint8_t set)
{
	if (socketcode[set]->isNewSignal(getReceivedValue()) == true) {
		socketcode[set]->setCurrentValue(getReceivedValue());
		socketcode[set]->setCurrentBitlength(getReceivedBitlength());
		socketcode[set]->setCurrentDelay(getReceivedDelay());
		socketcode[set]->setCurrentProtocol(getReceivedProtocol());
		socketcode[set]->incSignalPtr();
		LOGDEBUG(F("[RCSocketController]"), F("learnPattern()"), F("OK: Received data -> New Signal"), String(socketcode[set]->getCurrentValue()), String(socketcode[set]->getCurrentDelay()), String(socketcode[set]->getCurrentProtocol()));
	}
	else {
		LOGDEBUG(F("[RCSocketController]"), F("learnPattern()"), F("OK: Received data -> Signal alread known "), String(socketcode[set]->getCurrentValue()), String(socketcode[set]->getCurrentDelay()), String(socketcode[set]->getCurrentProtocol()));
	}
}

void RCSocketController::testSettings()
{
	learning = false;
	socketcode[code_set_ptr]->active = true;

	for (uint8_t i = 0; i < 5; i++) {
		sendCode(code_set_ptr);
		delay(200);
		LOGDEBUG(F("[RCSocketController]"), F("testSettings()"), F("OK: Starting Test for Set"), String(code_set_ptr), F("Number of Signal"), String(socketcode[code_set_ptr]->numberSignals()));
	}
	socketcode[code_set_ptr]->active = false;
}

void RCSocketController::switchLearningMode()
{
	if (learning == true) {
		learningmode_off();
	}
	else {
		learningmode_on();
	}
}

void RCSocketController::switchSignal()
{
	socketcode[code_set_ptr]->switchSignalPtr();
}

void RCSocketController::switchProtocol()
{
	socketcode[code_set_ptr]->switchCurrentProtocol();
}

void RCSocketController::switchActive()
{
	learning = false;
	if (socketcode[code_set_ptr]->active == true) socketcode[code_set_ptr]->active = false;
	else socketcode[code_set_ptr]->active = true;
}

void RCSocketController::resetSettings()
{
	for (uint8_t i = 0; i < RC_SIGNALS; i++) {
		socketcode[code_set_ptr]->nReceivedDelay[i] = 0;
		socketcode[code_set_ptr]->nReceivedProtocol[i] = 0;
		socketcode[code_set_ptr]->nReceivedValue[i] = 0;
		socketcode[code_set_ptr]->nReceivedBitlength[i] = 0;
	}
	socketcode[code_set_ptr]->active = false;
}

String RCSocketController::getDecimalKey()
{
	if (socketcode[code_set_ptr]->getCurrentValue() == 0) {
		return String(F("<undefined>"));
	}
	else {
		return String(socketcode[code_set_ptr]->getCurrentValue());
	}
}

String RCSocketController::getBinaryKey()
{
	if (socketcode[code_set_ptr]->getCurrentValue() == 0) {
		return String(F("<undefined>"));
	}
	else {
		return String(dec2binWzerofill(socketcode[code_set_ptr]->getCurrentValue(), socketcode[code_set_ptr]->getCurrentBitlength()));
	}
}

String RCSocketController::getBitLength()
{
	if (socketcode[code_set_ptr]->getCurrentBitlength() == 0) {
		return String(F("<undefined>"));
	}
	else {
		return String(socketcode[code_set_ptr]->getCurrentBitlength());
	}
}

String RCSocketController::getProtocol()
{
	if (socketcode[code_set_ptr]->getCurrentProtocol() == 0) {
		return String(F("<undefined>"));
	}
	else {
		return String(socketcode[code_set_ptr]->getCurrentProtocol());
	}
}

String RCSocketController::getActive()
{
	if (socketcode[code_set_ptr]->active == true) return String("ON");
	else return String("OFF");
}

String RCSocketController::getName()
{
	return String(socketcode[code_set_ptr]->name);
}

String RCSocketController::getSignalPointer()
{
	return String(socketcode[code_set_ptr]->signal_ptr);
}

String RCSocketController::getSwitchSignalText()
{
	String temp;
	temp = "(";
	temp += getSignalPointer();
	temp += "/";
	temp += String(socketcode[code_set_ptr]->numberSignals());
	temp += ")";

	return String(temp);
}

String RCSocketController::getSwitchProtocolText()
{
	return String(F("Change"));
}

String RCSocketController::getLearningMode()
{
	if (learning == true) return String(" Stop Learning");
	else return String(" Start Learning");
}

void RCSocketController::incCodeSet_Ptr()
{
	learning = false;
	if (code_set_ptr < (RC_SOCKETS * 2) - 1) code_set_ptr++;
	else code_set_ptr = 0;
}

void RCSocketController::decCodeSet_Ptr()
{
	learning = false;
	if (code_set_ptr > 0) code_set_ptr--;
	else code_set_ptr = RC_SOCKETS - 1;
}

void RCSocketController::sendCode(int set)
{
	LOGDEBUG(F("[RCSocketController]"), F("sendCode()"), F("OK: Called with"), F("Parameter"), String(set), String(learning));
	if (learning != true) {
		if (socketcode[set]->active == true) {
			transmitter_on();
			socketcode[set]->signal_ptr == 0;
			setRepeatTransmit(socketcode[set]->repeat);

			for (uint8_t i = 0; i < socketcode[set]->numberSignals(); i++) {
				setPulseLength(socketcode[set]->getCurrentDelay());
				setProtocol(socketcode[set]->getCurrentProtocol());
				send(socketcode[set]->getCurrentValue(), socketcode[set]->getCurrentBitlength());
				LOGDEBUG(F("[RCSocketController]"), F("sendCode()"), F("OK: Sending Signal"), String(socketcode[code_set_ptr]->getCurrentValue()), String(socketcode[code_set_ptr]->getCurrentDelay()), String(socketcode[code_set_ptr]->getCurrentProtocol()));
				socketcode[set]->incSignalPtr();
			}
			transmitter_off();
		}
		else {
			LOGDEBUG(F("[RCSocketController]"), F("sendCode()"), F("ERROR: Socket not active"), F("Parameter"), String(set), String(learning));
		}
	}
}

const char* RCSocketController::bin2tristate(const char* bin) {
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

String RCSocketController::dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
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