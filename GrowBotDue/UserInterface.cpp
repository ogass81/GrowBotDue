// 
// 
// 

#include "UserInterface.h"


UserInterface::UserInterface() {
	category_ptr = 0;
	trigger_ptr = 0;
	ruleset_ptr = 0;
	sensor_ptr = 0;
	action_ptr = 0;

	daterange = MINUTE;
}

void UserInterface::inCategoryPtr()
{
	if (category_ptr < (TRIGGER_TYPES - 1)) category_ptr++;
	else category_ptr = 0;
}

void UserInterface::decCategoryPtr()
{
	if (category_ptr > 0) category_ptr--;
	else category_ptr = TRIGGER_TYPES - 1;
}

void UserInterface::setCategoryPtr(int cat)
{
	if (cat >= 0 && cat < TRIGGER_TYPES) category_ptr = cat;
	else category_ptr = 0;

	trigger_ptr = 0;
}

void UserInterface::incSensorPtr()
{
	if (sensor_ptr < (SENS_NUM - 1)) sensor_ptr++;
	else sensor_ptr = 0;
}

void UserInterface::decSensorPtr()
{
	if (sensor_ptr > 0) sensor_ptr--;
	else sensor_ptr = SENS_NUM - 1;
}

void UserInterface::changeDateRange()
{
	switch (daterange) {
	case MINUTE:
		daterange = HOUR;
		break;
	case HOUR:
		daterange = DAY;
		break;
	case DAY:
		daterange = MONTH;
		break;
	case MONTH:
		daterange = YEAR;
		break;
	case YEAR:
		daterange = MINUTE;
		break;
	}
}

void UserInterface::incTriggerPtr()
{
	if (trigger_ptr < (TRIGGER_SETS - 1)) trigger_ptr++;
	else trigger_ptr = 0;
}

void UserInterface::decTriggerPtr()
{
	if (trigger_ptr > 0) trigger_ptr--;
	else trigger_ptr = TRIGGER_SETS - 1;
}

void UserInterface::incRulesetPtr()
{
	if (ruleset_ptr < (RULESETS_NUM - 1)) ruleset_ptr++;
	else ruleset_ptr = 0;
}

void UserInterface::decRulesetPtr()
{
	if (ruleset_ptr > 0) ruleset_ptr--;
	else ruleset_ptr = RULESETS_NUM - 1;
}

void UserInterface::incActionPtr()
{
	if (action_ptr < (ACTIONS_NUM - 1)) action_ptr++;
	else action_ptr = 0;
}

void UserInterface::decActionPtr()
{
	if (action_ptr > 0) action_ptr--;
	else action_ptr = ACTIONS_NUM - 1;
}

void UserInterface::draw()
{
	//Destory old UI Elements
	cleanup();

	//Update BackgroundFacebook
	drawBackground();

	//Draw new Menue 
	drawMenue(current_menue);
	drawFrame(current_frame);
}

void UserInterface::draw(int targetmenue, int targetframe)
{
	//Destory old UI Elements
	cleanup();

	//Update BackgroundFacebook
	drawBackground();

	//Draw new Menue 
	drawMenue(targetmenue);
	drawFrame(targetframe);
}

void UserInterface::drawBackground() {
	myGLCD.clrScr();
	myGLCD.setBackColor(BACKGROUNDCOLOR);
	myGLCD.setColor(VGA_WHITE);
	myGLCD.drawLine(UI_X_DIVIDER, UI_Y_DIVIDER, UI_X_DIVIDER, 239);
	myGLCD.drawLine(UI_X_DIVIDER, UI_Y_DIVIDER, 319, UI_Y_DIVIDER);

	myGLCD.setFont(SmallFont);


	myGLCD.print(currenttime.createDate(), 2, 4);
	myGLCD.print(currenttime.createTime(), 90, 4);
	myGLCD.print(sensors[0]->getValue(), 215, 4);
	myGLCD.print(sensors[1]->getValue(), 270, 4);
}

void UserInterface::drawMenue(int nav) {
	current_menue = nav;

	switch (nav) {

		//Menu Page 1
	case 1:
		menueElements[0] = new MenueButton("Info", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 11, 110);
		menueElements[1] = new MenueButton("Manual", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 12, 120);
		menueElements[2] = new MenueButton("Settings", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 13, 130);
		menueElements[3] = new MenueButton("<Page 2>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[4] = NULL;
		break;

		//Sub Menue Page 1:Info
	case 11:
		menueElements[0] = new MenueButton("Internal", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 11, 110);
		menueElements[1] = new MenueButton("Front", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 11, 111);
		menueElements[2] = new MenueButton("Relais", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 11, 112);
		menueElements[3] = new MenueButton("Sensor", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 11, 114);
		menueElements[4] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[5] = NULL;
		break;

		//Sub Menue Page 2: Manual
	case 12:
		menueElements[0] = new MenueButton("Relais", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 12, 120);
		menueElements[1] = new MenueButton("Water", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 12, 121);
		menueElements[2] = new MenueButton("Height", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 12, 122);
		menueElements[3] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[4] = NULL;
		break;

		//Sub Menue Page 3: Settings
	case 13:
		menueElements[0] = new MenueButton("RTC", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 13, 130);
		menueElements[1] = new MenueButton("RF Link", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 13, 131);
		menueElements[2] = new MenueButton("Func 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 13, 1);
		menueElements[3] = new MenueButton("Config", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 13, 133);
		menueElements[4] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[5] = NULL;
		break;

		//Page 2
	case 2:
		menueElements[0] = new MenueButton("<Page 1>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 0, this, true, 1, 1);
		menueElements[1] = new MenueButton("Intern", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 21, 1);
		menueElements[2] = new MenueButton("Analog", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 22, 1);
		menueElements[3] = new MenueButton("Digital", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 23, 1);
		menueElements[4] = new MenueButton("<Page 3>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 3, 1);
		menueElements[5] = NULL;
		break;

		//Time Trigger
	case 21:
		menueElements[0] = new TypedMenueButton<UserInterface>("Time", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, this, &UserInterface::setCategoryPtr, 0, true, 21, 210);
		menueElements[1] = new TypedMenueButton<UserInterface>("Temp.", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, this, &UserInterface::setCategoryPtr, 1, true, 21, 211);
		menueElements[2] = new TypedMenueButton<UserInterface>("Humid.", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, this, &UserInterface::setCategoryPtr, 2, true, 21, 211);
		menueElements[3] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[4] = NULL;
		break;


		//Analog Trigger
	case 22:
		menueElements[0] = new TypedMenueButton<UserInterface>("Front 1", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, this, &UserInterface::setCategoryPtr, 3, true, 22, 211);
		menueElements[1] = new TypedMenueButton<UserInterface>("Front 2", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, this, &UserInterface::setCategoryPtr, 4, true, 22, 211);
		menueElements[2] = new TypedMenueButton<UserInterface>("Front 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, this, &UserInterface::setCategoryPtr, 5, true, 22, 211);
		menueElements[3] = new TypedMenueButton<UserInterface>("Front 4", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, this, &UserInterface::setCategoryPtr, 6, true, 22, 211);
		menueElements[4] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[5] = NULL;
		break;
	case 23:
		menueElements[0] = new TypedMenueButton<UserInterface>("Top 1", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, this, &UserInterface::setCategoryPtr, 7, true, 23, 211);
		menueElements[1] = new TypedMenueButton<UserInterface>("Top 2", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, this, &UserInterface::setCategoryPtr, 8, true, 23, 211);
		menueElements[2] = new TypedMenueButton<UserInterface>("Top 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, this, &UserInterface::setCategoryPtr, 9, true, 23, 211);
		menueElements[3] = new TypedMenueButton<UserInterface>("Top 4", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, this, &UserInterface::setCategoryPtr, 10, true, 23, 211);
		menueElements[4] = new MenueButton("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[5] = NULL;
		break;

		//Page 3
	case 3:
		menueElements[0] = new MenueButton("<Page 2>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 0, this, true, 2, 1);
		menueElements[1] = new MenueButton("Actions", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 3, 310);
		menueElements[2] = new MenueButton("Rules", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 3, 311);
		menueElements[3] = NULL;
		break;

	case 99:
		menueElements[0] = new MenueButton("<Back>", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 1, 1);
		menueElements[1] = NULL;
		break;
	}
}
void UserInterface::drawFrame(int nav) {
	current_frame = nav;

	switch (nav) {
		// Home
	case 1:
		frameElements[0] = new TextLabel("GrowRobot V1.0", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("(c) Oliver Gass - 2017", 1, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = NULL;
		break;
		// Internal Sensors
	case 110:
		frameElements[0] = new TextLabel("Interal Sensors:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("I1:" + sensors[0]->getTitle(), 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[0]->getValue()), 2, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("I2:" + sensors[1]->getTitle(), 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[1]->getValue()), 3, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = NULL;
		break;
		// Analog / Front
	case 111:
		frameElements[0] = new TextLabel("Front Sensors:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("F1:" + sensors[2]->getTitle(), 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[2]->getValue()), 2, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("F2:" + sensors[3]->getTitle(), 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[3]->getValue()), 3, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("F3:" + sensors[4]->getTitle(), 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(sensors[4]->getValue()), 4, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("F4:" + sensors[5]->getTitle(), 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(sensors[5]->getValue()), 5, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Relais Status
	case 112: //
		bool r1, r2, r3, r4;

		r1 = (digitalRead(OUT_RELAY_1) == 1) ? false : true;
		r2 = (digitalRead(OUT_RELAY_2) == 1) ? false : true;
		r3 = (digitalRead(OUT_RELAY_3) == 1) ? false : true;
		r4 = (digitalRead(OUT_RELAY_4) == 1) ? false : true;

		frameElements[0] = new TextLabel("Relais Status:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("R1:", 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(r1), 2, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("R2:", 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(r2), 3, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("R3:", 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(r3), 4, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("R4:", 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(r4), 5, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Digital Status
	case 113:
		frameElements[0] = new TextLabel("Top Sensors:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("T1:" + sensors[6]->getTitle(), 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[6]->getValue()), 2, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("T2:" + sensors[7]->getTitle(), 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[7]->getValue()), 3, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("T3:" + sensors[8]->getTitle(), 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(sensors[8]->getValue()), 4, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("T4:" + sensors[9]->getTitle(), 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(sensors[9]->getValue()), 5, 6, 4, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
	case 114:
		frameElements[0] = new SensorGraph(sensors[this->sensor_ptr], this->daterange);
		frameElements[1] = new TypedControlButton<UserInterface>(this->getDateRange(), 9, 5, 1, 2, VGA_WHITE, VGA_BLACK, this, this, &UserInterface::changeDateRange, true, current_menue, current_frame);
		frameElements[2] = new TypedControlButton<UserInterface>("<<", 9, 7, 1, 2, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decSensorPtr, true, current_menue, current_frame);
		frameElements[3] = new TypedControlButton<UserInterface>(">>", 9, 9, 1, 2, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incSensorPtr, true, current_menue, current_frame);
		frameElements[4] = NULL;
		break;

		//Switch Relais
	case 120:
		frameElements[0] = new TextLabel("Relais", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TypedControlButton<RelaisBoard>("R1", 2, 1, 2, 2, VGA_BLUE, VGA_BLACK, this, relaisboard, &RelaisBoard::switchR1, true, 12, 120);
		frameElements[2] = new TextBox(String(relaisboard->getStatusR1()), 4, 1, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<RelaisBoard>("R2", 2, 5, 2, 2, VGA_BLUE, VGA_BLACK, this, relaisboard, &RelaisBoard::switchR2, true, 12, 120);
		frameElements[4] = new TextBox(String(relaisboard->getStatusR2()), 4, 5, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TypedControlButton<RelaisBoard>("R3", 7, 1, 2, 2, VGA_BLUE, VGA_BLACK, this, relaisboard, &RelaisBoard::switchR3, true, 12, 120);
		frameElements[6] = new TextBox(String(relaisboard->getStatusR3()), 9, 1, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TypedControlButton<RelaisBoard>("R4", 7, 5, 2, 2, VGA_BLUE, VGA_BLACK, this, relaisboard, &RelaisBoard::switchR4, true, 12, 120);
		frameElements[8] = new TextBox(String(relaisboard->getStatusR4()), 9, 5, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Switch Water Pump 
	case 121:
		frameElements[0] = new TextLabel("Water", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
		//Change Height
	case 122:
		frameElements[0] = new TextLabel("Height", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
		//Set RTC
	case 130:
		frameElements[0] = new TextLabel("Real Time Clock", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("Date", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TypedControlButton<CurrentTime>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incDay, true, 13, 130);
		frameElements[3] = new TypedControlButton<CurrentTime>("+", 1, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incMonth, true, 13, 130);
		frameElements[4] = new TypedControlButton<CurrentTime>("+", 1, 6, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incYear, true, 13, 130);
		frameElements[5] = new TextBox(String(currenttime.current_day), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(currenttime.current_month), 2, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextBox(String(currenttime.current_year), 2, 6, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[8] = new TypedControlButton<CurrentTime>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decDay, true, 13, 130);
		frameElements[9] = new TypedControlButton<CurrentTime>("-", 3, 4, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decMonth, true, 13, 130);
		frameElements[10] = new TypedControlButton<CurrentTime>("-", 3, 6, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decYear, true, 13, 130);
		frameElements[11] = new TextLabel("Time", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[12] = new TypedControlButton<CurrentTime>("+", 5, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incHour, true, 13, 130);
		frameElements[13] = new TypedControlButton<CurrentTime>("+", 5, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incMinute, true, 13, 130);
		frameElements[14] = new TextBox(String(currenttime.current_hour), 6, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[15] = new TextBox(String(currenttime.current_minute), 6, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[16] = new TypedControlButton<CurrentTime>("-", 7, 2, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decHour, true, 13, 130);
		frameElements[17] = new TypedControlButton<CurrentTime>("-", 7, 4, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decMinute, true, 13, 130);
		frameElements[18] = new TypedControlButton<CurrentTime>("Default", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, &currenttime, &CurrentTime::updateRTCdefault, true, 13, 130);
		frameElements[19] = NULL;
		break;
	case 131:
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String(rcsocketcontroller->getName()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TypedControlButton<RCSocketController>(String(rcsocketcontroller->getLearningMode()), 2, 2, 1, 8, VGA_WHITE, VGA_BLACK, this, rcsocketcontroller, &RCSocketController::switchLearningMode, true, current_menue, current_frame);
		frameElements[3] = new TypedControlButton<RCSocketController>(String("Test"), 3, 2, 1, 4, VGA_GREEN, VGA_BLACK, this, rcsocketcontroller, &RCSocketController::testSettings, true, current_menue, current_frame);
		frameElements[4] = new TypedControlButton<RCSocketController>(String("Reset"), 3, 6, 1, 4, VGA_RED, VGA_BLACK, this, rcsocketcontroller, &RCSocketController::resetSettings, true, current_menue, current_frame);

		frameElements[5] = new TextLabel("#", 5, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextLabel(String(rcsocketcontroller->getSignalPointer()), 5, 2, 5, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new TypedControlButton<RCSocketController>(String(rcsocketcontroller->getSwitchSignalText()), 5, 7, 1, 3, VGA_BLUE, VGA_WHITE, this, rcsocketcontroller, &RCSocketController::switchSignal, true, current_menue, current_frame);

		frameElements[8] = new TextLabel("Val", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[9] = new TextLabel(String(rcsocketcontroller->getDecimalKey()), 6, 2, 4, BACKGROUNDCOLOR, VGA_WHITE, this);
			
		frameElements[10] = new TextLabel("Prot", 7, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new TextLabel(String(rcsocketcontroller->getProtocol()), 7, 2, 4, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[12] = new TypedControlButton<RCSocketController>(String(rcsocketcontroller->getSwitchProtocolText()), 7, 7, 1, 3, VGA_BLUE, VGA_WHITE, this, rcsocketcontroller, &RCSocketController::switchProtocol, true, current_menue, current_frame);


		frameElements[13] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[14] = new TypedControlButton<RCSocketController>(String(rcsocketcontroller->getActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, rcsocketcontroller, &RCSocketController::switchActive, true, current_menue, current_frame);

		frameElements[15] = new TypedControlButton<RCSocketController>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, rcsocketcontroller, &RCSocketController::decCodeSet_Ptr, true, current_menue, current_frame);
		frameElements[16] = new TypedControlButton<RCSocketController>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, rcsocketcontroller, &RCSocketController::incCodeSet_Ptr, true, current_menue, current_frame);

		frameElements[17] = NULL;
		break;

	case 133:
		frameElements[0] = new TextLabel("Settings ", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("Active", 2, 0, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TypedControlButton<FileSystem>("Load", 2, 3, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::loadActiveConfig, true, 13, 133);
		frameElements[3] = new TypedControlButton<FileSystem>("Save", 2, 6, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::saveActiveConfig, true, 13, 133);
		frameElements[4] = new TextLabel("Backup", 4, 0, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[5] = new TypedControlButton<FileSystem>("Load", 4, 3, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::loadBackupConfig, true, 13, 133);
		frameElements[6] = new TypedControlButton<FileSystem>("Save", 4, 6, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::saveBackupConfig, true, 13, 133);
		frameElements[7] = new TextLabel("Default", 6, 0, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TypedControlButton<FileSystem>("Load", 6, 3, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::loadDefaultConfig, true, 13, 133);
		frameElements[9] = new TypedControlButton<FileSystem>("Save", 6, 6, 1, 3, VGA_YELLOW, VGA_BLACK, this, &filesystem, &FileSystem::saveDefaultConfig, true, 13, 133);
		frameElements[10] = new TextLabel("System", 8, 0, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new UnTypedControlButton("Reset", 8, 3, 1, 3, VGA_RED, VGA_BLACK, this, &Setting::reset, true, 13, 133);
		frameElements[12] = NULL;
		break;

		//Time
	case 210:
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String(trigger[category_ptr][trigger_ptr]->getTitle()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("From", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<Trigger>("+", 1, 2, 1, 1, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incStartDay, true, current_menue, current_frame);
		frameElements[4] = new TypedControlButton<Trigger>("+", 1, 3, 1, 1, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incStartMonth, true, current_menue, current_frame);
		frameElements[5] = new TypedControlButton<Trigger>("+", 1, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incStartYear, true, current_menue, current_frame);
		frameElements[6] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getStartDay()), 2, 2, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getStartMonth()), 2, 3, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getStartYear()), 2, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new TypedControlButton<Trigger>("-", 3, 2, 1, 1, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decStartDay, true, current_menue, current_frame);
		frameElements[10] = new TypedControlButton<Trigger>("-", 3, 3, 1, 1, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decStartMonth, true, current_menue, current_frame);
		frameElements[11] = new TypedControlButton<Trigger>("-", 3, 4, 1, 2, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decStartYear, true, current_menue, current_frame);

		frameElements[12] = new TextLabel("to", 2, 6, 1, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[13] = new TypedControlButton<Trigger>("+", 1, 7, 1, 1, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incEndDay, true, current_menue, current_frame);
		frameElements[14] = new TypedControlButton<Trigger>("+", 1, 8, 1, 1, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incEndMonth, true, current_menue, current_frame);
		frameElements[15] = new TypedControlButton<Trigger>("+", 1, 9, 1, 2, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incEndYear, true, current_menue, current_frame);
		frameElements[16] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getEndDay()), 2, 7, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[17] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getEndMonth()), 2, 8, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[18] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getEndYear()), 2, 9, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[19] = new TypedControlButton<Trigger>("-", 3, 7, 1, 1, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decEndDay, true, current_menue, current_frame);
		frameElements[20] = new TypedControlButton<Trigger>("-", 3, 8, 1, 1, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decEndMonth, true, current_menue, current_frame);
		frameElements[21] = new TypedControlButton<Trigger>("-", 3, 9, 1, 2, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decEndYear, true, current_menue, current_frame);

		frameElements[22] = new TextLabel("Time", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[23] = new TypedControlButton<Trigger>("+", 5, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incStartHour, true, current_menue, current_frame);
		frameElements[24] = new TypedControlButton<Trigger>("+", 5, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incStartMinute, true, current_menue, current_frame);
		frameElements[25] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getStartHour()), 6, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[26] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getStartMinute()), 6, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[27] = new TypedControlButton<Trigger>("-", 7, 2, 1, 2, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decStartHour, true, current_menue, current_frame);
		frameElements[28] = new TypedControlButton<Trigger>("-", 7, 4, 1, 2, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decStartMinute, true, current_menue, current_frame);

		frameElements[29] = new TextLabel("Int.", 6, 6, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[30] = new TypedControlButton<Trigger>("+", 5, 8, 1, 3, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incInterval, true, current_menue, current_frame);
		frameElements[31] = new TextBox(String(trigger[category_ptr][trigger_ptr]->getInterval()), 6, 8, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[32] = new TypedControlButton<Trigger>("-", 7, 8, 1, 3, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decInterval, true, current_menue, current_frame);

		frameElements[33] = new TextLabel("Stat.", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[34] = new TypedControlButton<Trigger>(String(trigger[category_ptr][trigger_ptr]->getActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, trigger[category_ptr][trigger_ptr], &Trigger::changeActive, true, current_menue, current_frame);

		frameElements[35] = new TypedControlButton<UserInterface>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decTriggerPtr, true, current_menue, current_frame);
		frameElements[36] = new TypedControlButton<UserInterface>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incTriggerPtr, true, current_menue, current_frame);

		frameElements[37] = NULL;
		break;

		//Sensor Trigger
	case 211:
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((trigger[category_ptr][trigger_ptr]->getTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<Trigger>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incRelOp, true, current_menue, current_frame);
		frameElements[4] = new TextBox(String((trigger[category_ptr][trigger_ptr]->getRelOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TypedControlButton<Trigger>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decRelOp, true, current_menue, current_frame);

		frameElements[6] = new TextLabel(" ", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new TypedControlButton<Trigger>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incThresh, true, current_menue, current_frame);
		frameElements[8] = new TextBox(String((trigger[category_ptr][trigger_ptr]->getThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new TypedControlButton<Trigger>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decThresh, true, current_menue, current_frame);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new TypedControlButton<Trigger>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::incInterval, true, current_menue, current_frame);
		frameElements[12] = new TextBox(String((trigger[category_ptr][trigger_ptr]->getInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new TypedControlButton<Trigger>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, trigger[category_ptr][trigger_ptr], &Trigger::decInterval, true, current_menue, current_frame);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new TypedControlButton<Trigger>(String(trigger[category_ptr][trigger_ptr]->getActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, trigger[category_ptr][trigger_ptr], &Trigger::changeActive, true, current_menue, current_frame);

		frameElements[16] = new TypedControlButton<UserInterface>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decTriggerPtr, true, current_menue, current_frame);
		frameElements[17] = new TypedControlButton<UserInterface>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incTriggerPtr, true, current_menue, current_frame);

		frameElements[18] = NULL;
		break;

		//Actionchains
	case 310:
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String(actionchains[action_ptr]->getTitle()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		//Only three Actions for Testing on small display
		frameElements[2] = new TextLabel("1:", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction1()), 2, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction1, true, current_menue, current_frame);
		frameElements[4] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar1()), 2, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar1, true, current_menue, current_frame);

		frameElements[5] = new TextLabel("2:", 4, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction2()), 4, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction2, true, current_menue, current_frame);
		frameElements[7] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar2()), 4, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar2, true, current_menue, current_frame);

		frameElements[8] = new TextLabel("3:", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[9] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction3()), 6, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction3, true, current_menue, current_frame);
		frameElements[10] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar3()), 6, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar3, true, current_menue, current_frame);

		frameElements[11] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[12] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changeChainActive, true, current_menue, current_frame);

		frameElements[13] = new TypedControlButton<UserInterface>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decActionPtr, true, current_menue, current_frame);
		frameElements[14] = new TypedControlButton<UserInterface>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incActionPtr, true, current_menue, current_frame);

		frameElements[15] = NULL;

		/*
		frameElements[2] = new TextLabel("1:", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction1()), 2, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction1, true, current_menue, current_frame);
		frameElements[4] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar1()), 2, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar1, true, current_menue, current_frame);

		frameElements[5] = new TextLabel("2:", 3, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction2()), 3, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction2, true, current_menue, current_frame);
		frameElements[7] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar2()), 3, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar2, true, current_menue, current_frame);

		frameElements[8] = new TextLabel("3:", 4, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[9] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction3()), 4, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction3, true, current_menue, current_frame);
		frameElements[10] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar3()), 4, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar3, true, current_menue, current_frame);


		frameElements[11] = new TextLabel("4:", 5, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[12] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction4()), 5, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction4, true, current_menue, current_frame);
		frameElements[13] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar4()), 5, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar4, true, current_menue, current_frame);

		frameElements[14] = new TextLabel("5:", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction5()), 6, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction5, true, current_menue, current_frame);
		frameElements[16] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar5()), 6, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar5, true, current_menue, current_frame);

		frameElements[17] = new TextLabel("6:", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[18] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainAction6()), 7, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, actionchains[action_ptr], &ActionChain::changeAction6, true, current_menue, current_frame);
		frameElements[19] = new TypedControlButton<ActionChain>(String(actionchains[action_ptr]->getChainPar6()), 7, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, actionchains[action_ptr], &ActionChain::changePar6, true, current_menue, current_frame);

		frameElements[20] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[21] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetActive, true, current_menue, current_frame);

		frameElements[22] = new TypedControlButton<UserInterface>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decActionPtr, true, current_menue, current_frame);
		frameElements[23] = new TypedControlButton<UserInterface>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incActionPtr, true, current_menue, current_frame);

		frameElements[24] = NULL;
		*/
		break;

		//Rules Set
	case 311:
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String(rulesets[ruleset_ptr]->getTitle()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("If", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetTrigger1()), 2, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetTrigger1, true, current_menue, current_frame);
		frameElements[4] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetBoolOp1()), 2, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetBoolOp1, true, current_menue, current_frame);
		
		frameElements[5] = new TextLabel("If", 3, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetTrigger2()), 3, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetTrigger2, true, current_menue, current_frame);
		frameElements[7] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetBoolOp2()), 3, 9, 1, 2, VGA_BLUE, VGA_WHITE, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetBoolOp2, true, current_menue, current_frame);

		frameElements[8] = new TextLabel("If", 4, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[9] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetTrigger3()), 4, 2, 1, 6, VGA_WHITE, VGA_BLACK, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetTrigger3, true, current_menue, current_frame);
		
		frameElements[10] = new TextLabel("Run", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetChain()), 6, 2, 1, 6, VGA_RED, VGA_BLACK, this, rulesets[ruleset_ptr], &RuleSet::changeRuleChain, true, current_menue, current_frame);
		
		frameElements[12] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[13] = new TypedControlButton<RuleSet>(String(rulesets[ruleset_ptr]->getRuleSetActive()), 9, 2, 1, 2, VGA_BLUE, VGA_WHITE, this, rulesets[ruleset_ptr], &RuleSet::changeRuleSetActive, true, current_menue, current_frame);

		frameElements[14] = new TypedControlButton<UserInterface>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::decRulesetPtr, true, current_menue, current_frame);
		frameElements[15] = new TypedControlButton<UserInterface>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, this, &UserInterface::incRulesetPtr, true, current_menue, current_frame);

		frameElements[16] = NULL;
		break;
	}
}
void UserInterface::checkEvent(int x, int y) {
	int i = 0, targetmenue = 1, targetframe = 1, hit = false;

	//Check if Menue Element was hit
	while (menueElements[i] != NULL && hit == false) {
		if (menueElements[i]->checkHit(x, y) == true) {
			
			menueElements[i]->executeAction();
			targetmenue = menueElements[i]->navmenue;
			targetframe = menueElements[i]->navframe;
			hit = true;
			break;
		}
		else i++;
	}
	i = 0;
	//Check if Frame Element was hit
	while (frameElements[i] != NULL && hit == false) {
		if (frameElements[i]->checkHit(x, y) == true) {

			frameElements[i]->executeAction();
			targetmenue = frameElements[i]->navmenue;
			targetframe = frameElements[i]->navframe;
			hit = true;
			break;
		}
		else {
			i++;
		}
	}

	if (hit == true) {
		draw(targetmenue, targetframe);
	}
}

String UserInterface::getDateRange()
{
	String label;

	switch (this->daterange) {
	case MINUTE:
		label = "Min";
		break;
	case HOUR:
		label = "Hour";
		break;
	case DAY:
		label = "Day";
		break;
	case MONTH:
		label = "Month";
		break;
	case YEAR:
		label = "Year";
		break;
	}

	return String(label);
}

void UserInterface::cleanup() {
	//Iterator
	int i;

	i = 0;
	//Delete Old Menue Buttons
	while (menueElements[i] != NULL) {
		delete menueElements[i];
		i++;
	}
	//Delete Frame User Interface
	i = 0;
	while (frameElements[i] != NULL) {
		delete frameElements[i];
		i++;
	}

}
