/*******************************************************************************************
"Body-Guard"
An Engineering Fair Project by Zade Lobo
Mr. Chihiro Ikezi
Saint Francis High School

Includes:
GSM Shield
GPS Breakout
Sound Sensor


This code is meant for the use of Zade Lobo only. Please respect privacy rights.  
*******************************************************************************************/

//definition of all of the variables, vectors, and objects used throughout the program
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
int sensorpin = A0;
int checkcount = 1;
int greatestvalue = 0;
#define ARRAYNUM 250
int sensorvalues[ARRAYNUM];
int counttoarray = 0;
int counttocheck = 0;
int verified = 0;
int superveri = 0;
boolean gunwasfired = false;

//setup is where the program is strating to initialize. In this section: 
//1. The GSM Shield is turned on and connected to the local cell towers
//2. The GPS is prompted to start searching for satellites. This process may not be 
//   completed now. 
//3. The baud rate is set for all serial port funtions. 
//4. The port 13 is set to OUTPUT for the buzzer. 
void setup()  
{
  Serial.begin(115200);//The baud rate is the speed at which the Arduino sends information
                       //back to the computer. The compute must also be told the same rate.
  pinMode(13, OUTPUT);//The digital pin 13 is set to output so that it can be used with
                      //the buzzer. 
  while (!Serial) {
  }
  Serial.println("Initializing GSM ...");
  boolean notConnected = true;
  //connect GSM shield to cell towers
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) 
    {
      notConnected = false;
    } 
    else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");
  GPS.begin(9600);//baud rate of the GPS
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);//set the update rate of the GPS
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
}

//The following are functions used by the GPS to interpret the information it receives from 
//the satellites.

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

//The loop is where all of the action happens. The Signal Processing algorithm, 
//the text message sending, and coordinate retrieving happen here. 

void loop()
{
  //Parse through the last GPS signal to get the coordinates. 
  if (! usingInterrupt) {
    char c = GPS.read();
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }
  sensorvalues[counttoarray]=analogRead(sensorpin);//Store sensor value in the next 
                                                   //available spot in the vector
  Serial.println(sensorvalues[counttoarray]);//print the value in the serial monitor
  delay(10);//wait for 10 milliseconds
  if (sensorvalues[counttoarray]>greatestvalue)//Peak-Detecting Algorithm
  {
    Serial.println("Reset");
    greatestvalue=sensorvalues[counttoarray];//Store the peak as the first value in the 
                                             //vector
    sensorvalues[0]=sensorvalues[counttoarray];
    counttoarray=0;
    Serial.println(sensorvalues[counttoarray]);
  }
  if (counttoarray>ARRAYNUM-2)//enter only once the array has been completely filled
  {
    while (checkcount<ARRAYNUM-1)//Slope Comparison Algorithm
    {                            //Repeat for every neigboring pair of two in the vector
      if (sensorvalues[checkcount]<(pow(sensorvalues[checkcount-1],0.99)) && (sensorvalues[checkcount]>(pow(sensorvalues[checkcount-1],0.85))))
      {//if the pair of two follows the prescribed slope
        if (sensorvalues[checkcount-1]>100)//make sure the value was large enough
        {
          verified++;//increase the confidence index
        }
      }
      if (sensorvalues[checkcount]>=400)//if the value is a secondary peak
      {
        superveri++;//raise the number of secondary peaks
      }
      checkcount++;
    }
    Serial.print("Verified: ");
    Serial.println(verified);
    Serial.print("Superverified: ");
    Serial.println(superveri);
    delay(1500);
    if ((verified>ARRAYNUM/25) && (verified<ARRAYNUM/10))//between 4 and 15 [15 to ignore a consistently high sound]
    {//if the confidence index passed the set threshold
      gunwasfired=true;
    }
    if ((verified>ARRAYNUM/63) && (verified<ARRAYNUM/25) && (superveri>5))
    {//if the confidence index was close to passing the threshold, but there were enough
     //secondary peaks
      gunwasfired=true;
    }
    if (gunwasfired)
    {
      if (GPS.fix)
      {
        digitalWrite(13,HIGH);//start buzzer
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
        sms.beginSMS("14083403241");//phone number
        //text message contents
        sms.print("Relaying Coordinates from Body-Guard Backpack #42: ");
        sms.print("http://maps.google.com/?q=");//generated coordinates URL
        sms.print(GPS.latitudeDegrees, 4);
        sms.print(",");
        sms.print(GPS.longitudeDegrees, 4);
        sms.endSMS();//send message
        Serial.println("\nCOMPLETE!\n");
        delay(5000);
        digitalWrite(13,LOW);//stop buzzer
      }
      if (! GPS.fix) 
      {//can't send a message if it has no coordinates!
        Serial.println("No fix yet!"); 
        delay(5000);
      }
    }
    Serial.println("Start");
    //reset variables needed
    verified=0;
    superveri=0;
    checkcount=0;
    gunwasfired=false;
    counttoarray=-1;
    greatestvalue=0;
  }
  counttoarray++;
}
