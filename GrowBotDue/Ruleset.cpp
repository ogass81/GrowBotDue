// 
// 
// 

#include "Ruleset.h"

RuleSet::RuleSet(int count)
{
	title = String(count);
	active = false;

	assignedTrigger[0] = NULL;
	assignedTrigger[1] = NULL;
	assignedTrigger[2] = NULL;

	assignedBoolOp[0] = AND;
	assignedBoolOp[1] = AND;

	assignedAction[0] = NULL;
	assignedAction[1] = NULL;

	triggercat1_ptr = TRIGCAT;
	triggercat2_ptr = TRIGCAT;
	triggercat3_ptr = TRIGCAT;
	triggerset1_ptr = TRIGNUMBER;
	triggerset2_ptr = TRIGNUMBER;
	triggerset3_ptr = TRIGNUMBER;

	action1_ptr = ACTIONS;
	action2_ptr = ACTIONS;

}

void RuleSet::changeRuleSetTrigger1()
{
	uint8_t cat = triggercat1_ptr;
	uint8_t set = triggerset1_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}
		
		if (cat == TRIGCAT) {
			assignedTrigger[0] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[0] = trigger[cat][set];
			break;
		}
	}
	triggercat1_ptr = cat;
	triggerset1_ptr = set;
}

void RuleSet::changeRuleSetTrigger2()
{
	uint8_t cat = triggercat2_ptr;
	uint8_t set = triggerset2_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}

		if (cat == TRIGCAT) {
			assignedTrigger[1] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[1] = trigger[cat][set];
			break;
		}
	}
	triggercat2_ptr = cat;
	triggerset2_ptr = set;
}

void RuleSet::changeRuleSetTrigger3()
{
	uint8_t cat = triggercat3_ptr;
	uint8_t set = triggerset3_ptr;

	//Cycle through active triggers
	while (true) {
		if (set == TRIGNUMBER - 1) {
			set = 0;

			if (cat < TRIGCAT) cat++;
			else cat = 0;
		}
		else if (set == TRIGNUMBER) {
			set = 0;
			cat = 0;
		}
		else {
			set++;
		}

		if (cat == TRIGCAT) {
			assignedTrigger[2] = NULL;
			set = TRIGNUMBER;
			break;
		}
		else if (trigger[cat][set]->active == true) {
			assignedTrigger[2] = trigger[cat][set];
			break;
		}
	}
	triggercat3_ptr = cat;
	triggerset3_ptr = set;
}

void RuleSet::changeRuleSetBoolOp1()
{
	if (assignedBoolOp[0] == NOT) assignedBoolOp[0] = AND;
	else if (assignedBoolOp[0] == AND) assignedBoolOp[0] = OR;
	else assignedBoolOp[0] = NOT;
}

void RuleSet::changeRuleSetBoolOp2()
{
	if (assignedBoolOp[1] == NOT) assignedBoolOp[1] = AND;
	else if (assignedBoolOp[1] == AND) assignedBoolOp[1] = OR;
	else assignedBoolOp[1] = NOT;
}

void RuleSet::changeRuleAction1()
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

void RuleSet::changeRuleAction2()
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
			assignedAction[1] = NULL;
			break;
		}
		else if (actions[action]->active == true) {
			assignedAction[1] = actions[action];
			break;
		}
	}
	action1_ptr = action;
}

void RuleSet::changeRuleSetActive()
{
	if(active == true) active = false;
	else active = true;
}

String RuleSet::getTitle()
{
	return String("Ruleset #" + title);
}

String RuleSet::getRuleSetCat1()
{
	return String("<disabled>");
}

String RuleSet::getRuleSetCat2()
{

 return String("<disabled>");
}

String RuleSet::getRuleSetCat3()
{
	return String("<disabled>");
}

String RuleSet::getRuleSetTrigger1()
{
	if (assignedTrigger[0] != NULL) {
		return String(assignedTrigger[0]->getTitle());
	}
	else return String("<disabled>");
}

String RuleSet::getRuleSetTrigger2()
{
	if (assignedTrigger[1] != NULL) {
		return String(assignedTrigger[1]->getTitle());
	}
	else return String("<disabled>");
}

String RuleSet::getRuleSetTrigger3()
{
	if (assignedTrigger[2] != NULL) {
		return String(assignedTrigger[2]->getTitle());
	}
	else return String("<disabled>");
}

String RuleSet::getRuleSetBoolOp1()
{
	String label;
	
	if (assignedBoolOp[0] == NOT) label = "AND";
	else if (assignedBoolOp[0] == AND) label = "OR";
	else label = "NOT";
	
	return(String(label));
}

String RuleSet::getRuleSetBoolOp2()
{
	String label;

	if (assignedBoolOp[1] == NOT) label = "AND";
	else if (assignedBoolOp[1] == AND) label = "OR";
	else label = "NOT";

	return(String(label));
}

String RuleSet::getRuleSetAction1()
{
	if (assignedAction[0] != NULL) return String(assignedAction[0]->getTitle());
	else return String("<disabled>");
}

String RuleSet::getRuleSetAction2()
{
	if (assignedAction[1] != NULL) return String(assignedAction[1]->getTitle());
	else return String("<disabled>");
}

String RuleSet::getRuleSetActive()
{
	if (active == true) return String("On");
	else return ("Off");
}

bool RuleSet::checkState()
{
	bool state = false;
	uint8_t i = 0;

	if (this->active == true) {
		while (assignedTrigger[i] != NULL) {
			Serial.print("Trigger:");
			Serial.println(assignedTrigger[i]->getTitle());

			if (i == 0) state = assignedTrigger[i]->checkState();
		
			else {
				if (assignedBoolOp[i - 1] != NULL) {

					switch (assignedBoolOp[i - 1]) {

					case AND:
						state = state && assignedTrigger[i]->checkState();
						Serial.println(">AND");
						break;

					case OR:
						state = state || assignedTrigger[i]->checkState();
						Serial.println(">OR");
						break;

					case NOT:
						state = state && !assignedTrigger[i]->checkState();
						Serial.println(">NOT");
						break;
					}
				}
			}
			i++;
		}
	}
	return state;
}

void RuleSet::serializeJSON(uint8_t id, char * json, size_t maxSize)
{
	StaticJsonBuffer<500> jsonBuffer;

	JsonObject& rules = jsonBuffer.createObject();

	rules["type"] = "Rules";
	rules["id"] = id;
	rules["active"] = this->active;
	rules["triggerset1_ptr"] = this->triggerset1_ptr;
	rules["triggercat1_ptr"] = this->triggercat1_ptr;
	rules["triggerset2_ptr"] = this->triggerset2_ptr;
	rules["triggercat2_ptr"] = this->triggercat2_ptr;
	rules["triggerset3_ptr"] = this->triggerset3_ptr;
	rules["triggercat3_ptr"] = this->triggercat3_ptr;
	rules["action1_ptr"] = this->action1_ptr;
	rules["action2_ptr"] = this->action2_ptr;

	JsonArray& boolop = rules.createNestedArray("Bool");
	boolop.add(this->assignedBoolOp[0]);
	boolop.add(this->assignedBoolOp[1]);

	rules.prettyPrintTo(json, maxSize);
}

bool RuleSet::deserializeJSON(JsonObject & data)
{
	if (data.success() == true) {
		this->active = data["active"];
		this->triggerset1_ptr = data["triggerset1_ptr"];
		this->triggercat1_ptr = data["triggercat1_ptr"];
		this->triggerset2_ptr = data["triggerset2_ptr"];
		this->triggercat2_ptr = data["triggercat2_ptr"];
		this->triggerset3_ptr = data["triggerset3_ptr"];
		this->triggercat3_ptr = data["triggercat3_ptr"];
		this->action1_ptr = data["action1_ptr"];
		this->action2_ptr = data["action2_ptr"];
		
		/*
		this->assignedBoolOp[0] = data["Bool"][0];
		this->assignedBoolOp[1] = data["Bool"][1];
		*/


		if (this->triggerset1_ptr != TRIGNUMBER && this->triggercat1_ptr != TRIGCAT) this->assignedTrigger[0] = trigger[triggercat1_ptr][triggerset1_ptr];
		if (this->triggerset2_ptr != TRIGNUMBER && this->triggercat2_ptr != TRIGCAT) this->assignedTrigger[1] = trigger[triggercat2_ptr][triggerset2_ptr];
		if (this->triggerset3_ptr != TRIGNUMBER && this->triggercat3_ptr != TRIGCAT) this->assignedTrigger[2] = trigger[triggercat3_ptr][triggerset3_ptr];
		if (this->action1_ptr != ACTIONS) this->assignedAction[0] = actions[action1_ptr];
		if (this->action2_ptr != ACTIONS) this->assignedAction[1] = actions[action2_ptr];
	}

	return data.success();
}

void RuleSet::executeAction()
{
	int i = 0;

	if (this->checkState() == true) {
		while (assignedAction[i] != 0) {
			assignedAction[i]->execute();
			i++;
		}
	}
}


