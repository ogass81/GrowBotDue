// ActionChain.h

#ifndef _ACTIONCHAIN_h
#define _ACTIONCHAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>
#include "Action.h"
#include "TaskManager.h"

class TaskManager;

extern TaskManager *taskmanager;
extern Action *actions[ACTIONS];



class ActionChain {
public:
	bool active;
	String title;

	//Pointer Values for Serialization
	uint8_t action1_ptr;
	uint8_t action2_ptr;
	uint8_t action3_ptr;
	uint8_t action4_ptr;
	uint8_t action5_ptr;
	uint8_t action6_ptr;

	//Pointer to Action Objects
	Action *assignedAction[5];
	//Parameter for Action Objects
	uint8_t actionParameter[5];

	ActionChain(int count);

	//UI Output
	String getTitle();

	String getChainAction1();
	String getChainAction2();
	String getChainAction3();
	String getChainAction4();
	String getChainAction5();
	String getChainAction6();
	
	String getChainPar1();
	String getChainPar2();
	String getChainPar3();
	String getChainPar4();
	String getChainPar5();
	String getChainPar6();
	
	String getChainActive();

	//UI Controls
	void changeAction1();
	void changeAction2();
	void changeAction3();
	void changeAction4();
	void changeAction5();
	void changeAction6();

	void changePar1();
	void changePar2();
	void changePar3();
	void changePar4();
	void changePar5();	
	void changePar6();

	void changeChainActive();

	//Settings
	void reset();

	//Serialize
	void serializeJSON(uint8_t id, char* json, size_t maxSize);
	bool deserializeJSON(JsonObject& data);

	//Execute all Actions in Chain
	void execute();
};

#endif

