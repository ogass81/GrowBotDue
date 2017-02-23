// Ruleset.h

#ifndef _RULESET_h
#define _RULESET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "Trigger.h"
#include "Action.h"

extern Action *actions[ACTIONS];
extern Trigger *trigger[TRIGCAT][TRIGNUMBER];

//Rulesets are Touples of Triggers, Boolean Operators. If the whole expression is true the assigned action (callback function) is executed
class RulesSet {
public:
	String title;
	bool active;

	Trigger *assignedTrigger[3];
	BoolOp *assignedBoolOp[3];
	Action *assignedAction[2];

	RulesSet();

	void changeRuleSetTrigger1();
	void changeRuleSetTrigger2();
	void changeRuleSetTrigger3();

	void changeRuleSetBoolOp1();
	void changeRuleSetBoolOp2();

	void changeRuleAction1();
	void changeRuleAction2();

	void changeRuleSetActive();

	String getRuleSetTrigger1();
	String getRuleSetTrigger2();
	String getRuleSetTrigger3();

	String getRuleSetBoolOp1();
	String getRuleSetBoolOp2();

	String getRuleSetAction1();
	String getRuleSetAction2();

	String getRuleSetActive();

	bool checkState();
	void executeAction();
};

#endif

