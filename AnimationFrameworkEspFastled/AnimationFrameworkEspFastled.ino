/*
   An animation frame work for the ESP that includes
   - Abstract animation class
   - wifi ap with webserver
   - Animation cycleing framework

*/

#include "FastLED.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//FastLED
FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    15
CRGB leds[NUM_LEDS];

int brightness = 255;
int framesPerSecond = 10;
long programCounter;

const char *ssid = "an";
const char *password = "12345678";
ESP8266WebServer server(80);

void setup() {
  delay(1000);
  Serial.begin(115200);

  //FaslLED Setup
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);

  //Wifi Setup
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");



  //Framwwork Setup
  programCounter = 0;
}

void loop() {

  testAnimation();
  doAnimation();
  doWebserver();

}

void doWebserver() {
  server.handleClient();
}

void doAnimation() {
  FastLED.show();
  FastLED.delay(1000 / framesPerSecond);
  programCounter++;
}

void testAnimation() {
  int pos = programCounter % NUM_LEDS;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[pos] = CRGB::Red;

}


