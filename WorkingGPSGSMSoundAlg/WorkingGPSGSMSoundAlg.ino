#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <GSM.h>
SoftwareSerial mySerial(9, 8);
Adafruit_GPS GPS(&mySerial);
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
boolean usingInterrupt = false;
void useInterrupt(boolean); 
//char remoteNum[20];  // telephone number to send to
int sensorpin = A0;
int checkcount = 1;
int greatestvalue = 0;
#define ARRAYNUM 50
int sensorvalues[ARRAYNUM];
int counttoarray = 0;
int counttocheck = 0;
int verified = 0;

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
  //Serial.print("Enter a mobile number: ");
  //readSerial(remoteNum);
  //Serial.println(remoteNum);
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
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
  if (! usingInterrupt) {
    char c = GPS.read();
  }
  if (GPS.newNMEAreceived()) {
    //Serial.println("*******************************************");
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }

  sensorvalues[counttoarray]=analogRead(sensorpin);
  Serial.println(sensorvalues[counttoarray]);
  delay(10);
  if (sensorvalues[counttoarray]>greatestvalue)
  {
    Serial.println("Reset");
    //delay(1000);
    greatestvalue=sensorvalues[counttoarray];
    sensorvalues[0]=sensorvalues[counttoarray];
    counttoarray=0;
  }
  if (counttoarray>ARRAYNUM-2)
  {
    while (checkcount<ARRAYNUM-1)
    {
      if (sensorvalues[checkcount]<(pow(sensorvalues[checkcount-1],0.99)) && (sensorvalues[checkcount]>(pow(sensorvalues[checkcount-1],0.85))))
      {
        verified++;
      }
      checkcount++;
    }
    Serial.print("Verified: ");
    Serial.println(verified);
    delay(1500);
    if (verified>ARRAYNUM/16.667)
    {
      if (sensorvalues[0]>600)
      {
        if (GPS.fix)
        {
          digitalWrite(13,HIGH);
          Serial.print("Location URL, works with Google Maps: ");
          Serial.print("http://maps.google.com/?q=");
          Serial.print(GPS.latitudeDegrees, 4);
          Serial.print(", "); 
          Serial.println(GPS.longitudeDegrees, 4);
          Serial.print("Number of satellites found: "); 
          Serial.println((int)GPS.satellites);
          Serial.println("SENDING MESSAGE to phone number ");
          Serial.println("1-(408)-340-3241");
          Serial.println();
          sms.beginSMS("14083403241");
          //sms.beginSMS(remoteNum);
          sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
          sms.print("http://maps.google.com/?q=");
          sms.print(GPS.latitudeDegrees, 4);
          sms.print(",");
          sms.print(GPS.longitudeDegrees, 4);
          sms.endSMS();
          Serial.println("\nCOMPLETE!\n");
          delay(5000);
          digitalWrite(13,LOW);
        }
        if (! GPS.fix) 
        {
          Serial.println("No fix yet!"); 
          delay(5000);
        }
      }
      delay(1500);
      digitalWrite(13,LOW);
    }
    Serial.println("Start");
    verified=0;
    checkcount=0;
    counttoarray=-1;
    greatestvalue=0;
  }
  counttoarray++;
}

