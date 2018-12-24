#include <Ramp.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
uint32_t DURATION = 6000;

rampInt redRamp;
rampInt greenRamp;
rampInt blueRamp;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  redRamp.setGrain(1);
  greenRamp.setGrain(1);
  blueRamp.setGrain(1);
}

uint32_t red = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t purple = strip.Color(152, 0, 255);
uint32_t black = strip.Color(0, 0, 0);
uint32_t green = strip.Color(52, 187, 28);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(255, 232, 216);

void loop() {
  stripWipe(green, DURATION);
  
  for (int i = 0; i < strip.numPixels(); i += 1) {
    if (i % 2 == 0) {
      pixelWipe(i, black, DURATION / 6);
    } else {
      pixelWipe(i, white, DURATION / 6);
    }
  }

  for (int i = 0; i < strip.numPixels(); i += 1) {
    if (i % 2 == 0) {
      pixelWipe(i, blue, DURATION / 6);
    } else {
      pixelWipe(i, green, DURATION / 6);
    }
  }

  for (int i = 0; i < strip.numPixels(); i += 1) {
    if (i % 2 == 0) {
      pixelWipe(i, purple, DURATION / 6);
    } else {
      pixelWipe(i, blue, DURATION / 6);
    }
  }

  stripWipe(purple, DURATION);

  stripWipe(blue, DURATION / 2);

  for (int i = 0; i < strip.numPixels(); i += 1) {
    if (i % 2 == 0) {
      pixelWipe(i, red, DURATION / 6);
    } else {
      pixelWipe(i, black, DURATION / 6);
    }
  }

  stripWipe(green, DURATION / 2);

  stripWipe(yellow, DURATION);
}

void stripWipe(uint32_t c, uint32_t wait) {  
  for(uint8_t i = 0; i < strip.numPixels(); i+=1) {
    pixelWipe(i, c, wait);
  }
}

void pixelWipe(uint8_t i, uint32_t c, uint32_t wait) {
  redRamp.go(Red(strip.getPixelColor(i)));
  redRamp.go(Red(c), wait);

  greenRamp.go(Green(strip.getPixelColor(i)));
  greenRamp.go(Green(c), wait);

  blueRamp.go(Blue(strip.getPixelColor(i)));
  blueRamp.go(Blue(c), wait);

  while(
    !redRamp.isFinished() &&
    !greenRamp.isFinished() &&
    !blueRamp.isFinished()
  ) {
    strip.setPixelColor(i, strip.Color(
      redRamp.update(),
      greenRamp.update(),
      blueRamp.update()
    ));
    
    strip.show();
  }
}
