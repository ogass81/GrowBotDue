// 
// 
// 

#include "ActionChain.h"

ActionChain::ActionChain()
{
	reset();
}

void ActionChain::changeAction1()
{
	uint8_t action = action1_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[0] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[0] = actions[action];
			break;
		}
	}
	action1_ptr = action;
}

void ActionChain::changeAction2()
{
	uint8_t action = action2_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[1] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[1] = actions[action];
			break;
		}
	}
	action2_ptr = action;
}

void ActionChain::changeAction3()
{
	uint8_t action = action3_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[2] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[2] = actions[action];
			break;
		}
	}
	action3_ptr = action;
}

void ActionChain::changeAction4()
{
	uint8_t action = action4_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[3] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[3] = actions[action];
			break;
		}
	}
	action4_ptr = action;
}

void ActionChain::changeAction5()
{
	uint8_t action = action5_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[4] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[4] = actions[action];
			break;
		}
	}
	action5_ptr = action;
}

void ActionChain::changeAction6()
{
	uint8_t action = action6_ptr;

	//Cycle through actions
	while (true) {
		if (action == ACTIONS) {
			action = 0;
		}
		else {
			action++;
		}

		if (action == ACTIONS) {
			assignedAction[5] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[5] = actions[action];
			break;
		}
	}
	action6_ptr = action;
}

void ActionChain::changePar1()
{
	if (actionParameter[0] < MAXTASKSECONDS) {
		actionParameter[0]++;
	}
	else actionParameter[0] = 0;
}

void ActionChain::changePar2()
{
	if (actionParameter[1] < MAXTASKSECONDS) {
		actionParameter[1]++;
	}
	else actionParameter[1] = 0;
}

void ActionChain::changePar3()
{
	if (actionParameter[2] < MAXTASKSECONDS) {
		actionParameter[2]++;
	}
	else actionParameter[2] = 0;
}

void ActionChain::changePar4()
{
	if (actionParameter[3] < MAXTASKSECONDS) {
		actionParameter[3]++;
	}
	else actionParameter[3] = 0;
}

void ActionChain::changePar5()
{
	if (actionParameter[4] < MAXTASKSECONDS) {
		actionParameter[4]++;
	}
	else actionParameter[4] = 0;
}

void ActionChain::changePar6()
{
	if (actionParameter[5] < MAXTASKSECONDS) {
		actionParameter[5]++;
	}
	else actionParameter[5] = 0;
}

void ActionChain::reset()
{
	active = false;

	assignedAction[0] = NULL;
	assignedAction[1] = NULL;
	assignedAction[2] = NULL;
	assignedAction[3] = NULL;
	assignedAction[4] = NULL;
	assignedAction[5] = NULL;

	action1_ptr = ACTIONS;
	action2_ptr = ACTIONS;
	action3_ptr = ACTIONS;
	action4_ptr = ACTIONS;
	action5_ptr = ACTIONS;
	action6_ptr = ACTIONS;

	actionParameter[0] = 0;
	actionParameter[1] = 0;
	actionParameter[2] = 0;
	actionParameter[3] = 0;
	actionParameter[4] = 0;
	actionParameter[5] = 0;
}

void ActionChain::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& actions = jsonBuffer.createObject();

	actions["type"] = "CHAIN";
	actions["id"] = id;
	actions["active"] = active;
	actions["action1_ptr"] = action1_ptr;
	actions["action2_ptr"] = action2_ptr;
	actions["action1_ptr"] = action3_ptr;
	actions["action2_ptr"] = action4_ptr;
	actions["action1_ptr"] = action5_ptr;
	actions["action2_ptr"] = action6_ptr;
	actions["action1_par"] = actionParameter[0];
	actions["action2_par"] = actionParameter[1];
	actions["action3_par"] = actionParameter[2];
	actions["action4_par"] = actionParameter[3];
	actions["action5_par"] = actionParameter[4];
	actions["action6_par"] = actionParameter[5];
	
	actions.printTo(json, maxSize);
}

bool ActionChain::deserializeJSON(JsonObject & data)
{
	if (data.success() == true) {
		active = data["active"];
		action1_ptr = data["action1_ptr"];
		action2_ptr = data["action2_ptr"];
		action3_ptr = data["action3_ptr"];
		action4_ptr = data["action4_ptr"];
		action5_ptr = data["action5_ptr"];
		action6_ptr = data["action6_ptr"];

		actionParameter[0] = data["action1_par"];
		actionParameter[1] = data["action2_par"];
		actionParameter[2] = data["action3_par"];
		actionParameter[3] = data["action4_par"];
		actionParameter[4] = data["action5_par"];
		actionParameter[5] = data["action6_par"];

		if (this->action1_ptr != ACTIONS) this->assignedAction[0] = actions[action1_ptr];
		else this->assignedAction[0] = NULL;
		if (this->action2_ptr != ACTIONS) this->assignedAction[1] = actions[action2_ptr];
		else this->assignedAction[1] = NULL;
		if (this->action3_ptr != ACTIONS) this->assignedAction[2] = actions[action3_ptr];
		else this->assignedAction[2] = NULL;
		if (this->action4_ptr != ACTIONS) this->assignedAction[3] = actions[action4_ptr];
		else this->assignedAction[3] = NULL;
		if (this->action5_ptr != ACTIONS) this->assignedAction[4] = actions[action5_ptr];
		else this->assignedAction[4] = NULL;
		if (this->action6_ptr != ACTIONS) this->assignedAction[5] = actions[action6_ptr];
		else this->assignedAction[5] = NULL;
	}

	return data.success();
}

void ActionChain::executeAction()
{
	taskmanager->addActions(this);
}
