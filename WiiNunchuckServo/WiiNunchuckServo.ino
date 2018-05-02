
#include <Wire.h>
#include <WiiChuck.h>
#include <Servo.h>

Servo Elevation;
Servo Azimuth;
WiiChuck Chuck;

// adjust these values to find the servo center point
float ElevationPos = 90;
float AzimuthPos = 90;

void setup() {
  // attach servos to pins 9 and 10 (or any other PWM pins)
  Elevation.attach(9);
  Azimuth.attach(10);
  
  // attach WiiChuck to A4 and A5 (or SDA / SCL on the Uno)
  Chuck.begin();
  Chuck.update();
}

void loop() {
  // refresh the nunchuck's status
  Chuck.update();
  
  // joyY will be a value between 0 and 255. 0 = bottom, 255 = top
  // adjust it to -128 to 128, and then shrink it so it moves slowly enough
  // to adjust movement speed, change this 1000. a higher number moves more slowly
  ElevationPos += Chuck.joyY - 128 / 1000;
  // limit the movement of the servo. these might need adjustment if your servo 
  // can't handle this range
  ElevationPos = ElevationPos > 180 ? 180 : ElevationPos;
  ElevationPos = ElevationPos < 0 ? 0 : ElevationPos;
  
  // same thing with azimuth
  AzimuthPos += Chuck.joyX - 128 / 1000;
  AzimuthPos = AzimuthPos > 180 ? 180 : AzimuthPos;
  AzimuthPos = AzimuthPos < 0 ? 0 : AzimuthPos;
  
  // set the position of the servos
  Elevation.write(ElevationPos);
  Azimuth.write(AzimuthPos);
  
  // slow things down a little bit
  delay(10);
}
