// 
// 
// 

#include "UserInterfaceElement.h"

void UserInterfaceElement::draw() {
	//Overwrite
}

UserInterfaceElement::UserInterfaceElement() {
	//Overwrite
}
UserInterfaceElement::~UserInterfaceElement() {

}
void UserInterfaceElement::executeAction() {

}

bool UserInterfaceElement::checkHit(int x, int y) {
	//Current Navpoints, need to be stored temporaley while objects are destroyed
	int navmenue, navframe;

	if (x >= this->x1 && x <= this->x2 && y >= this->y1 && y <= this->y2 && this->active == true) {
		return true;
	}
	else return false;
}

TextLabel::TextLabel(String value, uint8_t row, uint8_t column, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->row_spread = column_spread;
	this->column_spread = column_spread;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = UI_X_DIVIDER + column * UI_COLUMN_WIDTH + UI_PADDING;
	this->y1 = UI_Y_DIVIDER + row * UI_ROW_HEIGHT + UI_PADDING;
	this->x2 = x1 + column_spread * UI_COLUMN_WIDTH - UI_PADDING;
	this->y2 = y1 + UI_ROW_HEIGHT - UI_PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	draw();
}
void TextLabel::draw() {
	myGLCD.setFont(SmallFont);
	myGLCD.setBackColor(fill_color);
	myGLCD.setColor(text_color);
	myGLCD.print(value, x1 + 3, y1 + 3);
}

TextBox::TextBox(String value, uint8_t row, uint8_t column, uint8_t column_spread, word frame_color, word text_color, UserInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and Feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->column_spread = column_spread;
	this->frame_color = frame_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = UI_X_DIVIDER + column * UI_COLUMN_WIDTH + UI_PADDING;
	this->y1 = UI_Y_DIVIDER + row * UI_ROW_HEIGHT + UI_PADDING;
	this->x2 = x1 + column_spread * UI_COLUMN_WIDTH - UI_PADDING;
	this->y2 = y1 + UI_ROW_HEIGHT - UI_PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	draw();
}
void TextBox::draw() {
	myGLCD.setFont(SmallFont);
	myGLCD.setColor(this->frame_color);
	myGLCD.drawRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(BACKGROUNDCOLOR);
	myGLCD.setColor(this->text_color);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

MenueButton::MenueButton(String value, word frame_color, word fill_color, word text_color, uint8_t row, UserInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and Feel
	this->value = value;
	this->row = row;
	this->frame_color = frame_color;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;

	this->x1 = 0;
	this->y1 = UI_Y_DIVIDER + row * UI_MENUE_HEIGHT;
	this->x2 = UI_X_DIVIDER;
	this->y2 = y1 + UI_MENUE_HEIGHT;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	draw();
}
void MenueButton::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setColor(this->frame_color);
	myGLCD.drawRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

template<class ActionType>
TypedMenueButton<ActionType>::TypedMenueButton(String value, word frame_color, word fill_color, word text_color, uint8_t row, UserInterface * touchmenue, ActionType * actionObj, void(ActionType::* actionFunc)(int), int par, bool active, int navmenue, int navframe)
{
	//Look and Feel
	this->value = value;
	this->row = row;
	this->frame_color = frame_color;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;

	this->x1 = 0;
	this->y1 = UI_Y_DIVIDER + row * UI_MENUE_HEIGHT;
	this->x2 = UI_X_DIVIDER;
	this->y2 = y1 + UI_MENUE_HEIGHT;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	//Callback
	this->actionObject = actionObj;
	this->callback = actionFunc;
	this->active = active;
	this->parameter = par;

	draw();
}

template<class ActionType>
void TypedMenueButton<ActionType>::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setColor(this->frame_color);
	myGLCD.drawRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

template<class ActionType>
void TypedMenueButton<ActionType>::executeAction()
{
	if (active == true && actionObject != NULL) {
		(actionObject->*callback)(parameter);
	}
	else Serial.println("FAIL: Button has no action");
}

ControlButton::ControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface * touchmenue, bool active, int navmenue, int navframe)
{
	this->active = active;
	
	//Look and Feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->row_spread = row_spread;
	this->column_spread = column_spread;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = UI_X_DIVIDER + column * UI_COLUMN_WIDTH + UI_PADDING;
	this->y1 = UI_Y_DIVIDER + row * UI_ROW_HEIGHT + UI_PADDING;
	this->x2 = x1 + column_spread * UI_COLUMN_WIDTH - UI_PADDING;
	this->y2 = y1 + row_spread * UI_ROW_HEIGHT - UI_PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;
}


void ControlButton::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRoundRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

UnTypedControlButton::UnTypedControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface * touchmenue, void(* actionFunc)(), bool active, int navmenue, int navframe) 
	: ControlButton(value, row, column, row_spread, column_spread, fill_color, text_color, touchmenue, active, navmenue, navframe) {

	//Action Handler
	this->callback = actionFunc;

	draw();
}

void UnTypedControlButton::executeAction()
{
	if (active == true) {
		if (callback != NULL) {
			callback();
		}
		else LOGDEBUG(F("[TypedControlButton]"), F("execute()"), F("ERROR: Button has no Action assigned"), F("Title"), String(value), "");
	}
}


template <class ActionType>
TypedControlButton<ActionType>::TypedControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, ActionType *actionObj, void (ActionType::*actionFunc)(), bool active, int navmenue, int navframe)
	: ControlButton(value, row, column, row_spread, column_spread, fill_color, text_color, touchmenue, active, navmenue, navframe) {

	//Action Handler
	this->actionObject = actionObj;
	this->callback = actionFunc;

	draw();
}

template <class ActionType>
void TypedControlButton<ActionType>::executeAction() {
	if (active == true) {
		if (actionObject != NULL && callback != NULL) {
			(actionObject->*callback)();
		}
		else LOGDEBUG(F("[TypedControlButton]"), F("execute()"), F("ERROR: Button has no Action assigned"), F("Title"), String(value), "");
	}
}


SensorGraph::SensorGraph(Sensor *sensor_ptr, DateRange range) {
	this->sensor_ptr = sensor_ptr;
	drawGraph(range);
}

short SensorGraph::getMaxValue(DateRange range)
{
	short max = -32767;

	switch (range) {

	case MINUTE:
		for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) {
			if (sensor_ptr->minute_values[i] > max) max = sensor_ptr->minute_values[i];
		}
		break;
	
	case HOUR:
		for (uint8_t i = 0; i < SENS_VALUES_HOUR ; i++) {
			if (sensor_ptr->hour_values[i] > max) max = sensor_ptr->hour_values[i];
		}
		break;
		
	case DAY:
		for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) {
			if (sensor_ptr->day_values[i] > max) max = sensor_ptr->day_values[i];
		}
		break;
		
	case MONTH:
		for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) {
			if (sensor_ptr->month_values[i] > max) max = sensor_ptr->month_values[i];
		}
		break;
		
	case YEAR:
		for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) {
			if (sensor_ptr->year_values[i] > max) max = sensor_ptr->year_values[i];
		}
		break;
	}
	LOGDEBUG(F("[SensorGraph]"), F("getMaxValue()"), F("OK: Maximum value in Sensor data"), String(max), "", "");

	return max;
}

short SensorGraph::getMinValue(DateRange range)
{
	short min = 32767;

	switch (range) {

	case MINUTE:
		for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) {
			if (sensor_ptr->minute_values[i] < min) min = sensor_ptr->minute_values[i];
		}
		break;

	case HOUR:
		for (uint8_t i = 0; i < SENS_VALUES_HOUR ; i++) {
			if (sensor_ptr->hour_values[i] < min) min = sensor_ptr->hour_values[i];
		}
		break;
		
	case DAY:
		for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) {
			if (sensor_ptr->day_values[i] < min) min = sensor_ptr->day_values[i];
		}
		break;
		
	case MONTH:
		for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) {
			if (sensor_ptr->month_values[i] < min) min = sensor_ptr->month_values[i];
		}
		break;
		
	case YEAR:
		for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) {
			if (sensor_ptr->year_values[i] < min) min = sensor_ptr->year_values[i];
		}
		break;
	}
	LOGDEBUG(F("[SensorGraph]"), F("getMinValue()"), F("OK: Minimum value in Sensor data"), String(min), "", "");

	return min;
}

float SensorGraph::getXMultiplier(DateRange range)
{
	float multiplier;

	switch (range) {

	case MINUTE:
		multiplier = (320 - UI_X_DIVIDER - 4 * UI_PADDING) / SENS_VALUES_MIN;
		break;

	case HOUR:
		multiplier = (320 - UI_X_DIVIDER - 4 * UI_PADDING) / SENS_VALUES_HOUR ;
		break;

	case DAY:
		multiplier = (320 - UI_X_DIVIDER - 4 * UI_PADDING) / SENS_VALUES_DAY;
		break;

	case MONTH:
		multiplier = (320 - UI_X_DIVIDER - 4 * UI_PADDING) / SENS_VALUES_MONTH;
		break;

	case YEAR:
		multiplier = (320 - UI_X_DIVIDER - 4 * UI_PADDING) / SENS_VALUES_YEAR;
		break;

	}
	LOGDEBUG(F("[SensorGraph]"), F("getXMultiplier()"), F("OK: X Multiplier"), String(multiplier), "", "");

	return (float) multiplier;
}

float SensorGraph::getYMultiplier(short min, short max)
{
	short range;
	float multiplier;

	if (max > 0 && min < 0) {
		range = max + abs(min);
	}
	else if (max < 0 && min < 0) {
		range = abs(min);
	}
	else if (max > 0 && min > 0) {
		range = abs(max);
	}
	else {
		Serial.println("Error: Range 0");
		range = 0;
	}

	if (range > 0) {
		multiplier = (float)(240 - UI_Y_DIVIDER - 2 * UI_PADDING) / (float)range;
	}
	else multiplier = 0;
	
	Serial.print("Range:");
	Serial.println(range);
	Serial.print("Y-Multiplier:");
	Serial.println(multiplier);
	
	LOGDEBUG(F("[SensorGraph]"), F("getYMultiplier()"), F("OK: Y Multiplier"), String(multiplier), String(range), "");
	
	return (float)multiplier; 
}

void SensorGraph::drawValue(uint8_t counter, short value, float x_multiplier, float y_multiplier, short base)
{
	short x1, x2, y1, y2;
	
	if (value < 0 && value > -32768) {
		x1 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)(counter * x_multiplier);
		y1 = base;
		x2 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = (short)(base - value * y_multiplier);
	}
	else if (value >= 0) {
		x1 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)(counter * x_multiplier);
		y1 = (short)(base - value * y_multiplier);
		x2 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = base;
	}
	else {
		x1 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)(counter * x_multiplier);
		y1 = base;
		x2 = (UI_X_DIVIDER + 2 * UI_PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = base;
	}

	myGLCD.fillRect(x1, y1, x2, y2);
}

void SensorGraph::drawGraph(DateRange range)
{
	short base;
	String label;
	
	short min = getMinValue(range);
	short max = getMaxValue(range);
	float x_multiplier = getXMultiplier(range);
	float y_multiplier = getYMultiplier(min, max);


	if (max < 0 || min < 0) {
		base = 240 - UI_PADDING + min * y_multiplier;
	}
	else {
		base = 240 - UI_PADDING;
	}

	LOGDEBUG(F("[SensorGraph]"), F("drawGraph()"), F("OK: Baseline"), String(base), "", "");
	
	switch (range) {

	case MINUTE:
		for (uint8_t i = 0; i < SENS_VALUES_MIN; i++) {
			myGLCD.setColor(VGA_RED);
			drawValue(i, sensor_ptr->minute_values[i], x_multiplier, y_multiplier, base);
			
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i > 0) myGLCD.print(String(i*5), UI_X_DIVIDER + 5 * UI_PADDING + i * x_multiplier, base - 12);
			}
			else {
				if (i > 0) myGLCD.print(String(i*5), UI_X_DIVIDER + 5 * UI_PADDING + i * x_multiplier, base + 12);
			}
		}
		
		break;

	case HOUR:
		for (uint8_t i = 0; i < SENS_VALUES_HOUR ; i++) {
			myGLCD.setColor(VGA_FUCHSIA);
			drawValue(i, sensor_ptr->hour_values[i], x_multiplier, y_multiplier, base);
			
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i  % 15 == 0) myGLCD.print(String(i), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i %  15 == 0) myGLCD.print(String(i), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		}
		break;

	case DAY:

		for (uint8_t i = 0; i < SENS_VALUES_DAY; i++) {
			myGLCD.setColor(VGA_LIME);
			drawValue(i, sensor_ptr->day_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 8 == 0) myGLCD.print(String(i/4), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 8 == 0) myGLCD.print(String(i/4), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		}
		break;

	case MONTH:
		for (uint8_t i = 0; i < SENS_VALUES_MONTH; i++) {
			myGLCD.setColor(VGA_BLUE);
			drawValue(i, sensor_ptr->month_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 14 == 0) myGLCD.print(String(i / 14), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 14 == 0) myGLCD.print(String(i / 14), UI_X_DIVIDER + 5 * UI_PADDING + (i-1) * x_multiplier, base + 12);
			}
		}
		break;

	case YEAR:
		for (uint8_t i = 0; i < SENS_VALUES_YEAR; i++) {
			myGLCD.setColor(VGA_RED);
			drawValue(i, sensor_ptr->year_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 12 == 0) myGLCD.print(String(i / 12), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 12 == 0) myGLCD.print(String(i / 12), UI_X_DIVIDER + 5 * UI_PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		
		}
		break;
	}


	//Draw Axis
	myGLCD.setColor(VGA_WHITE);
	myGLCD.setBackColor(VGA_TRANSPARENT);
	myGLCD.drawLine(UI_X_DIVIDER + UI_PADDING, base, 320 - UI_PADDING, base);
	myGLCD.drawLine(UI_X_DIVIDER + 2 * UI_PADDING, UI_Y_DIVIDER + UI_PADDING, UI_X_DIVIDER + 2 * UI_PADDING, 240 - UI_PADDING);

	//Labels
	if (base > 120) {
		label = "0";
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, UI_X_DIVIDER + 3 * UI_PADDING, base - 12);
	} 
	else {
		label = "0";
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, UI_X_DIVIDER + 3 * UI_PADDING, base + 12);
	}

	//Labels
	if (max > 0 && base > 60) {
		label = "Max:";
		label += (String)max;
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, UI_X_DIVIDER + 3 * UI_PADDING, UI_Y_DIVIDER + UI_PADDING);
	}
	//Min
	if (min < 0 && base < 180 ) {
		label = "Min:";
		label += (String)min;
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, UI_X_DIVIDER + 3 * UI_PADDING, 240 - 12 - UI_PADDING);
	}
}


//All Types of Templates used:
template class TypedMenueButton<Trigger>;
template class TypedMenueButton<RuleSet>;
template class TypedMenueButton<UserInterface>;

template class TypedControlButton<RelaisBoard>;
template class TypedControlButton<CurrentTime>;
template class TypedControlButton<RuleSet>;
template class TypedControlButton<UserInterface>;
template class TypedControlButton<Trigger>;
template class TypedControlButton<FileSystem>;
template class TypedControlButton<ActionChain>;
template class TypedControlButton<RFController>;