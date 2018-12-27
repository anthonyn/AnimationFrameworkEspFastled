/*
 * An animation frame work for the ESP that includes
 * -
 * 
 */

#include "FastLED.h"


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


void setup() {
  //FaslLED Setup
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);

  //Wifi Setup





  //Framwwork Setup
  programCounter = 0;
}

void loop() {
  testAnimation();

  FastLED.show();
  FastLED.delay(1000 / framesPerSecond);
  programCounter++;
}

void testAnimation(){
  int pos = programCounter % NUM_LEDS;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[pos] = CRGB::Red;

}


