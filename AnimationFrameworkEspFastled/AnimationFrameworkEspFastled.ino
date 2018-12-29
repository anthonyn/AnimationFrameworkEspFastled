/*
   An animation frame work for the ESP that includes
   - Abstract animation class
   - wifi ap with webserver
   - Animation cycleing framework

*/

#include "Animation.cpp"

#include "FastLED.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Secrets.h"
#include "config.h"

//FastLED
FASTLED_USING_NAMESPACE
CRGB leds[NUM_LEDS];


int brightness = 255;
int framesPerSecond = 10;
long programCounter;

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

TestAnimation ta(leds);

Animation *a = &ta;

void loop() {

  //  testAnimation();


  //ta.doDraw();

  a->doDraw();
//  a->test();


  doAnimation();
  doWebserver();

  programCounter++;
}

void doWebserver() {
  server.handleClient();
}

void doAnimation() {
  FastLED.show();
  FastLED.delay(1000 / framesPerSecond);
}

void testAnimation() {
  int pos = programCounter % NUM_LEDS;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[pos] = CRGB::Red;

}

