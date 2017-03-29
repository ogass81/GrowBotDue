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
	
	Serial.println(request);

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
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);
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
		Serial.println("Ok: New client connected");

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
		//Serial.println("Payload:");
		//Serial.println(request);

		if (payload == true) {
			JsonObject& node = jsonBuffer.parseObject(request);
			if (node.success()) {
				if (node["type"] == "Trigger" && node["cat"] != "" && node["id"] != "") {
					id = (int)node["id"];
					cat = (int)node["cat"];
					if (cat < TRIGCAT && id < TRIGNUMBER) {
						if (node["action"] == "GET") {
							trigger[cat][id]->serializeJSON(cat, id, json, 2500);
							Serial.println("Ok: Sending data via POST");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = trigger[cat][id]->deserializeJSON(node);
							Serial.print("Ok: Deserialized trigger " + (String)cat);
							Serial.println("|" + (String)id);
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else Serial.println("Error: No Action Method");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
					delay(100);
				}
				else if (node["type"] == "Rules" && node["id"] != "") {
					id = (int)node["id"];

					if (id < RULES) {
						if (node["action"] == "GET") {
							rulesets[id]->serializeJSON(id, json, 2500);
							Serial.println("Ok: Sending data via POST");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = rulesets[id]->deserializeJSON(node);
							Serial.print("Ok: Deserialized ruleset " + (String)id);
							Serial.println("|" + (String)id);
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else Serial.println("Error: No Action Method");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}
				else if (node["type"] == "Chain" && node["id"] != "") {
					id = (int)node["id"];

					if (id < ACTIONCHAINS) {
						if (node["action"] == "GET") {
							actionchains[id]->serializeJSON(id, json, 2500);
							Serial.println("Ok: Sending data via POST");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							success = actionchains[id]->deserializeJSON(node);
							Serial.print("Ok: Deserialized actionchain " + (String)id);
							Serial.println("|" + (String)id);
							client.print(createHtmlResponse("200 OK", "JSON received"));
						}
						else Serial.println("Error: No Action Method");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
				}
				else if (node["type"] == "Sensor" && node["id"] != "") {
					id = (int)node["id"];

					if (id < RULES) {
						if (node["action"] == "GET") {
							sensors[id]->serializeJSON(id, json, 2500);
							Serial.println("Ok: Sending data via POST");
							client.print(createPostRequest(json));
						}
						else if (node["action"] == "SET") {
							Serial.print("Error: SET for Sensor Object not supported");
							client.print(createHtmlResponse("501 NOT IMPLEMENTED ", "SET for Sensor Object not supported"));
						}
						else Serial.println("Error: No Action Method");
						client.print(createHtmlResponse("400 BAD REQUEST", "No Action Method"));
					}
					delay(150);
				}
				else {
					Serial.println("Error: Incomplete Request");
					client.print(createHtmlResponse("400 BAD REQUEST", "Incomplete Request"));
				}
			}
			Serial.println("Error: JSON parsing failed");
			client.print(createHtmlResponse("400 BAD REQUEST", "JSON parsing failed"));
		}
		else {
			Serial.println("Error: No Payload");
			client.print(createHtmlResponse("400 BAD REQUEST", "No Payload"));
		}
		
		// give the web browser time to receive the data
		delay(150);
		// close the connection:
		client.stop();
		Serial.println("Ok: Client disconnected");
	}
}
