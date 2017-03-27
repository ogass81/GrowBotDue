// 
// 
// 

#include "Relais.h"

RelaisBoard::RelaisBoard() {
	//Initialize Relais

	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	
	digitalWrite(RELAY1, HIGH);
	digitalWrite(RELAY2, HIGH);
	digitalWrite(RELAY3, HIGH);
	digitalWrite(RELAY4, HIGH);
}

void RelaisBoard::allOff() {
	digitalWrite(RELAY1, HIGH);
	digitalWrite(RELAY2, HIGH);
	digitalWrite(RELAY3, HIGH);
	digitalWrite(RELAY4, HIGH);
}
void RelaisBoard::allOn() {
	digitalWrite(RELAY1, LOW);
	digitalWrite(RELAY2, LOW);
	digitalWrite(RELAY3, LOW);
	digitalWrite(RELAY4, LOW);
}
void RelaisBoard::switchR1() {
	if (digitalRead(RELAY1) == 1) {
		digitalWrite(RELAY1, LOW);
	}
	else {
		digitalWrite(RELAY1, HIGH);
	}
}
void RelaisBoard::switchR2() {
	if (digitalRead(RELAY2) == 1) {
		digitalWrite(RELAY2, LOW);
	}
	else {
		digitalWrite(RELAY2, HIGH);
	}
}
void RelaisBoard::switchR3() {
	if (digitalRead(RELAY3) == 1) {
		digitalWrite(RELAY3, LOW);
	}
	else {
		digitalWrite(RELAY3, HIGH);
	}
}
void RelaisBoard::switchR4() {
	if (digitalRead(RELAY4) == 1) {
		digitalWrite(RELAY4, LOW);
	}
	else {
		digitalWrite(RELAY4, HIGH);
	}
}

void RelaisBoard::R1On()
{
	if (digitalRead(RELAY1) == 1) {
		digitalWrite(RELAY1, LOW);
	}
}

void RelaisBoard::R1Off()
{
	if (digitalRead(RELAY1) == 0) {
		digitalWrite(RELAY1, HIGH);
	}
}

void RelaisBoard::R2On()
{
	if (digitalRead(RELAY2) == 1) {
		digitalWrite(RELAY2, LOW);
	}
}

void RelaisBoard::R2Off()
{
	if (digitalRead(RELAY2) == 0) {
		digitalWrite(RELAY2, HIGH);
	}
}

void RelaisBoard::R3On()
{
	if (digitalRead(RELAY3) == 1) {
		digitalWrite(RELAY3, LOW);
	}
}

void RelaisBoard::R3Off()
{
	if (digitalRead(RELAY3) == 0) {
		digitalWrite(RELAY3, HIGH);
	}
}

void RelaisBoard::R4On()
{
	if (digitalRead(RELAY4) == 1) {
		digitalWrite(RELAY4, LOW);
	}
}

void RelaisBoard::R4Off()
{
	if (digitalRead(RELAY4) == 0) {
		digitalWrite(RELAY4, HIGH);
	}
}

void RelaisBoard::switchR1R2() {
	switchR1();
	switchR2();
}
void RelaisBoard::switchR1R3() {
	switchR1();
	switchR3();
}
void RelaisBoard::switchR1R4() {
	switchR1();
	switchR4();
}
void RelaisBoard::switchR2R3() {
	switchR2();
	switchR3();
}
void RelaisBoard::switchR2R4() {
	switchR2();
	switchR4();
}
void RelaisBoard::switchR3R4() {
	switchR3();
	switchR4();
}

String RelaisBoard::getStatusR1() {
	String tmp;
	if (digitalRead(RELAY1) == 1) {
		tmp = "Off";
	}
	else {
		tmp = "On";
	}
	return tmp;
}
String RelaisBoard::getStatusR2() {
	String tmp;
	if (digitalRead(RELAY2) == 1) {
		tmp = "Off";
	}
	else {
		tmp = "On";
	}
	return tmp;
}
String RelaisBoard::getStatusR3() {
	String tmp;
	if (digitalRead(RELAY3) == 1) {
		tmp = "Off";
	}
	else {
		tmp = "On";
	}
	return tmp;
}
String RelaisBoard::getStatusR4() {
	String tmp;
	if (digitalRead(RELAY4) == 1) {
		tmp = "Off";
	}
	else {
		tmp = "On";
	}
	return tmp;
}
