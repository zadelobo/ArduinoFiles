#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
 
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
}
 
void loop() {
  // read the analog in value:            
  // print the results to the serial monitor:    
  for (int j = 50; j >=0; j--)
  {
    colorWipe(strip.Color(j*2.05, j, j*1.08), 0);
    delay(2);
  }    
  for (int i = 0; i <=50; i++)
  {
    colorWipe(strip.Color(i*2.05, i, i*1.08), 0);
    delay(2);
  }      
}

void fadeColors(int r, int g, int b, int wait)
{
  if (r > b && r > g)
  {
    double ratio1 = r/g;
    double ratio2 = r/b;
    for (int j = 50; j >=0; j--)
    {
      colorWipe(strip.Color(j, j*rtogratio, j*1.08), 0);
      delay(2);
    }    
    for (int i = 0; i <=50; i++)
    {
      colorWipe(strip.Color(i*2.05, i, i*1.08), 0);
      delay(2);
    }      
  }

  if (b > r && b > g)
  {
    double ratio1 = b/r;
    double ratio2 = b/g;
  }

  if (g > b && g > r)
  {
    double ratio1 = r/g;
    double ratio2 = r/b;
  }
  
  for (int j = 50; j >=0; j--)
  {
    colorWipe(strip.Color(j, j*rtogratio, j*1.08), 0);
    delay(2);
  }    
  for (int i = 0; i <=50; i++)
  {
    colorWipe(strip.Color(i*2.05, i, i*1.08), 0);
    delay(2);
  }      
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
