// 
// 
// 

#include "ActionChain.h"

ActionChain::ActionChain(int count)
{
	title = String(count);
	reset();
}

void ActionChain::changeAction1()
{
	uint8_t action = actionPtr[0];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[0] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[0] = actions[action];
			break;
		}
	}
	actionPtr[0] = action;
}

void ActionChain::changeAction2()
{
	uint8_t action = actionPtr[1];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[1] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[1] = actions[action];
			break;
		}
	}
	actionPtr[1] = action;
}

void ActionChain::changeAction3()
{
	uint8_t action = actionPtr[2];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[2] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[2] = actions[action];
			break;
		}
	}
	actionPtr[2] = action;
}

void ActionChain::changeAction4()
{
	uint8_t action = actionPtr[3];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[3] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[3] = actions[action];
			break;
		}
	}
	actionPtr[3] = action;
}

void ActionChain::changeAction5()
{
	uint8_t action = actionPtr[4];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[4] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[4] = actions[action];
			break;
		}
	}
	actionPtr[4] = action;
}

void ActionChain::changeAction6()
{
	uint8_t action = actionPtr[5];

	//Cycle through actions
	while (true) {
		if (action == ACTIONS_NUM) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS_NUM) {
			assignedAction[5] = NULL;
			break;
		}
		else if (actions[action]->visible == true) {
			assignedAction[5] = actions[action];
			break;
		}
	}
	actionPtr[5] = action;
}

void ActionChain::changePar1()
{
	if (actionPar[0] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[0]++;
	}
	else actionPar[0] = 0;
}

void ActionChain::changePar2()
{
	if (actionPar[1] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[1]++;
	}
	else actionPar[1] = 0;
}

void ActionChain::changePar3()
{
	if (actionPar[2] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[2]++;
	}
	else actionPar[2] = 0;
}

void ActionChain::changePar4()
{
	if (actionPar[3] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[3]++;
	}
	else actionPar[3] = 0;
}

void ActionChain::changePar5()
{
	if (actionPar[4] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[4]++;
	}
	else actionPar[4] = 0;
}

void ActionChain::changePar6()
{
	if (actionPar[5] < ACTIONCHAIN_TASK_MAXDURATION) {
		actionPar[5]++;
	}
	else actionPar[5] = 0;
}

void ActionChain::changeChainActive()
{
	if (active == true) active = false;
	else active = true;
}

void ActionChain::reset()
{
	active = false;

	for (uint8_t i = 0; i < ACTIONCHAIN_LENGTH; i++) {
		assignedAction[i] = NULL;
		actionPtr[i] = ACTIONS_NUM;
		actionPar[i] = 0;
	}
}

void ActionChain::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	actions["type"] = "CHAIN";
	actions["id"] = id;
	actions["active"] = active;
	
	for (uint8_t i = 0; i < ACTIONCHAIN_LENGTH; i++) {
		actions[String("actPtr" + i)] = actionPtr[i];
		actions[String("actPar" + i)] = actionPar[i];
	}

	actions.printTo(json, maxSize);
	LOGDEBUG2(F("[ActionChain]"), F("serializeJSON()"), F("OK: Serialized Members for Actionchain"), String(id), String(actions.measureLength()), String(maxSize));
}

bool ActionChain::deserializeJSON(JsonObject & data)
{
	if (data.success() == true) {
		
		if (data["active"] != "") active = data["active"];
		
		for (uint8_t i = 0; i < ACTIONCHAIN_LENGTH; i++) {
			//Assign Pointers to Action using Index to Action
			if (data[String("actPtr" + i)] != "") {
				actionPtr[i] = data[String("actPtr" + i)];
				assignedAction[i] = actions[actionPtr[i]];
			}
			else {
				actionPtr[i] = ACTIONS_NUM;
				assignedAction[i] = NULL;
			}
			//Assign Action Parameter to Member
			if (data[String("actPar" + i)] != "") actionPar[i] = data[String("actPar" + i)];
			else actionPtr[i] = 0;
		}

		LOGDEBUG2(F("[ActionChain]"), F("deserializeJSON()"), F("OK: Deserialized members for Actionchain"), String(data["id"].asString()), "", "");
	}
	else {
		LOGDEBUG2(F("[ActionChain]"), F("deserializeJSON()"), F("ERROR: No Data to deserialize members"), F("Datasize"), String(data.size()), "");
	}
	return data.success();
}

void ActionChain::execute()
{
	taskmanager->addActions(this);
}

String ActionChain::getTitle()
{
	return String("Action Chain #" + String(title));
}

String ActionChain::getChainAction1()
{
	if (assignedAction[0] != NULL) return String(assignedAction[0]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainAction2()
{
	if (assignedAction[1] != NULL) return String(assignedAction[1]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainAction3()
{
	if (assignedAction[2] != NULL) return String(assignedAction[2]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainAction4()
{
	if (assignedAction[3] != NULL) return String(assignedAction[3]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainAction5()
{
	if (assignedAction[4] != NULL) return String(assignedAction[4]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainAction6()
{
	if (assignedAction[5] != NULL) return String(assignedAction[5]->getTitle());
	else return String(F("<NONE>"));
}

String ActionChain::getChainPar1()
{
	return String(actionPar[0]);
}

String ActionChain::getChainPar2()
{
	return String(actionPar[1]);
}

String ActionChain::getChainPar3()
{
	return String(actionPar[2]);
}

String ActionChain::getChainPar4()
{
	return String(actionPar[3]);
}

String ActionChain::getChainPar5()
{
	return String(actionPar[4]);
}

String ActionChain::getChainPar6()
{
	return String(actionPar[5]);
}

String ActionChain::getChainActive()
{
	if (active == true) return String(F("ON"));
	else return (F("OFF"));
}