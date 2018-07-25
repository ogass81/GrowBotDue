// 
// 
// 

#include "Action.h"

void Action::execute()
{
}

void Action::serializeJSON(uint8_t id, char * json, size_t maxSize, Scope scope)
{
}

String Action::getTitle()
{
	return String(title);
}

void Action::setAntagonist(String group_title, Action * aObject)
{
	//LOGDEBUG2(F("[Action]"), F("setAntagonist()"), F("OK: Setting Antagonist Object"), "", "", "");
	this->group_title = group_title;
	this->antaObject = aObject;
}


template<class ActionType>
SimpleAction<ActionType>::SimpleAction(String title, ActionType * actionObj, void(ActionType::*cFunct)(), bool visible)
{
	this->title = title;
	this->group_title = "";
	this->actionObject = actionObj;
	this->callback = cFunct;
	this->visible = visible;
}

template<class ActionType>
void SimpleAction<ActionType>::serializeJSON(uint8_t id, char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	if (scope == LIST || scope == DETAILS) {
		actions["tit"] = title;
		actions["grp"] = group_title;
		if(antaObject != NULL) actions["opp"] = antaObject->title;
		actions["vis"] = visible;
	}
	
	if (scope == DETAILS) {
		actions["id"] = id;
		actions["obj"] = "ACTION";
	}

	actions.printTo(json, maxSize);
	LOGDEBUG2(F("[SimpleAction]"), F("serializeJSON()"), F("OK: Serialized Action"), String(id), String(actions.measureLength()), String(maxSize));
}

template<class ActionType>
void SimpleAction<ActionType>::execute()
{
	if (actionObject != NULL && callback != NULL) {
		LOGDEBUG(F("[Action]"), F("execute()"), F("OK: Execute Action"), title, "", "");
		(actionObject->*callback)();

		String keys[] = { "Action" };
		String values[] = { title };
		logengine.addLogEntry(0, "Action", "OK: Execute Action", keys, values, 1);
	}
}

template<class ActionType>
ParameterizedSimpleAction<ActionType>::ParameterizedSimpleAction(String title, ActionType * actionObj, void(ActionType::*cFunct)(int), int par, bool visible)
{
	this->title = title;
	this->group_title = "";
	this->actionObject = actionObj;
	this->callback = cFunct;
	this->visible = visible;
	this->parameter = par;
}

template<class ActionType>
void ParameterizedSimpleAction<ActionType>::serializeJSON(uint8_t id, char * json, size_t maxSize, Scope scope)
{
	StaticJsonBuffer<JSONBUFFER_SIZE> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	if (scope == LIST || scope == DETAILS) {
		actions["tit"] = title;
		actions["grp"] = group_title;
		if (antaObject != NULL) actions["anta"] = antaObject->title;
		actions["vis"] = visible;
		actions["par"] = parameter;
	}


	if (scope == DETAILS) {
		actions["id"] = id;
		actions["obj"] = "ACTION";
	}

	actions.printTo(json, maxSize);
	LOGDEBUG2(F("[ParameterizedSimpleAction]"), F("serializeJSON()"), F("OK: Serialized Action"), String(id), String(actions.measureLength()), String(maxSize));
}

template<class ActionType>
void ParameterizedSimpleAction<ActionType>::execute()
{
	if (actionObject != NULL) {
		if (callback != NULL) {
			if (parameter >= 0) {
				LOGDEBUG(F("[Action]"), F("execute()"), F("OK: Execute Action"), title, "", "");
				String keys[] = { "Action" };
				String values[] = { title };
				logengine.addLogEntry(0, "Action", "OK: Execute Action", keys, values, 1);

				(actionObject->*callback)(parameter);
			}
			else {
				LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Argument missing"), title, "", "");

				String keys[] = { "Action" };
				String values[] = { title };
				logengine.addLogEntry(0, "Action", "ERROR: Argument missing", keys, values, 1);
			}
		}
		else LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Callback missing"), title, "", "");
	}
	else LOGDEBUG(F("[Action]"), F("execute()"), F("ERROR: Action Object missing"), title, "", "");
}
//All Types of Templates used:
template class SimpleAction<RCSocketController>;
template class ParameterizedSimpleAction<RCSocketController>;
