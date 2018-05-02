#include <TinyGPS++.h> 
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
}

void loop() {
  /*Serial.print("Coordinates: ");
  Serial.print(gps.location.lat(), 6);
  Serial.print(", ");
  Serial.println(gps.location.lng(), 6);
  delay(250);
  Serial.println("*");
  delay(250);*/
  Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
  Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
  Serial.print("ALT=");  Serial.println(gps.altitude.meters());
}
