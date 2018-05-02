#include <Adafruit_NeoPixel.h>

#define PIN 12
#define PIN 13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(1, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  strip.Color(255, 255, 255); //white
  strip2.Color(0, 0, 255); //blue
}
