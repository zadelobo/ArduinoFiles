int sensorpin = A0;
int sensorvalue = 0;
int checkvalueone = 0;
int checkcount = 0;
//#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(5, 4);
//Adafruit_GPS GPS(&mySerial);
//#define GPSECHO  true
#include <GSM.h>
#include <TinyGPS++.h>
#include <AltSoftSerial.h>
TinyGPSPlus gps;
AltSoftSerial ss;
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
boolean usingInterrupt = false;
void useInterrupt(boolean); 

void setup()  
{
  ss.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("GSM Initializing...");
  while (!Serial) {
  }
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } 
    else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");
}

void loop()                    
{
  checkcount=0;
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  if (sensorvalue>500)
  {
    delay(200);
    while(checkcount < 3)
    {
      checkvalueone=analogRead(sensorpin);
      Serial.println(checkvalueone);
      if (checkvalueone<(pow(sensorvalue,0.99)) && (checkvalueone>(pow(sensorvalue,0.85))))
      {
        if (gps.location.lat(), 6 != 0.000000) {
          digitalWrite(13,HIGH);
          Serial.print("Location (in degrees, works with Google Maps): ");
          Serial.print(gps.location.lat(), 6);
          Serial.print(", "); 
          Serial.println(gps.location.lng(), 6);
          Serial.println("SENDING MESSAGE");
          Serial.println();
          sms.beginSMS("14083403241");
          sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
          sms.print(gps.location.lat(), 6);
          sms.print(", ");
          sms.print(gps.location.lng(), 6);
          sms.endSMS();
          Serial.println("\nCOMPLETE!\n");
          delay(5000);
          digitalWrite(13,LOW);
        }
        if (gps.location.lat(), 6 == 0.000000) {
          Serial.println("No fix yet!"); 
          delay(5000);
        }
        checkcount=42;
      }
      checkcount++;
    } 
  }
}
