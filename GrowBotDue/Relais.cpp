// 
// 
// 

#include "Relais.h"

RelaisBoard::RelaisBoard() {
	pinMode(OUT_RELAY_1, OUTPUT);
	pinMode(OUT_RELAY_2, OUTPUT);
	pinMode(OUT_RELAY_3, OUTPUT);
	pinMode(OUT_RELAY_4, OUTPUT);
	
	digitalWrite(OUT_RELAY_1, HIGH);
	digitalWrite(OUT_RELAY_2, HIGH);
	digitalWrite(OUT_RELAY_3, HIGH);
	digitalWrite(OUT_RELAY_4, HIGH);
}

void RelaisBoard::allOff() {
	digitalWrite(OUT_RELAY_1, HIGH);
	digitalWrite(OUT_RELAY_2, HIGH);
	digitalWrite(OUT_RELAY_3, HIGH);
	digitalWrite(OUT_RELAY_4, HIGH);
}
void RelaisBoard::allOn() {
	digitalWrite(OUT_RELAY_1, LOW);
	digitalWrite(OUT_RELAY_2, LOW);
	digitalWrite(OUT_RELAY_3, LOW);
	digitalWrite(OUT_RELAY_4, LOW);
}
void RelaisBoard::switchR1() {
	if (digitalRead(OUT_RELAY_1) == 1) {
		digitalWrite(OUT_RELAY_1, LOW);
	}
	else {
		digitalWrite(OUT_RELAY_1, HIGH);
	}
}
void RelaisBoard::switchR2() {
	if (digitalRead(OUT_RELAY_2) == 1) {
		digitalWrite(OUT_RELAY_2, LOW);
	}
	else {
		digitalWrite(OUT_RELAY_2, HIGH);
	}
}
void RelaisBoard::switchR3() {
	if (digitalRead(OUT_RELAY_3) == 1) {
		digitalWrite(OUT_RELAY_3, LOW);
	}
	else {
		digitalWrite(OUT_RELAY_3, HIGH);
	}
}
void RelaisBoard::switchR4() {
	if (digitalRead(OUT_RELAY_4) == 1) {
		digitalWrite(OUT_RELAY_4, LOW);
	}
	else {
		digitalWrite(OUT_RELAY_4, HIGH);
	}
}

void RelaisBoard::R1On()
{
	if (digitalRead(OUT_RELAY_1) == 1) {
		digitalWrite(OUT_RELAY_1, LOW);
	}
}

void RelaisBoard::R1Off()
{
	if (digitalRead(OUT_RELAY_1) == 0) {
		digitalWrite(OUT_RELAY_1, HIGH);
	}
}

void RelaisBoard::R2On()
{
	if (digitalRead(OUT_RELAY_2) == 1) {
		digitalWrite(OUT_RELAY_2, LOW);
	}
}

void RelaisBoard::R2Off()
{
	if (digitalRead(OUT_RELAY_2) == 0) {
		digitalWrite(OUT_RELAY_2, HIGH);
	}
}

void RelaisBoard::R3On()
{
	if (digitalRead(OUT_RELAY_3) == 1) {
		digitalWrite(OUT_RELAY_3, LOW);
	}
}

void RelaisBoard::R3Off()
{
	if (digitalRead(OUT_RELAY_3) == 0) {
		digitalWrite(OUT_RELAY_3, HIGH);
	}
}

void RelaisBoard::R4On()
{
	if (digitalRead(OUT_RELAY_4) == 1) {
		digitalWrite(OUT_RELAY_4, LOW);
	}
}

void RelaisBoard::R4Off()
{
	if (digitalRead(OUT_RELAY_4) == 0) {
		digitalWrite(OUT_RELAY_4, HIGH);
	}
}

String RelaisBoard::getStatusR1() {
	if (digitalRead(OUT_RELAY_1) == 1) {
		return String(F("OFF"));
	}
	return String(F("ON"));
}

String RelaisBoard::getStatusR2() {
	if (digitalRead(OUT_RELAY_2) == 1) {
		return String(F("OFF"));
	}
	return String(F("ON"));
}

String RelaisBoard::getStatusR3() {
	if (digitalRead(OUT_RELAY_3) == 1) {
		return String(F("OFF"));
	}
	return String(F("ON"));
}

String RelaisBoard::getStatusR4() {
	if (digitalRead(OUT_RELAY_4) == 1) {
		return String(F("OFF"));
	}
	return String(F("ON"));
}