int sensorpin = A0;
int sensorvalue = 0;
int checkvalueone = 0;
int checkcount = 0;
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 4);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
#include <GSM.h>
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
boolean usingInterrupt = false;
void useInterrupt(boolean); 

void setup()  
{
  Serial.begin(115200);
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
  Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  //mySerial.println(PMTK_Q_RELEASE);
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();

void loop()                    
{
  checkcount = 0;
  if (! usingInterrupt) {
    char c = GPS.read();
    //if (GPSECHO)
    //  if (c) Serial.print(c);
  }
  if (GPS.newNMEAreceived()) {
    Serial.println("*******************************************");
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }
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
        if (GPS.fix) {
          digitalWrite(13,HIGH);
          Serial.print("Location (in degrees, works with Google Maps): ");
          Serial.print(GPS.latitudeDegrees, 4);
          Serial.print(", "); 
          Serial.println(GPS.longitudeDegrees, 4);
          Serial.print("Number of satellites found: "); 
          Serial.println((int)GPS.satellites);
          Serial.println("SENDING MESSAGE");
          Serial.println();
          sms.beginSMS("14083403241");
          sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
          sms.print(GPS.latitudeDegrees, 4);
          sms.print(", ");
          sms.print(GPS.longitudeDegrees, 4);
          sms.endSMS();
          Serial.println("\nCOMPLETE!\n");
          delay(5000);
          digitalWrite(13,LOW);
        }
        if (! GPS.fix) {
          Serial.println("No fix yet!"); 
          delay(5000);
        }
        checkcount=42;
      }
      checkcount++;
    } 
  }
}
