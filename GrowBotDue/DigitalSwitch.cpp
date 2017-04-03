// 
// 
// 

#include "DigitalSwitch.h"

DigitalSwitch::DigitalSwitch()
{
	pinMode(TOP1, OUTPUT);
	pinMode(TOP2, OUTPUT);
	pinMode(TOP3, OUTPUT);
	pinMode(TOP4, OUTPUT);

	//Set to off
	digitalWrite(TOP1, HIGH);
	digitalWrite(TOP2, HIGH);
	digitalWrite(TOP3, HIGH);
	digitalWrite(TOP4, HIGH);
}

void DigitalSwitch::S1On()
{
	if (digitalRead(TOP1) == 1) {
		digitalWrite(TOP1, LOW);
	}
}

void DigitalSwitch::S1Off()
{
	if (digitalRead(TOP1) == 0) {
		digitalWrite(TOP1, HIGH);
	}
}

void DigitalSwitch::S2On()
{
	if (digitalRead(TOP2) == 1) {
		digitalWrite(TOP2, LOW);
	}
}

void DigitalSwitch::S2Off()
{
	if (digitalRead(TOP2) == 0) {
		digitalWrite(TOP2, HIGH);
	}
}

void DigitalSwitch::S3On()
{
	if (digitalRead(TOP3) == 1) {
		digitalWrite(TOP3, LOW);
	}
}

void DigitalSwitch::S3Off()
{
	if (digitalRead(TOP3) == 0) {
		digitalWrite(TOP3, HIGH);
	}
}

void DigitalSwitch::S4On()
{
	if (digitalRead(TOP4) == 1) {
		digitalWrite(TOP4, LOW);
	}
}

void DigitalSwitch::S4Off()
{
	if (digitalRead(TOP4) == 0) {
		digitalWrite(TOP4, HIGH);
	}
}

String DigitalSwitch::getStatusS1()
{
	if (digitalRead(TOP1) == 1) {
		return String("OFF");
	}
	return String("ON");
}

String DigitalSwitch::getStatusS2()
{
	if (digitalRead(TOP2) == 1) {
		return String("OFF");
	}
	return String("ON");
}

String DigitalSwitch::getStatusS3()
{
	if (digitalRead(TOP3) == 1) {
		return String("OFF");
	}
	return String("ON");
}

String DigitalSwitch::getStatusS4()
{
	if (digitalRead(TOP4) == 1) {
		return String("OFF");
	}
	return String("ON");
}
