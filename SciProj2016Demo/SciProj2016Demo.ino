#include <SoftwareSerial.h>
#include <GSM.h>
#include <Adafruit_GPS.h>
SoftwareSerial mySerial(9, 8);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  false
#define DEBUG true
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
boolean usingInterrupt = false;
void useInterrupt(boolean); 
char remoteNum[20] = "4083403241";  // telephone number to send to
int sensorpin = A0;
int sensorvalue = 0;
int checkvalueone = 0;
int checkcount = 0;
void setup()  
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  while (!Serial) {
  }
  Serial.println("Initializing GSM ...");
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
  //Serial.println(" GPS library  test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  //delay(1000);
  //mySerial.println(PMTK_Q_RELEASE);
  /* Serial.print("Enter a mobile number: ");
  readSerial(remoteNum);
  Serial.println(remoteNum);*/
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

/*
  Read input serial
 */
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

void loop()                    
{
  
  
  checkcount = 0;
  if (! usingInterrupt) {
    char c = GPS.read();
    //if (GPSECHO)
    //  if (c) Serial.print(c);
  }
  if (GPS.newNMEAreceived()) {
    //Serial.println("*******************************************");
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }
  sensorvalue=analogRead(sensorpin);
  
  if (DEBUG)
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
        digitalWrite(13,HIGH);
        delay(2000);
        digitalWrite(13,LOW);
        sms.beginSMS(remoteNum);
        sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
        sms.print("http://maps.google.com/?q=37.328457,-121.887113");
        //sms.print(GPS.latitudeDegrees, 4);
        //sms.print(",");
        //sms.print(GPS.longitudeDegrees, 4);
        sms.endSMS();
        Serial.println("\nCOMPLETE!\n");
        delay(1000);
        /*if (GPS.fix) 
        {
          Serial.print("Location URL, works with Google Maps: ");
          Serial.print("http://maps.google.com/?q=");
          Serial.print(GPS.latitudeDegrees, 4);
          Serial.print(","); 
          Serial.println(GPS.longitudeDegrees, 4);
          Serial.print("Number of satellites found: "); 
          Serial.println((int)GPS.satellites);
          Serial.println("SENDING MESSAGE to phone number ");
          Serial.println(remoteNum);
          Serial.println();
          //sms.beginSMS("14082054646");
          sms.beginSMS(remoteNum);
          
          sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
          sms.print("http://maps.google.com/?q=");
          sms.print(GPS.latitudeDegrees, 4);
          sms.print(",");
          sms.print(GPS.longitudeDegrees, 4);
          sms.endSMS();
          Serial.println("\nCOMPLETE!\n");
          delay(5000);
        }
        if (! GPS.fix) {
          Serial.println("No fix yet!"); 
          delay(5000);
        }*/
        checkcount=42;
      }
      checkcount++;
    } 
  }
}
