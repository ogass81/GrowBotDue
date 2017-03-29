// Network.h

#ifndef _NETWORK_h
#define _NETWORK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <WiFiEsp.h>

#include <ArduinoJson.h>
#include "CurrentTime.h"
#include "Sensor.h"
#include "Trigger.h"
#include "Ruleset.h"
#include "ActionChain.h"

extern CurrentTime currenttime;
extern Sensor *sensors[SENSNUMBER];
extern Trigger *trigger[TRIGCAT][TRIGNUMBER];
extern RuleSet *rulesets[RULES];
extern ActionChain *actionchains[ACTIONCHAINS];


class WebServer : public WiFiEspServer {
private: 
	String createPostRequest(char *json);
	String createHtmlResponse(String code, String text);

public:
	WebServer();
	void checkConnection();

};



#endif

