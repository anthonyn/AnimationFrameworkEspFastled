#include <Arduino.h>
#include "FastLED.h"
#include "config.h"

class Animation {
  protected:
    long c;
    int incVal;
    CRGB* leds;
  public:
    Animation() {
      incVal = 1;
    };
    virtual void doDraw();
    void test() {
      Serial.println("Printing from Animation");
    };
};

class TestAnimation :  public Animation
{
  public:
    TestAnimation(CRGB* _leds) {
      leds = _leds;
      c = 0;
      incVal = 5;
    };
    void doDraw() {

      int val = c % 255;
      //fill_solid(leds, NUM_LEDS, CRGB::Black);
      leds[0] = CRGB(val, 0, 0);
      Serial.println(c);
      c += incVal;
    };
};

//      int pos = c % NUM_LEDS;
//      fill_solid(leds, NUM_LEDS, CRGB::Black);
//      leds[pos] = CRGB::Green;
//      c++;

