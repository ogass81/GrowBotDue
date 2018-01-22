// WifiClientInterface.h

#ifndef _WIFICLIENTINTERFACE_h
#define _WIFICLIENTINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiEsp.h>

class WifiClientInterface : public WiFiEspClient, public WiFiClient {


};


#endif

