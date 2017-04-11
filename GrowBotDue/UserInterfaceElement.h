// UserInterfaceElement.h

#ifndef _USERINTERFACEELEMENT_h
#define _USERINTERFACEELEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <UTouch.h>
#include <UTouchCD.h>
#include <UTFT.h>
#include "Definitions.h"
#include "UserInterface.h"

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


class UserInterface;

class UserInterfaceElement {
public:
	//Referenz to Touch Menue
	UserInterface *touchmenue;
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

class TextLabel : public UserInterfaceElement {
public:
	TextLabel(String value, uint8_t row, uint8_t column, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, bool active = false, int navmenue = 1, int navframe = 1);

	void draw();
};

class TextBox : public UserInterfaceElement {
public:
	TextBox(String value, uint8_t row, uint8_t column, uint8_t column_spread, word frame_color, word text_color, UserInterface *touchmenue, bool active = false, int navmenue = 1, int navframe = 1);
	void draw();
};


class MenueButton : public UserInterfaceElement {
public:
	MenueButton(String value, word frame_color, word fill_color, word text_color, uint8_t row, UserInterface *touchmenue, bool active = true, int navmenue = 999, int navframe = 999);

	void draw();
};


template <class ActionType>
class TypedMenueButton : public UserInterfaceElement {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)(int);
	int parameter;
		
	TypedMenueButton(String value, word frame_color, word fill_color, word text_color, uint8_t row, UserInterface *touchmenue, ActionType *actionObj, void (ActionType::*actionFunc)(int), int par, bool active = true, int navmenue = 1, int navframe = 1);
	
	void draw();
	void executeAction();
};

class ControlButton : public UserInterfaceElement {
public:
	ControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, bool active = true, int navmenue = 999, int navframe = 999);
	void draw();
};

class UnTypedControlButton : public ControlButton {
public:
	void (*callback)() = NULL;

	UnTypedControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, void (*actionFunc)(), bool active = true, int navmenue = 999, int navframe = 999);

	void executeAction();
};

template <class ActionType>
class TypedControlButton : public ControlButton {

public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)() = NULL;

	TypedControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, ActionType *actionObj, void (ActionType::*actionFunc)(), bool active = true, int navmenue = 999, int navframe = 999);

	void executeAction();
};


class SensorGraph : public UserInterfaceElement {
public:
	Sensor *sensor_ptr;
	DateRange range;

	short getMaxValue(DateRange range);
	short getMinValue(DateRange range);
	float getXMultiplier(DateRange range);
	float getYMultiplier(short min, short max);

	void drawGraph(DateRange range);

	void drawValue(uint8_t counter, short value, float x_multiplier, float y_multiplier, short base);

	SensorGraph(Sensor *sensor_ptr, DateRange range);
};

#endif

