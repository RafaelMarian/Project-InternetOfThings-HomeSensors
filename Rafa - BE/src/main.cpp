#include <Wire.h>
#include "Adafruit_VEML6070.h"
#include <WiFi.h>
#include "ThingSpeak.h"
#include <Adafruit_Sensor.h>

#define CHANEL_ID 
#define CHANEL_WRITE_API_KEY ""

WiFiClient client;

#define WIFI_TIMEOUT_MS 35000

#define WIFI_NETWORK ""
#define WIFI_PASSWORD ""

void connectToWiFi()
{
  Serial.print("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(" Failed!");
  }
  else
  {
    Serial.print(" Connected!");
    Serial.println(WiFi.localIP());
  }
}

Adafruit_VEML6070 uv = Adafruit_VEML6070();

void setup()
{
  Serial.begin(9600);

  Serial.println("VEML6070 Test");
  uv.begin(VEML6070_1_T);

  connectToWiFi();
  ThingSpeak.begin(client);
}

void loop()
{
  int uvValue = uv.readUV();
  Serial.print("UV light level: ");
  Serial.println(uvValue);

  delay(1000);

  ThingSpeak.setField(1, uvValue);

  ThingSpeak.writeFields(CHANEL_ID, CHANEL_WRITE_API_KEY);
}