// 
// 
// 

#include "Action.h"

void Action::execute()
{
}

void Action::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
}

String Action::getTitle()
{
	return String(name);
}

void Action::setAntagonist(Action * aObject)
{
	LOGDEBUG2(F("[Action]"), F("setAntagonist()"), F("OK: Setting Antagonist Object"), "", "", "");
	antaObject = aObject;
}


template<class ActionType>
SimpleAction<ActionType>::SimpleAction(String name, ActionType * actionObj, void(ActionType::*cFunct)(), bool visible)
{
	this->name = name;
	this->actionObject = actionObj;
	this->callback = cFunct;
	this->visible = visible;
}

template<class ActionType>
void SimpleAction<ActionType>::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	actions["type"] = "ACTION";
	actions["id"] = id;
	actions["visible"] = visible;
	actions["name"] = name;

	actions.printTo(json, maxSize);
	LOGDEBUG2(F("[SimpleAction]"), F("serializeJSON()"), F("OK: Serialized Action"), String(id), String(actions.measureLength()), String(maxSize));
}

template<class ActionType>
void SimpleAction<ActionType>::execute()
{
	if (actionObject != NULL && callback != NULL) {
		LOGDEBUG(F("[Action]"), F("execute()"), F("OK: Execute Action"), name, "", "");
		(actionObject->*callback)();
	}
}

template<class ActionType>
ParameterizedSimpleAction<ActionType>::ParameterizedSimpleAction(String name, ActionType * actionObj, void(ActionType::*cFunct)(int), int par, bool visible)
{
	this->name = name;
	this->actionObject = actionObj;
	this->callback = cFunct;
	this->visible = visible;
	this->parameter = par;
}

template<class ActionType>
void ParameterizedSimpleAction<ActionType>::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	actions["type"] = "ACTION";
	actions["id"] = id;
	actions["visible"] = visible;
	actions["name"] = name;

	actions.printTo(json, maxSize);
	LOGDEBUG2(F("[ParameterizedSimpleAction]"), F("serializeJSON()"), F("OK: Serialized Action"), String(id), String(actions.measureLength()), String(maxSize));
}

template<class ActionType>
void ParameterizedSimpleAction<ActionType>::execute()
{
	if (actionObject != NULL) {
		if (callback != NULL) {
			if (parameter >= 0) {
				LOGDEBUG(F("[Action]"), F("execute()"), F("OK: Execute Action"), name, "", "");
				(actionObject->*callback)(parameter);
			}
			else LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Argument missing"), name, "", "");
		}
		else LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Callback missing"), name, "", "");
	}
	else LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Action Object missing"), name, "", "");
}
//All Types of Templates used:
template class SimpleAction<RelaisBoard>;
template class SimpleAction<DigitalSwitch>;
template class ParameterizedSimpleAction<RCSocketController>;