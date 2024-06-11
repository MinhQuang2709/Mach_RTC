#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "FPT VinhNgoan";
const char* password = "huong12345@";

const char* mqtt_sever = "c945940064f44cb48e82d3daa7b6afa0.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user_name = "hivemq.webclient.1717815740196";
const char* mqtt_password = "dlVET1N:sa0?Ky6<H,w2";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi()
{
	Serial.println();
	Serial.print("connectinf to: ");
	Serial.print(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print('.');
	}
	randomSeed(micros());
	Serial.println("");
	Serial.print("Wifi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

void reconnect()
{
	while (!client.connected())
	{
		Serial.print("Attempting MQTT connection...");
		String clientID = "espClient-";
		clientID += String(random(0xffff), HEX);
		if (client.connect(clientID.c_str(), mqtt_user_name, mqtt_password))
		{
			Serial.println("connected");
			client.subscribe("esp32/client");
		}
		else
		{
			Serial.print("failed");
			Serial.print(client.state());
			Serial.println("try again in 5s");
			delay(5000);
		}
	}
}

void callBack(char* topic, byte* payload, unsigned int length)
{
	String incomingMessage = "";
	for (int i = 0; i < length; i++)
	{
		incomingMessage += (char)payload[i];
	}
	Serial.print("messagge arrived: (" + String(topic) + ") :");
	Serial.println(incomingMessage);
}

void publishMessage(char* topic, String payload, boolean retained)
{
	if (client.publish(topic, payload.c_str(), true))
	{
		Serial.println("publish message: (" + String(topic) + ") : " + payload);
	}
}

void setup()
{
	Serial.begin(9600);
	while (!Serial) delay(1);
	setup_wifi();
	espClient.setInsecure();
	client.setServer(mqtt_sever, mqtt_port);
	client.setCallback(callBack);
}

void loop()
{
	if (!client.connected())
	{
		reconnect();
	}
	client.loop();
	while (Serial.available() > 0) {
		String reading = Serial.readStringUntil('\n');
		if (reading.length() > 0) {
			publishMessage("esp32/test", reading, true);
		}
	}
}