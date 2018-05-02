#include "Adafruit_NeoPixel.h"

/*****************************************************************************
Example sketch for driving Adafruit Flora pixels
Connect the pixel(s) to Digital 6 (low right hand)
*****************************************************************************/

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60,5,NEO_GRB+NEO_KHZ800);

void setup() {
    
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels

  colorWipe(strip.Color(255, 0, 0), 2);
  colorWipe(strip.Color(0, 0, 0), 2);
  delay(500);
  colorWipe(strip.Color(0, 255, 0), 2);
  colorWipe(strip.Color(0, 0, 0), 2);
  delay(500);
  colorWipe(strip.Color(0, 0, 255), 2);
  colorWipe(strip.Color(0, 0, 0), 2);
  delay(500);


}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
static colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
/*RGBPixel Color(byte r, byte g, byte b)
{
  RGBPixel p;
  
  p.red = r;
  p.green = g;
  p.blue = b;
  
  return p;
}*/

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
static Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
