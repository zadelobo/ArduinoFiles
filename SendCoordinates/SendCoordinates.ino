int sensorpin = A0;
int sensorvalue = 0;
int checkvalueone = 0;
int checkcount = 0;
#include <AltSoftSerial.h>
#include <TinyGPS++.h> 
//#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(5, 4);
TinyGPSPlus gps;
#define GPSECHO  true
#include <GSM.h>
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
boolean usingInterrupt = false;
void useInterrupt(boolean); 
AltSoftSerial ss;

void setup()  
{
  ss.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
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

  sms.beginSMS("14083403241"); // begin an sms to the sender number
  sms.print(gps.location.lat(), 6); // append the lat to the sms
  sms.print(", "); // append a comma
  sms.print(gps.location.lng(), 6); // append the lon to the sms
  sms.endSMS(); //send the sms
}

void loop(){

}


