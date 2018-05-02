#include <Adafruit_NeoPixel.h>
 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
int sensorValue = 0;        // value read from the pot
 
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void loop() {
  // read the analog in value:
  colorWipe(strip.Color(255, 0, 0), 25);
  colorWipe(strip.Color(0, 0, 0), 25);
  
}  
