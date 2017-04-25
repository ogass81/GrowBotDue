// 
// 
// 

#include "Network.h"

String WebServer::createPostRequest(char *json)
{
	String load, request;

	load = String(json)+"\r\n";
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
				if (node["type"] == "TRIGGER" && node["cat"] != "" && node["id"] != "") {
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
					delay(100);
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
						else if (node["action"] == "LEARN") {
							if (node["mode"] == "ON") {
								//TBD
							}
							else if (node["mode"] == "OFF") {
								//TBD

							}
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Remote Socket Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
				}

				else if (node["type"] == "SENSOR" && node["id"] != "") {
					id = (int)node["id"];

					if (id < SENS_NUM) {
						if (node["action"] == "GET") {
							sensors[id]->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Sensor Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							LOGMSG(F("[WebServer]"), F("OK: Invalid HTTP Request"), F("Type: Sensor Action: SET "), "Not Supported", String(id));
							client.print(createHtmlResponse("501 NOT IMPLEMENTED ", "SET for Sensor Object not supported"));
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Sensor Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
					delay(150);
				}
				else if (node["type"] == "ACTION" && node["id"] != "") {
					id = (int)node["id"];

					if (id < SENS_NUM) {
						if (node["action"] == "GET") {
							actions[id]->serializeJSON(id, json, 2500);
							LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: GET"), String(id), "");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							LOGMSG(F("[WebServer]"), F("OK: Invalid HTTP Request"), F("Type: Action Object Action: SET "), "Not Supported", String(id));
							client.print(createHtmlResponse("501 NOT IMPLEMENTED ", "SET for Action Object not supported"));
						}
						else {
							LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Action Object Action: UNKOWN"), String(id), "");
							client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
						}
					}
					delay(150);
				}
				else if (node["type"] == "SETTINGS") {
					if (node["action"] == "GET") {
						Setting::serializeJSON(json, 2500);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Action Object Action: GET"), String(id), "");
						client.print(createPostRequest(json));
					}
					else if (node["action"] == "SET") {
						success = Setting::deserializeJSON(node);
						LOGMSG(F("[WebServer]"), F("OK: Valid HTTP Request"), F("Type: Settings Action: SET"), String(id), "");
						client.print(createHtmlResponse("200 OK", "JSON received"));
					}
					else {
						LOGMSG(F("[WebServer]"), F("ERROR: Invalid HTTP Request"), F("Type: Action Object Action: UNKOWN"), String(id), "");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}
				delay(150);
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
		delay(10);
		// close the connection:
		client.stop();
		LOGMSG(F("[WebServer]"), F("OK: Client disconnected"), "@" + currenttime.createTime(), F("IPV4"), client.remoteIP());
	}
}