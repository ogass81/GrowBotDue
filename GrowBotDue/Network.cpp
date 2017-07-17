// 
// 
// 

#include "Network.h"

String WebServer::createPostRequest(char *json)
{
	String load, request;

	load = String(json) + "\r\n";
	//request = "POST / HTTP/1.1\r\n";
	request = "HTTP/1.1 200 OK\r\n";
	//request += "Host: " + ip.printTo;
	//request += "\r\n";
	request += "Accept: */*\r\n";
	request += "Content-Length: ";
	request += load.length();
	request += "\r\n";
	request += "Content-Type: application/json\r\n";
	request += "\r\n";
	request += load;
	request += "\r\n";

	return String(request);
}

String WebServer::createHtmlResponse(String code, String text)
{
	String request;

	request = "HTTP/1.1 " + (String)code;
	request += "\r\n";
	request += "Content-type:text/html\r\n";
	request += "\r\n";
	request += "<html><title>GrowBot V1.0<\\title><body>";
	request += (String)text;
	request += "<\\body><\\html>";
	request += "\r\n";

	return String(request);
}

WebServer::WebServer() : WiFiEspServer(80)
{
	// print your WiFi shield's IP address
	IPAddress ip = WiFi.localIP();
	LOGMSG(F("[WebServer]"), F("OK: Webserver started"), F("IPV4"), ip, "");
}

void WebServer::checkConnection()
{
	WiFiEspClient client = this->available();

	//Incoming Data
	StaticJsonBuffer<2000> jsonBuffer;

	//Outgoing Data
	char json[2500];

	String request = "";
	bool begin = false;
	bool payload = false;
	bool blankline = true;
	bool success = false;
	int counter = 0;

	int id = 0;
	int cat = 0;

	if (client == true) {
		LOGMSG(F("[WebServer]"), F("OK: New Client connected"), "@" + currenttime.createTime(), F("IPV4"), client.remoteIP());

		while (client.connected()) {
			if (client.available() > 0) {
				char c = client.read();

				if (c == '{') {
					begin = true;
				}
				if (begin == true) {
					request += c;
					if (c == '}') {
						payload = true;
						break;
					}
				}
			}
			else break;
		}
		LOGDEBUG(F("[WebServer]"), F("checkConnection()"), F("OK: Payload"), F("#START#"), String(request), F("#END#"));

		if (payload == true) {
			JsonObject& node = jsonBuffer.parseObject(request);
			if (node.success()) {
				if (node["type"] == "LOGIN") {
					if (node["action"] == "GET") {
						Setting::serializeConstantsJSON(json, 2500);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Constants Action: GET"), "", "");
						client.print(createPostRequest(json));
					}
				}
				else if (node["type"] == "TRIGGER" && node["cat"] != "" && node["id"] != "") {
					id = (int)node["id"];
					cat = (int)node["cat"];
					if (cat < TRIGGER_TYPES && id < TRIGGER_SETS) {
						if (node["action"] == "GET") {
							trigger[cat][id]->serializeJSON(cat, id, json, 2500);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Trigger Action: GET"), String(cat), String(id));
						}
						else if (node["action"] == "SET") {
							success = trigger[cat][id]->deserializeJSON(node);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Trigger Action: SET"), String(cat), String(id));
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Trigger Action: UNKNOWN"), String(cat), String(id));
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}
				else if (node["type"] == "RULE" && node["id"] != "") {
					id = (int)node["id"];

					if (id < RULESETS_NUM) {
						if (node["action"] == "GET") {
							rulesets[id]->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Ruleset Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = rulesets[id]->deserializeJSON(node);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Ruleset Action: SET"), String(id), "");
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Ruleset Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}
				else if (node["type"] == "CHAIN" && node["id"] != "") {
					id = (int)node["id"];

					if (id < ACTIONCHAINS_NUM) {
						if (node["action"] == "GET") {
							actionchains[id]->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actionchain Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = actionchains[id]->deserializeJSON(node);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actionchain Action: SET"), String(id), "");
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Actionchain Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}
				else if (node["type"] == "RCSOCKET" && node["id"] != "") {
					id = (int)node["id"];

					if (id < RC_SOCKETS * 2) {
						if (node["action"] == "GET") {
							rcsocketcontroller->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = rcsocketcontroller->deserializeJSON(id, node);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: SET"), String(id), "");
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else if (node["action"] == "RESET") {
							rcsocketcontroller->resetSettings(id);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: RESET"), String(id), "");
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else if (node["action"] == "LEARN") {
							if (node["mode"] == "ON") {
								rcsocketcontroller->learningmode_on(id);
								client.print(createHtmlResponse("200 OK", "Learning mode activated"));
							}
							else if (node["mode"] == "OFF") {
								rcsocketcontroller->learningmode_off();
								client.print(createHtmlResponse("200 OK", "Learning mode deactivated"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Remote Socket Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}
				else if (node["type"] == "SENSOR") {
					if (node["action"] == "GET") {
						if (node["id"] == "") {
							JsonArray& sensorlist = jsonBuffer.createArray();
							
							for (uint8_t i = 0; i < SENS_NUM; i++) {
								sensors[i]->serializeJSON(i, json, 2500, NONE);
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("Info:"), String(json), "", "");
								sensorlist.add(json);
							}
							sensorlist.printTo(json);
							LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("Info:"), String(json), "", "");
							client.print(json);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < SENS_NUM) {
								if (node["mode"] == "ALL") {
									sensors[id]->serializeJSON(id, json, 2500, ALL);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: ALL"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "AVG") {
									sensors[id]->serializeJSON(id, json, 2500, AVG);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: AVG"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "MINUTE") {
									sensors[id]->serializeJSON(id, json, 2500, MINUTE);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: MINUTE"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "HOUR") {
									sensors[id]->serializeJSON(id, json, 2500, HOUR);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: HOUR"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DAY") {
									sensors[id]->serializeJSON(id, json, 2500, DAY);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: DAY"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "MONTH") {
									sensors[id]->serializeJSON(id, json, 2500, MONTH);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: MONTH"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "YEAR") {
									sensors[id]->serializeJSON(id, json, 2500, YEAR);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: YEAR"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "ALL") {
									sensors[id]->serializeJSON(id, json, 2500, ALL);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: ALL"));
									client.print(createPostRequest(json));
								}
							}
						}
						else {
						}
					}
					else if (node["action"] == "SET") {
						success = sensors[id]->deserializeJSON(node);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Sensor Action: SET"), String(id), "");
						client.print(createHtmlResponse("200 OK", "JSON received"));
					}
					else if (node["action"] == "LEARN") {
						if (node["mode"] == "LOWER") {
							sensors[id]->setLowerThreshold();
							client.print(createHtmlResponse("200 OK", "Set lower threshold"));
						}
						else if (node["mode"] == "UPPER") {
							sensors[id]->setUpperThreshold();
							client.print(createHtmlResponse("200 OK", "Set lower threshold"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Sensor Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}
				else if (node["type"] == "ACTION" && node["id"] != "") {
					id = (int)node["id"];

					if (id < ACTIONS_NUM) {
						if (node["action"] == "GET") {
							actions[id]->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							LOGMSG(F("[WebServer]"), F("OK: Invalid HTTP Request"), F("Type: Action Object Action: SET "), "Not Supported", String(id));
							client.print(createHtmlResponse("501 NOT IMPLEMENTED ", "SET for Action Object not supported"));
						}
						else if (node["action"] == "EXECUTE") {
							actions[id]->execute();
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: EXECUTE"), String(id), "");
							client.print(createHtmlResponse("200 OK", "Executed action"));
						}

						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Action Object Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}
				else if (node["type"] == "SETTING") {
					if (node["action"] == "GET") {
						Setting::serializeJSON(json, 2500);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: GET"), "", "");
						client.print(createPostRequest(json));
					}
					else if (node["action"] == "SET") {
						success = Setting::deserializeJSON(node);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: SET"), "", "");
						client.print(createHtmlResponse("200 OK", "JSON received"));
					}
					else if (node["action"] == "SAVE") {
						if (node["target"] == "ACTIVE") {
							filesystem.saveActiveConfig();
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: SAVE"), "Active Config", "");
							client.print(createHtmlResponse("200 OK", "Saved Active config"));
						}
						else if (node["target"] == "DEFAULT") {
							filesystem.saveDefaultConfig();
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: SAVE"), "Default Config", "");
							client.print(createHtmlResponse("200 OK", "Saved Default config"));
						}
					}
					else if (node["action"] == "LOAD") {
						if (node["target"] == "ACTIVE") {
							filesystem.loadActiveConfig();
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: LOAD"), "Active Config", "");
							client.print(createHtmlResponse("200 OK", "Loaded Active config"));
						}
						else if (node["target"] == "DEFAULT") {
							filesystem.loadDefaultConfig();
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: LOAD"), "Default Config", "");
							client.print(createHtmlResponse("200 OK", "Loaded Default config"));
						}
					}
					else if (node["action"] == "RESET") {
						Setting::reset();
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: RESET"), "", "");
						client.print(createHtmlResponse("200 OK", "Factory Reset"));
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Action Object Action: UNKOWN"), "", "");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}
			}
			else {
				LOGMSG(F("[WebServer]"), F("ERROR: HTTP Request received"), "JSON parsing failed", "", "");
				client.print(createHtmlResponse("400 BAD REQUEST", "JSON parsing failed"));
			}
		}
		else {
			LOGMSG(F("[WebServer]"), F("ERROR: HTTP Request received"), "No payload", "", "");
			client.print(createHtmlResponse("400 BAD REQUEST", "No Payload"));
		}

		// give the web browser time to receive the data
		delay(200);
		// close the connection:
		client.stop();
		LOGMSG(F("[WebServer]"), F("OK: Client disconnected"), "@" + currenttime.createTime(), F("IPV4"), client.remoteIP());
	}
}