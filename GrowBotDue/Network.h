// Network.h

#ifndef _NETWORK_h
#define _NETWORK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <ArduinoJson.h>
#include "RealTimeClock.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "Action.h"
#include "ActionChain.h"
#include "RCSocketController.h"
#include "Setting.h"
#include "FileSystem.h"
#include "TaskManager.h"

extern RealTimeClock internalRTC;
extern Sensor *sensors[SENS_NUM];
extern Trigger *trigger[TRIGGER_TYPES][TRIGGER_SETS];
extern RuleSet *rulesets[RULESETS_NUM];
extern Action *actions[ACTIONS_NUM];
extern ActionChain *actionchains[ACTIONCHAINS_NUM];
extern RCSocketController *rcsocketcontroller;
extern TaskManager *taskmanager;
extern FileSystem filesystem;


template <class ObjectType>
class ListGenerator {
public:
	ObjectType **objectarray;
	int8_t object_count;
	int8_t category_count;

	ListGenerator(ObjectType **objects, int8_t num);
	void generateList(String object_type, char *json);
	void generateList(String object_type, uint8_t id, char *json);
};

class WebTimeClient : public WiFiEspClient {
public:
	unsigned long getWebTime();

};

class WebServer : public WiFiEspServer {
private: 
	//Create POST Request with JSON in HTTP body
	String createPostRequest(char *json);
	//Create HTTP Response with HTML Body
	String createHtmlResponse(String code, String text);

public:
	WebServer();
	void checkConnection();
};
#endif
