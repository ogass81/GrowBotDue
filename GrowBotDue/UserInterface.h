// UserInterface.h

#ifndef _USERINTERFACE_h
#define _USERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "CurrentTime.h"
#include "Sensor.h"
#include "Relais.h"
#include "RulesEngine.h"
#include <UTouch.h>
#include <UTouchCD.h>
#include <UTFT.h>

//UI Variables
extern int touch_x, touch_y;

extern uint8_t BigFont[];
extern uint8_t SmallFont[];

extern int color;
extern word colorlist[];
extern int  bsize;
extern bool unit;
extern String debug;

extern UTFT myGLCD;
extern UTouch myTouch;

//Time
extern CurrentTime currenttime;
//Sensors
extern Sensor *sensors[SENSNUMBER];
//Relais
extern RelaisBoard relaisboard;

extern RulesEngine *rulesengine;

class TouchInterface;

class UserInterfaceElement {
public:
	//Referenz to Touch Menue
	TouchInterface *touchmenue;
	int navmenue, navframe;

	int x1, x2, y1, y2;
	uint8_t row, column, row_spread, column_spread;
	word frame_color, text_color, fill_color;
	String value;

	bool active;

	UserInterfaceElement();
	~UserInterfaceElement();


	bool checkHit(int x, int y);

	void draw();

	virtual void executeAction();
};

class MenueItem : public UserInterfaceElement {
public:
	MenueItem(String value, word frame_color, word fill_color, word text_color, uint8_t row, TouchInterface *touchmenue, bool active = true, int navmenue = 999, int navframe = 999);

	void draw();
};

class TextLabel : public UserInterfaceElement {
public:
	TextLabel(String value, uint8_t row, uint8_t column, uint8_t column_spread, word fill_color, word text_color, TouchInterface *touchmenue, bool active = false, int navmenue = 999, int navframe = 999);

	void draw();
};

class TextBox : public UserInterfaceElement {
public:
	TextBox(String value, uint8_t row, uint8_t column, uint8_t column_spread, word frame_color, word text_color, TouchInterface *touchmenue, bool active = false, int navmenue = 999, int navframe = 999);
	void draw();
};

template <class T>
class ControlButton : public UserInterfaceElement {

public:
	T *actionObject = NULL;
	void (T::*callback)();

	ControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, TouchInterface *touchmenue, T *actionObj, void (T::*actionFunc)(), bool active = true, int navmenue = 999, int navframe = 999);
	void draw();
	void executeAction();
};


class TouchInterface {
public:
	UserInterfaceElement *menueElements[6];
	UserInterfaceElement *frameElements[47];

	int current_menue, current_frame;

	TouchInterface();
	void drawBackground();

	void drawMenue(int nav);
	void drawFrame(int nav);
	void checkEvent(int x, int y);

	void cleanup();
};

#endif

