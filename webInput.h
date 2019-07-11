#pragma once

// WiFi network name and password:
const char * networkName = "ESP_Master";
const char * networkPswd = "ESP_Secure_Password";

//bool timeout = false;
//long int try_again_time = millis() + 60000 * 5;

//const char * networkName = "seejayjames";
//const char * networkPswd = "qwerty22";

//const char* networkName = "Trap House";
//const char* networkPswd = "ThIsHoUsEisatrap72";

//IP address to send UDP data to:
// either use the ip address of the server or
// a network broadcast address
//String udpAddress = "192.168.0.255"; // not used in this version, we are only receiving UDP
int udpPort = 33333;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;
char incomingPacket[255];  // buffer for incoming packets
//char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


//wifi event handler
// uncommented in original
void WiFiEvent(WiFiEvent_t event) {
	
	startTime("WiFiEvent");

	switch (event) {

	case SYSTEM_EVENT_STA_GOT_IP:
		//When connected set
		Serial.print("WiFi connected! IP address: ");
		Serial.println(WiFi.localIP());
		//initializes the UDP state
		//This initializes the transfer buffer
		udp.begin(WiFi.localIP(), udpPort);
		connected = true;

		universe.uAutoplay = false;

		break;
	case SYSTEM_EVENT_STA_DISCONNECTED:
		Serial.println("WiFi lost connection");
		
		connected = false;

		break;
	default:
		break;
	}

	endTime("WiFiEvent");

}

void connectToWiFi(const char* ssid, const char* pwd) { // was const char * for both in originial
	Serial.println("Connecting to WiFi network: " + String(ssid));

	//WiFi.persistent(false); // trying something from online
	WiFi.mode(WIFI_STA);
	//WiFi.mode(WIFI_AP_STA);
	//WiFi.mode(WIFI_AP);

	//timeout = false;

	while(connected == false )//&& timeout == false)
	{
		//universe.uAutoplay = false;

		static long int time = millis();

		//static long int timeout_time = millis() + 10000;

		if (millis() > time + 2500)
		{
			// delete old config
			WiFi.disconnect(); // passed "true" in original
			//register event handler
			
			WiFi.onEvent(WiFiEvent); // uncommented in original

			WiFi.enableSTA(true);

			//Initiate connection
			WiFi.begin(ssid, pwd);

			time = millis();
		}

		//if (millis() > timeout_time)
		//{
		//	timeout = true;
		//	try_again_time = millis() + 60000 * 5;
		//	universe.uAutoplay = true;
		//}

	}

	WiFi.setSleep(false);

	Serial.println("Waiting for WIFI connection...");
}

void setupWeb()
{
	//Connect to the WiFi network
	connectToWiFi(networkName, networkPswd);
}



void handleWeb() {
	//only send data when connected
	//startTime("handleWeb NOT CONNECTED YET");

	if (connected) {

		//startTime("handleWeb CONNECTED");

		int packetSize = udp.parsePacket();
		if (packetSize)
		{

			//middleTime("handleWeb");

			// receive incoming UDP packets
			//Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
			int len = udp.read(incomingPacket, 255);
			if (len > 0)
			{
				incomingPacket[len] = 0; // don't know why this is here
			}
			//Serial.printf("UDP packet contents: %s\n", incomingPacket); // Original
			// I had some issues with casting types using Serial.printf(), use Serial.println() instead

			//middleTime("handleWeb");

			String valueFromPacket = String(incomingPacket); // cast incomingPacket char array to String to use substring()
			//Serial.println("UDP packet contents: " + valueFromPacket);
			// Format coming in: "brt 127" = brightness 127 = first value char is at position 4 (counts from 0)
			int value = valueFromPacket.substring(4, 7).toInt(); // positions 4, 5, and 6 (doesn't include 7)
			// Use this to set the actual parameters, but for Serial.println() they need to be cast to Strings

			//middleTime("handleWeb");

			if (valueFromPacket.substring(0, 3) == "brt")
			{
				universe.uBrightness = value;
				Serial.println("Brightness = " + String(value));
			}
			else if (valueFromPacket.substring(0, 3) == "spd")
			{
				universe.ChangeSpeedFactor((float)value/40);
				Serial.println("Speed = " + String(value));
			}
			else if (valueFromPacket.substring(0, 3) == "hue")
			{
				universe.SetHue(value);
				Serial.println("Hue = " + String(value));
			}
			else if (valueFromPacket.substring(0, 3) == "hsp")
			{
				universe.ChangeHueFactor((float)value/80);
				Serial.println("Hue Speed = " + String(value));
			}
			else if (valueFromPacket.substring(0, 3) == "off")
			{
				universe.ChangeOffset(value);
				Serial.println("Offset = " + String(value));
			}
			else if (valueFromPacket.substring(0, 3) == "b00")
			{
				universe.NextPattern();
			}
			else if (valueFromPacket.substring(0, 3) == "b01")
			{
				universe.PrevPattern();
			}
			else if (valueFromPacket.substring(0, 3) == "t00")
			{
				universe.uAutoplay = (bool)value;
				//universe.ToggleAutoplay();
			}
			else if (valueFromPacket.substring(0, 3) == "b04")
			{
				universe.NextHue();
			}
			else if (valueFromPacket.substring(0, 3) == "b05")
			{
				universe.RandomHue();
			}
			else if (valueFromPacket.substring(0, 3) == "str")
			{
				universe.uStrobeTime = value;
			}
			else if (valueFromPacket.substring(0, 3) == "t01")
			{
				universe.uStrobe = (bool)value;
			}
			else if (valueFromPacket.substring(0, 3) == "b06")
			{
				universe.uFlash = (bool)value;
			}
			else if (valueFromPacket.substring(0, 3) == "b07")
			{
				ESP.restart();
			}
			else if (valueFromPacket.substring(0, 3) == "b02")
			{
				universe.ChangeReflect();
			}
			else if (valueFromPacket.substring(0, 3) == "pat")
			{
				universe.SetPattern(value);
			}
			else if (valueFromPacket.substring(0, 3) == "act")
			{
				universe.uPower = (bool)value;
			}
			else if (valueFromPacket.substring(0, 3) == "b03")
			{
				universe.uSlowStart = millis();
				universe.uSlow = (bool)value;
			}
			else if (valueFromPacket.substring(0, 3) == "del")
			{
				universe.uSlowDelay = value;
			}

			//middleTime("handleWeb");

			Serial.println(valueFromPacket);

		}
		//endTime("handleWeb CONNECTED");

	}
	else
	{
		//if (millis() > try_again_time)
		//{
		universe.uAutoplay = true;
		connectToWiFi(networkName, networkPswd);
		//}
	}
	//endTime("handleWeb NOT CONNECTED YET");

	// Testing for number/string formatting (UPD sends strings only so will need to get numbers from string)
	//String temp1 = "127";
	//String temp2 = "10";
	//int tempResult = temp1.toInt() + temp2.toInt();
	//Serial.println(tempResult); // works, prints 137

	//Tweak this for responsiveness, seems to handle 50ms just fine with the serial monitor
	//delay(100);

}