// UserInterface.h

#ifndef _USERINTERFACE_h
#define _USERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <UTouch.h>
#include <UTouchCD.h>
#include <UTFT.h>

#include "Definitions.h"
#include "CurrentTime.h"
#include "Sensor.h"
#include "Relais.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "ActionChain.h"
#include "UserInterfaceElement.h"
#include "FileSystem.h"
#include "Setting.h"
#include "RFController.h";

//UI Variables
extern int touch_x, touch_y;

extern uint8_t BigFont[];
extern uint8_t SmallFont[];

extern int color;
extern word colorlist[];
extern int  bsize;
extern bool unit;

extern UTFT myGLCD;
extern UTouch myTouch;

extern FileSystem filesystem;

//Time
extern CurrentTime currenttime;
//Sensors
extern Sensor *sensors[SENS_NUM];
//Relais
extern RelaisBoard *relaisboard;

extern Trigger *trigger[TRIGGER_TYPES][TRIGGER_SETS];

extern RuleSet *rulesets[RULESETS_NUM];

extern ActionChain *actionchains[ACTIONCHAINS_NUM];

extern RFController *rfcontroller;


//Vordeklariert
class UserInterfaceElement;

class UserInterface {
public:
	UserInterfaceElement *menueElements[6];
	UserInterfaceElement *frameElements[47];

	int current_menue, current_frame, sensor_ptr = 0, trigger_ptr = 0, category_ptr = 0, ruleset_ptr = 0, action_ptr = 0;
	DateRange daterange;

	UserInterface();

	void inCategoryPtr();
	void decCategoryPtr();
	void setCategoryPtr(int i);

	void incSensorPtr();
	void decSensorPtr();

	void changeDateRange();
	
	void incTriggerPtr();
	void decTriggerPtr();

	void incRulesetPtr();
	void decRulesetPtr();

	void incActionPtr();
	void decActionPtr();
		
	void draw();
	void draw(int targetmenue, int targetframe);
	void drawBackground();
	void drawMenue(int nav);
	void drawFrame(int nav);
	void checkEvent(int x, int y);

	String getDateRange();

	void cleanup();
};

#endif

