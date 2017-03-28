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
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + ROW_HEIGHT - PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	draw();

}
void TextLabel::draw() {
	myGLCD.setFont(SmallFont);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
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
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + ROW_HEIGHT - PADDING;

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
	this->y1 = Y_DIVIDER + row * MENUE_HEIGHT;
	this->x2 = X_DIVIDER;
	this->y2 = y1 + MENUE_HEIGHT;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	this->draw();

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
MenueControlButton<ActionType>::MenueControlButton(String value, word frame_color, word fill_color, word text_color, uint8_t row, UserInterface * touchmenue, ActionType * actionObj, void(ActionType::* actionFunc)(int), int par, bool active, int navmenue, int navframe)
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
	this->y1 = Y_DIVIDER + row * MENUE_HEIGHT;
	this->x2 = X_DIVIDER;
	this->y2 = y1 + MENUE_HEIGHT;

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
void MenueControlButton<ActionType>::draw() {
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
void MenueControlButton<ActionType>::executeAction()
{
	if (this->active == true && this->actionObject != NULL) {
		(actionObject->*callback)(parameter);
	}
	else Serial.println("FAIL: Button has no action");
}


template <class ActionType>
ControlButton<ActionType>::ControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, UserInterface *touchmenue, ActionType *actionObj, void (ActionType::*actionFunc)(), bool active, int navmenue, int navframe) {
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
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + row_spread * ROW_HEIGHT - PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	//Action Handler
	this->actionObject = actionObj;
	this->callback = actionFunc;
	this->active = active;

	draw();
}

template <class ActionType>
void ControlButton<ActionType>::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRoundRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

template <class ActionType>
void ControlButton<ActionType>::executeAction() {
	if (this->active == true && this->actionObject != NULL && this->callback != NULL) {
		(actionObject->*callback)();
	}
	else Serial.println("FAIL: Button has no action");
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
		for (uint8_t i = 0; i < NUMMINUTE; i++) {
			if (sensor_ptr->minute_values[i] > max) max = sensor_ptr->minute_values[i];
		}
		break;
	
	case HOUR:
		for (uint8_t i = 0; i < NUMHOUR; i++) {
			if (sensor_ptr->hour_values[i] > max) max = sensor_ptr->hour_values[i];
		}
		break;
		
	case DAY:
		for (uint8_t i = 0; i < NUMDAY; i++) {
			if (sensor_ptr->day_values[i] > max) max = sensor_ptr->day_values[i];
		}
		break;
		
	case MONTH:
		for (uint8_t i = 0; i < NUMMONTH; i++) {
			if (sensor_ptr->month_values[i] > max) max = sensor_ptr->month_values[i];
		}
		break;
		
	case YEAR:
		for (uint8_t i = 0; i < NUMYEAR; i++) {
			if (sensor_ptr->year_values[i] > max) max = sensor_ptr->year_values[i];
		}
		break;
	}
	Serial.print("Max Value:");
	Serial.println(max);
	return max;
}

short SensorGraph::getMinValue(DateRange range)
{
	short min = 32767;

	switch (range) {

	case MINUTE:
		for (uint8_t i = 0; i < NUMMINUTE; i++) {
			if (sensor_ptr->minute_values[i] < min) min = sensor_ptr->minute_values[i];
		}
		break;

	case HOUR:
		for (uint8_t i = 0; i < NUMHOUR; i++) {
			if (sensor_ptr->hour_values[i] < min) min = sensor_ptr->hour_values[i];
		}
		break;
		
	case DAY:
		for (uint8_t i = 0; i < NUMDAY; i++) {
			if (sensor_ptr->day_values[i] < min) min = sensor_ptr->day_values[i];
		}
		break;
		
	case MONTH:
		for (uint8_t i = 0; i < NUMMONTH; i++) {
			if (sensor_ptr->month_values[i] < min) min = sensor_ptr->month_values[i];
		}
		break;
		
	case YEAR:
		for (uint8_t i = 0; i < NUMYEAR; i++) {
			if (sensor_ptr->year_values[i] < min) min = sensor_ptr->year_values[i];
		}
		break;
	}
	Serial.print("Min Value:");
	Serial.println(min);
	return min;
}

float SensorGraph::getXMultiplier(DateRange range)
{
	float multiplier;

	switch (range) {

	case MINUTE:
		multiplier = (320 - X_DIVIDER - 4 * PADDING) / NUMMINUTE;
		break;

	case HOUR:
		multiplier = (320 - X_DIVIDER - 4 * PADDING) / NUMHOUR;
		break;

	case DAY:
		multiplier = (320 - X_DIVIDER - 4 * PADDING) / NUMDAY;
		break;

	case MONTH:
		multiplier = (320 - X_DIVIDER - 4 * PADDING) / NUMMONTH;
		break;

	case YEAR:
		multiplier = (320 - X_DIVIDER - 4 * PADDING) / NUMYEAR;
		break;

	}
	Serial.print("X-Multiplier:");
	Serial.println(multiplier);

	return (float) multiplier;
}

float SensorGraph::getYMultiplier(short min, short max)
{
	short range;
	float multiplier;

	Serial.print("Min Function:");
	Serial.println(min);
	Serial.print("Max Function:");
	Serial.println(max);

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
		multiplier = (float)(240 - Y_DIVIDER - 2 * PADDING) / (float)range;
	}
	else multiplier = 0;
	
	Serial.print("Range:");
	Serial.println(range);
	Serial.print("Y-Multiplier:");
	Serial.println(multiplier);
	
	return (float)multiplier; 
}

void SensorGraph::drawValue(uint8_t counter, short value, float x_multiplier, float y_multiplier, short base)
{
	short x1, x2, y1, y2;
	
	Serial.println("------------------------------------");
	Serial.print("Counter:");
	Serial.println(counter);
	Serial.print("Value");
	Serial.println(value);

	
	if (value < 0 && value > -32768) {
		x1 = (X_DIVIDER + 2 * PADDING) + (short)(counter * x_multiplier);
		y1 = base;
		x2 = (X_DIVIDER + 2 * PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = (short)(base - value * y_multiplier);
		//myGLCD.drawLine(x1 - 1, y2, x1 + 1, y2);
	}
	else if (value >= 0) {
		x1 = (X_DIVIDER + 2 * PADDING) + (short)(counter * x_multiplier);
		y1 = (short)(base - value * y_multiplier);
		x2 = (X_DIVIDER + 2 * PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = base;
		//myGLCD.drawLine(x1 - 1, y1, x1 + 1, y1);
	}
	else {
		x1 = (X_DIVIDER + 2 * PADDING) + (short)(counter * x_multiplier);
		y1 = base;
		x2 = (X_DIVIDER + 2 * PADDING) + (short)((counter + 1) * x_multiplier);
		y2 = base;
	}


	Serial.print("X1:");
	Serial.println(x1);
	Serial.print("Y1:");
	Serial.println(y1);
	Serial.print("X2:");
	Serial.println(x2);
	Serial.print("Y2:");
	Serial.println(y2);

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
		base = 240 - PADDING + min * y_multiplier;
	}
	else {
		base = 240 - PADDING;
	}

	Serial.print("Base:");
	Serial.println(base);
	Serial.println("++Points++++");
	
	switch (range) {

	case MINUTE:
		for (uint8_t i = 0; i < NUMMINUTE; i++) {
			myGLCD.setColor(VGA_RED);
			drawValue(i, sensor_ptr->minute_values[i], x_multiplier, y_multiplier, base);
			
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i > 0) myGLCD.print(String(i*5), X_DIVIDER + 5 * PADDING + i * x_multiplier, base - 12);
			}
			else {
				if (i > 0) myGLCD.print(String(i*5), X_DIVIDER + 5 * PADDING + i * x_multiplier, base + 12);
			}
		}
		
		break;

	case HOUR:
		for (uint8_t i = 0; i < NUMHOUR; i++) {
			myGLCD.setColor(VGA_FUCHSIA);
			drawValue(i, sensor_ptr->hour_values[i], x_multiplier, y_multiplier, base);
			
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i  % 15 == 0) myGLCD.print(String(i), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i %  15 == 0) myGLCD.print(String(i), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		}
		break;

	case DAY:

		for (uint8_t i = 0; i < NUMDAY; i++) {
			myGLCD.setColor(VGA_LIME);
			drawValue(i, sensor_ptr->day_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 8 == 0) myGLCD.print(String(i/4), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 8 == 0) myGLCD.print(String(i/4), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		}
		break;

	case MONTH:
		for (uint8_t i = 0; i < NUMMONTH; i++) {
			myGLCD.setColor(VGA_BLUE);
			drawValue(i, sensor_ptr->month_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 14 == 0) myGLCD.print(String(i / 14), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 14 == 0) myGLCD.print(String(i / 14), X_DIVIDER + 5 * PADDING + (i-1) * x_multiplier, base + 12);
			}
		}
		break;

	case YEAR:
		for (uint8_t i = 0; i < NUMYEAR; i++) {
			myGLCD.setColor(VGA_RED);
			drawValue(i, sensor_ptr->year_values[i], x_multiplier, y_multiplier, base);
		
			myGLCD.setColor(VGA_WHITE);
			myGLCD.setBackColor(VGA_TRANSPARENT);

			if (base > 120) {
				if (i % 12 == 0) myGLCD.print(String(i / 12), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base - 12);
			}
			else {
				if (i % 12 == 0) myGLCD.print(String(i / 12), X_DIVIDER + 5 * PADDING + (i - 1)  * x_multiplier, base + 12);
			}
		
		}
		break;
	}


	//Draw Axis
	myGLCD.setColor(VGA_WHITE);
	myGLCD.setBackColor(VGA_TRANSPARENT);
	myGLCD.drawLine(X_DIVIDER + PADDING, base, 320 - PADDING, base);
	myGLCD.drawLine(X_DIVIDER + 2 * PADDING, Y_DIVIDER + PADDING, X_DIVIDER + 2 * PADDING, 240 - PADDING);

	//Labels
	if (base > 120) {
		label = "0";
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, X_DIVIDER + 3 * PADDING, base - 12);
	} 
	else {
		label = "0";
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, X_DIVIDER + 3 * PADDING, base + 12);
	}

	//Labels
	if (max > 0 && base > 60) {
		label = "Max:";
		label += (String)max;
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, X_DIVIDER + 3 * PADDING, Y_DIVIDER + PADDING);
	}
	//Min
	if (min < 0 && base < 180 ) {
		label = "Min:";
		label += (String)min;
		label += (String)sensor_ptr->unit;
		myGLCD.print(label, X_DIVIDER + 3 * PADDING, 240 - 12 - PADDING);
	}
}


//All Types of Templates used:
template class MenueControlButton<Trigger>;
template class MenueControlButton<RuleSet>;
template class MenueControlButton<UserInterface>;

template class ControlButton<RelaisBoard>;
template class ControlButton<CurrentTime>;
template class ControlButton<RuleSet>;
template class ControlButton<UserInterface>;
template class ControlButton<Trigger>;
template class ControlButton<FileSystem>;
template class ControlButton<ActionChain>;