#include <Adafruit_NeoPixel.h>

const int firstAnalogInPin = A9;  // Analog input pin that the potentiometer is attached to
const int secondAnalogInPin = A10;  
Adafruit_NeoPixel firstStrip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel secondStrip = Adafruit_NeoPixel(60, 12, NEO_GRB + NEO_KHZ800);
int sensorValue = 0;        // value read from the pot
int ssensorValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(9, INPUT_PULLUP); 
  pinMode(10, INPUT_PULLUP);
  firstStrip.begin();
  firstStrip.show(); // Initialize all pixels to 'off'
  secondStrip.begin();
  secondStrip.show(); // Initialize all pixels to 'off'
}

void loop() {

  /*************first red****************/
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);   
  if (sensorValue < 30){
  Serial.println("leds triggered"); 
  colorWipe(firstStrip.Color(255, 0, 0), 5);
  colorWipe(firstStrip.Color(0, 0, 0), 5);
  } 
  
  /*************second red****************/
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);   
  if (ssensorValue < 30){
  Serial.println("leds triggered"); 
  colorWipe(secondStrip.Color(255, 0, 0), 5);
  colorWipe(secondStrip.Color(0, 0, 0), 5);
  } 
 
  /*************first orange****************/
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
  if (sensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(firstStrip.Color(255, 100, 0), 5);
    colorWipe(firstStrip.Color(0, 0, 0), 5);
  }  
  
  /*************second orange****************/
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);  
  if (ssensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(secondStrip.Color(255, 100, 0), 5);
    colorWipe(secondStrip.Color(0, 0, 0), 5);
  }  
  
  /*************first yellow****************/
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
  if (sensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(firstStrip.Color(255, 255, 0), 5);
    colorWipe(firstStrip.Color(0, 0, 0), 5);
  }

  /*************second yellow****************/
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);  
  if (ssensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(secondStrip.Color(255, 255, 0), 5);
    colorWipe(secondStrip.Color(0, 0, 0), 5);
  }

  /*************first green****************/  
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
  if (sensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(firstStrip.Color(0, 255, 0), 5);
    colorWipe(firstStrip.Color(0, 0, 0), 5);
  }  

  /*************second green****************/  
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);  
  if (ssensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(secondStrip.Color(0, 255, 0), 5);
    colorWipe(secondStrip.Color(0, 0, 0), 5);
  }  
  
  /*************first blue****************/
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
  if (sensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(firstStrip.Color(0, 0, 255), 5);
    colorWipe(firstStrip.Color(0, 0, 0), 5);
  }  
  
  /*************second blue****************/
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);  
  if (ssensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(secondStrip.Color(0, 0, 255), 5);
    colorWipe(secondStrip.Color(0, 0, 0), 5);
  }  
 
  /*************first purple****************/
  sensorValue = analogRead(firstAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
  if (sensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(firstStrip.Color(255, 0, 255), 5);
    colorWipe(firstStrip.Color(0, 0, 0), 5);
  }
  
  /*************second purle****************/
  ssensorValue = analogRead(secondAnalogInPin);              
  Serial.print("sensor = " );                       
  Serial.println(ssensorValue);  
  if (ssensorValue < 30){
    Serial.println("leds triggered"); 
    colorWipe(secondStrip.Color(255, 0, 255), 5);
    colorWipe(secondStrip.Color(0, 0, 0), 5);
  }  
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<firstStrip.numPixels(); i++) {
      firstStrip.setPixelColor(i, c);
      firstStrip.show();
      delay(wait);
  }
}

