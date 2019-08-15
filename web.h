// All code for handling the self hosted web server interface is here.

#pragma once

// Replace with your network credentials
const char* ssid = "ESP32_Master";
const char* password = "";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

////////////////////////////

void setupWeb()
{

	// Initialize SPIFFS
	if (!SPIFFS.begin(true)) {
		Serial.println("An Error has occurred while mounting SPIFFS");
		return;
	}

	// Connect to Wi-Fi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	// Print ESP32 Local IP Address
	Serial.println(WiFi.localIP());

	// Route for root / web page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
		request->send(SPIFFS, "/index.html");
		});

	server.on("/input", HTTP_GET, [](AsyncWebServerRequest * request) {
		String result;
		if (request->hasParam("power")) {
			result = request->getParam("power")->value();
			Serial.println("power : " + result);

		}
		else if (request->hasParam("pattern")) {
			result = request->getParam("pattern")->value();
			Serial.println("pattern : " + result);

		}
		else if (request->hasParam("brightness")) {
			result = request->getParam("brightness")->value();
			Serial.println("brightness : " + result);

		}
		else if (request->hasParam("speed")) {
			result = request->getParam("speed")->value();
			Serial.println("speed : " + result);

		}
		else if (request->hasParam("hue")) {
			result = request->getParam("hue")->value();
			Serial.println("hue : " + result);

		}
		else if (request->hasParam("hueSpeed")) {
			result = request->getParam("hueSpeed")->value();
			Serial.println("hueSpeed : " + result);

		}
		else if (request->hasParam("offset")) {
			result = request->getParam("offset")->value();
			Serial.println("offset : " + result);

		}
		else {
			result = "No message sent";
		}
		//request->send(200, "text/plain", "Hello, GET: " + message);

		});

	// Start server
	server.begin();
}
