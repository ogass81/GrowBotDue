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

void parse_request(String row) {



}




void WebServer::checkConnection()
{
	WiFiEspClient client = this->available();

	//Incoming Data
	StaticJsonBuffer<2000> jsonBuffer;

	//Outgoing Data
	char json[2500];

	String line = "";
	int8_t line_count = 0;
	bool header = true;

	String http_method = "";
	String uri[REST_URI_DEPTH];
	int content_length = 0;
	String password = "";
	String payload = "";


	if (client == true) {
		LOGMSG(F("[WebServer]"), F("OK: New Client connected"), "@" + currenttime.createTime(), F("IPV4"), client.remoteIP());

		while (client.connected()) {
			if (client.available() > 0) {
				char c = client.read();
				line += c;


				if (line.endsWith("\n") && line != "\r\n") {
					if (line_count == 0) {

						String parts[3];
						int8_t i = 0;

						//Break up line in Command and Resource


						char temp[line.length() + 1];
						line.toCharArray(temp, line.length() + 1);
						char *token = strtok(temp, " ");

						while (token != NULL && i < 3) {
							parts[i] = token;
							token = strtok(NULL, " ");
							i++;
						}

						//Parse command
						if (parts[0] != NULL) {
							if ((parts[0].indexOf("GET")) > -1) {
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("HTTP Method detected"), F("GET"), "", "");
								http_method = "GET";
							}
							else if ((parts[0].indexOf("POST")) > -1) {
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("HTTP Method detected"), F("POST"), "", "");
								http_method = "POST";
							}
							else if ((parts[0].indexOf("PATCH")) > -1) {
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("HTTP Method detected"), F("PATCH"), "", "");
								http_method = "PATCH";
							}
						}

						//Parse URI
						if (parts[1] != NULL) {
							int8_t i = 0;

							char temp[parts[1].length() + 1];
							parts[1].toCharArray(temp, parts[1].length() + 1);
							char *token = strtok(temp, "/");

							while (token != NULL && i < REST_URI_DEPTH) {
								uri[i] = token;
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("URI Collection / Element found"), i, uri[i], "");
								token = strtok(NULL, "/");
								i++;
							}
						}
					}
					//Check for Authorization or other tags
					else {

						//Check for Authorization Token
						if (line.startsWith("authorization:")) {

							String parts[3];
							int8_t i = 0;

							//Break up line in Command and Resource
							char temp[line.length() + 1];
							line.toCharArray(temp, line.length() + 1);
							char *token = strtok(temp, " ");

							while (token != NULL && i < 3) {
								parts[i] = token;
								token = strtok(NULL, " ");
								i++;
							}

							if (parts[1] == "Basic" && parts[2] != NULL) {
								password = parts[2];
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("Authorization Token detected"), password, "", "");
							}
						}

						//Check for Content Length Token
						if (line.startsWith("content-length:")) {

							String parts[3];
							int8_t i = 0;

							//Break up line in Command and Resource
							char temp[line.length() + 1];
							line.toCharArray(temp, line.length() + 1);
							char *token = strtok(temp, " ");

							while (token != NULL && i < 3) {
								parts[i] = token;
								token = strtok(NULL, " ");
								i++;
							}

							if (parts[1] != NULL) {
								content_length = parts[1].toInt();
								LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("Content Lenght"), content_length, "", "");
							}
						}

					}
					line_count++;
					line = "";
				}
				//Detect Empty Line at end of header
				else if (line == "\r\n") {
					header = false;
					line = "";
					LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("End of HTTP Header detected"), "", "", "");
				}

				//Read Http Body
				if (header == false) {
					if (line.length() == content_length) {
						payload = line;
						LOGDEBUG2(F("[WebServer]"), F("checkConnection()"), F("Payload detected"), payload, "", "");
						break;
					}
				}
			}
		}

	
		/*
		if (payload == true) {
			JsonObject& node = jsonBuffer.parseObject(request);
			if (node.success()) {
				
				//Login Request
				//New API 18.07.2017
				if (node["type"] == "LOGIN") {
					if (node["action"] == "GET") {
						Setting::serializeConstantsJSON(json, 2500);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Constants Action: GET"), "", "");
						client.print(createPostRequest(json));
					}
				}
			
				//Trigger Request
				//New API 18.07.2017
				else if (node["type"] == "TRIGGER") {
					if (node["action"] == "GET") {
						if (node["cat"] != "") {
							cat = (int)node["cat"];
							if (node["id"] == "") {
								ListGenerator<Trigger> list(trigger[cat], TRIGGER_SETS);
								list.generateList(cat, json);
								client.print(createPostRequest(json));
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Trigger Action: GET"), F("List View"), "");
							}
							else if (node["id"] != "") {
								id = (int)node["id"];

								if (id < TRIGGER_SETS) {
									trigger[cat][id]->serializeJSON(cat, id, json, 2500, DETAILS);
									client.print(createPostRequest(json));
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Trigger Action: GET"), String(cat), String(id));
								}
								else {
									LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
									client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
								}
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No Category provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Category provided"));
						}
					}
					else if (node["action"] == "SET") {
						if (node["cat"] != "") {
							cat = (int)node["cat"];

							if (node["id"] != "") {
								id = (int)node["id"];

								if (id < TRIGGER_SETS) {
									success = trigger[cat][id]->deserializeJSON(node);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Trigger Action: SET"), String(cat), String(id));
									client.print(createHtmlResponse("200 OK", "JSON received"));
								}
								else {
									LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
									client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
								}
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
								client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No Category provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Category provided"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Actionchain Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "Unknow Action Method"));
					}
				}

			
				//Ruleset Request
				//New API 18.07.2017
				else if (node["type"] == "RULE") {
					if (node["action"] == "GET") {
						if (node["id"] == "") {
							ListGenerator<RuleSet> list(rulesets, RULESETS_NUM);
							list.generateList(json);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Ruleset Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RULESETS_NUM) {
								rulesets[id]->serializeJSON(id, json, 2500, DETAILS);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Ruleset Action: GET"), String(id), "");
								client.print(createPostRequest(json));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
					}
					else if (node["action"] == "SET") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RULESETS_NUM) {
								success = rulesets[id]->deserializeJSON(node);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Ruleset Action: SET"), String(id), "");
								client.print(createHtmlResponse("200 OK", "JSON received"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Ruleset Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "Unknow Action Method"));
					}
				}
				
				//ActionChain Request
				//New API 18.07.2017
				else if (node["type"] == "CHAIN") {
					if (node["action"] == "GET") {
						if (node["id"] == "") {
							ListGenerator<ActionChain> list(actionchains, ACTIONCHAINS_NUM);
							list.generateList(json);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actionchain Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < ACTIONCHAINS_NUM) {
								actionchains[id]->serializeJSON(id, json, 2500, DETAILS);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actionchain Action: GET"), String(id), "");
								client.print(createPostRequest(json));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
					}
					else if (node["action"] == "SET") {
						if(node["id"] != "") {
							id = (int)node["id"];

							if (id < ACTIONCHAINS_NUM) {
								success = actionchains[id]->deserializeJSON(node);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actionchain Action: SET"), String(id), "");
								client.print(createHtmlResponse("200 OK", "JSON received"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Actionchain Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "Unknow Action Method"));
					}
				}


				//RCSocket Request
				//New API 18.07.2017
				else if (node["type"] == "RCSOCKET") {
					if (node["action"] == "GET") {
						if (node["id"] == "") {
							ListGenerator<RCSocketController> list(&rcsocketcontroller, RC_SOCKETS);
							list.generateList(json);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: ### Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RC_SOCKETS) {
								rcsocketcontroller->serializeJSON(id, json, 2500, DETAILS);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: GET"), String(id), "");
								client.print(createPostRequest(json));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
					}
					else if (node["action"] == "SET") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RC_SOCKETS) {
								success = rcsocketcontroller->deserializeJSON(id, node);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: SET"), String(id), "");
								client.print(createHtmlResponse("200 OK", "JSON received"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else if (node["action"] == "LEARN") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RC_SOCKETS) {
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
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else if (node["action"] == "RESET") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < RC_SOCKETS) {
								rcsocketcontroller->resetSettings(id);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Socket Action: RESET"), String(id), "");
								client.print(createHtmlResponse("200 OK", "JSON received"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: RCSocket Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "Unknow Action Method"));
					}
				}
				
				
				//Sensor Request
				//New API 18.07.2017
				else if (node["type"] == "SENSOR") {
					if (node["action"] == "GET") {
						if (node["id"] == "") {
							ListGenerator<Sensor> list(sensors, SENS_NUM);
							list.generateList(json);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < SENS_NUM) {
								if (node["mode"] == "AVG") {
									sensors[id]->serializeJSON(id, json, 2500, AVG);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: AVG"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_MINUTE") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_MINUTE);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: MINUTE"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_HOUR") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_HOUR);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: HOUR"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_DAY") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_DAY);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: DAY"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_MONTH") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_MONTH);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: MONTH"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_YEAR") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_YEAR);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: YEAR"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DATE_ALL") {
									sensors[id]->serializeJSON(id, json, 2500, DATE_ALL);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: ALL"));
									client.print(createPostRequest(json));
								}
								else if (node["mode"] == "DETAILS") {
									sensors[id]->serializeJSON(id, json, 2500, DETAILS);
									LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), F("Mode: DETAILS"));
									client.print(createPostRequest(json));
								}
								else {
									LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Unknown mode"), String(id), "");
									client.print(createHtmlResponse("400 BAD REQUEST", "Unknown mode"));
								}
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
					}
					else if (node["action"] == "SET") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < SENS_NUM) {
								success = sensors[id]->deserializeJSON(node);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Remote Sensor Action: SET"), String(id), "");
								client.print(createHtmlResponse("200 OK", "JSON received"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else if (node["action"] == "LEARN") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < SENS_NUM) {
								if (node["mode"] == "LOWER") {
									sensors[id]->setLowerThreshold();
									client.print(createHtmlResponse("200 OK", "Set lower threshold"));
								}
								else if (node["mode"] == "UPPER") {
									sensors[id]->setUpperThreshold();
									client.print(createHtmlResponse("200 OK", "Set lower threshold"));
								}
								else {
									LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Unknown variable"), String(id), "");
									client.print(createHtmlResponse("400 BAD REQUEST", "Unknown variable"));
								}
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
								client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Sensor Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}

				//Action Request
				//New API 18.07.2017
				else if (node["type"] == "ACTION") {

					if (node["action"] == "GET") {
						if (node["id"] == "") {
							ListGenerator<Action> list(actions, ACTIONS_NUM);
							list.generateList(json);
							client.print(createPostRequest(json));
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Actions - Action: GET"), F("List View"), "");
						}
						else if (node["id"] != "") {
							id = (int)node["id"];

							if (id < ACTIONS_NUM) {
								actions[id]->serializeJSON(id, json, 2500, DETAILS);
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: GET"), String(id), "");
								client.print(createPostRequest(json));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
					}
					else if (node["action"] == "SET") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < ACTIONS_NUM) {
								LOGMSG(F("[WebServer]"), F("OK: Invalid HTTP Request"), F("Type: Action Object Action: SET "), "Not Supported", String(id));
								client.print(createHtmlResponse("501 NOT IMPLEMENTED ", "SET for Action Object not supported"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else if (node["action"] == "EXECUTE") {
						if (node["id"] != "") {
							id = (int)node["id"];

							if (id < ACTIONS_NUM) {
								actions[id]->execute();
								LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: EXECUTE"), String(id), "");
								client.print(createHtmlResponse("200 OK", "Executed action"));
							}
							else {
								LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: ID out of bound"), String(id), "");
								client.print(createHtmlResponse("400 BAD REQUEST", "ID out of bound"));
							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: No ID provided"), "", "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No ID provided"));
						}
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Action Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "Unknow Action Method"));
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

		*/

		// give the web browser time to receive the data
		delay(200);
		// close the connection:
		client.stop();
		LOGMSG(F("[WebServer]"), F("OK: Client disconnected"), "@" + currenttime.createTime(), F("IPV4"), client.remoteIP());
	}
}

template<class ObjectType>
ListGenerator<ObjectType>::ListGenerator(ObjectType **objects, int8_t num)
{
	this->objectarray = objects;
	this->object_count = num;

}

template<class ObjectType>
inline void ListGenerator<ObjectType>::generateList(char * json)
{
	String jsonarray = "{\"list\":[";

	for (uint8_t i = 0; i < object_count; i++) {
		objectarray[i]->serializeJSON(i, json, 2500, LIST);
		jsonarray += json;
		if (object_count - i > 1) {
			jsonarray += ",";
		}
		else jsonarray += "]}";
	}
	if (jsonarray.length() > 0) {
		jsonarray.toCharArray(json, jsonarray.length() + 1);
	}
}

template<class ObjectType>
void ListGenerator<ObjectType>::generateList(uint8_t cat, char * json)
{
	String jsonarray = "{\"list\":[";

	for (uint8_t i = 0; i < object_count; i++) {
		objectarray[i]->serializeJSON(cat, i, json, 2500, LIST);
		jsonarray += json;
		if (object_count - i > 1) {
			jsonarray += ",";
		}
		else jsonarray += "]}";
	}
	if (jsonarray.length() > 0) {
		jsonarray.toCharArray(json, jsonarray.length() + 1);
	}
}