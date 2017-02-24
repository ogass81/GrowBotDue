// Ruleset.h

#ifndef _RULESET_h
#define _RULESET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>
#include "Trigger.h"
#include "Action.h"

extern Action *actions[ACTIONS];
extern Trigger *trigger[TRIGCAT][TRIGNUMBER];

//Rulesets are Touples of Triggers, Boolean Operators. If the whole expression is true the assigned action (callback function) is executed
class RuleSet {
public:
	String title;
	bool active;

	uint8_t triggercat1_ptr, triggercat2_ptr, triggercat3_ptr;
	uint8_t triggerset1_ptr, triggerset2_ptr, triggerset3_ptr;

	uint8_t action1_ptr, action2_ptr;
	

	Trigger *assignedTrigger[3];
	BoolOp assignedBoolOp[2];
	Action *assignedAction[2];

	RuleSet(int count);

	void changeRuleSetTrigger1();
	void changeRuleSetTrigger2();
	void changeRuleSetTrigger3();

	void changeRuleSetBoolOp1();
	void changeRuleSetBoolOp2();

	void changeRuleAction1();
	void changeRuleAction2();

	void changeRuleSetActive();
	
	String getTitle();

	String getRuleSetCat1();
	String getRuleSetCat2();
	String getRuleSetCat3();

	String getRuleSetTrigger1();
	String getRuleSetTrigger2();
	String getRuleSetTrigger3();

	String getRuleSetBoolOp1();
	String getRuleSetBoolOp2();

	String getRuleSetAction1();
	String getRuleSetAction2();

	String getRuleSetActive();

	bool checkState();

	void serializeJSON(uint8_t id, char* json, size_t maxSize);
	bool deserializeJSON(JsonObject& data);

	void executeAction();
};

#endif

