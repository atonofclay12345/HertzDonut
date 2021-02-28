#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/************ Network Information (CHANGE THESE FOR YOUR SETUP) ************************/
const char* ssid = "network name";
const char* password = "password";

const char* sensor_name = "NodeMCU";
const char* ota_password = "no";

const bool static_ip = true;
IPAddress ip(128, 61, 27, 115);
IPAddress gateway(128, 61, 16, 1);
IPAddress subnet(255, 255, 240, 0);

const int udp_port = 7778;

//global
WiFiUDP port;

void setup() {
  Serial.begin(115200);
  // Setup the wifi connection
  setup_wifi();

  // Setup OTA firmware updates
  setup_ota();

  // Initialize the UDP port
  port.begin(udp_port);

}

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  if (static_ip) {
    WiFi.config(ip, gateway, subnet);
  }
  
  WiFi.hostname(sensor_name);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_ota() {
  ArduinoOTA.setHostname(sensor_name);
  ArduinoOTA.setPassword(ota_password);

  ArduinoOTA.onStart([]() {
    Serial.println("Starting");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}
