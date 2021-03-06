/*
 SMS sender
 
 This sketch, for the Arduino GSM shield,sends an SMS message 
 you enter in the serial monitor. Connect your Arduino with the 
 GSM shield and SIM card, open the serial monitor, and wait for 
 the "READY" message to appear in the monitor. Next, type a 
 message to send and press "return". Make sure the serial 
 monitor is set to send a newline when you press return.
 
 Circuit:
 * GSM shield 
 * SIM card that can send SMS
 
 created 25 Feb 2012
 by Tom Igoe
 
 This example is in the public domain.
 
 http://arduino.cc/en/Tutorial/GSMExamplesSendSMS
 
 */

// Include the GSM library
#include <GSM.h>
#include <Time.h>
#define PINNUMBER ""
#define LED 13
// wait before you sense in seconds
#define resetcount 20 
// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;
int sensorpin = A0;
int sensorvalue = 0;
int count = resetcount;
void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode (LED, OUTPUT);
  
  Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  digitalWrite (LED, HIGH);
  
  if (sensorvalue < 1)
  {
   // char remoteNum[20]; 
    /*Serial.print("Enter a mobile number: ");
     // telephone number to send sms
    readSerial(remoteNum);
    Serial.print("Returned from readSerial");
    Serial.println(remoteNum);
      
    // sms text
    Serial.print("Now, enter SMS content: ");
    char txtMsg[200];
    readSerial(txtMsg);*/
    //txtMsg="Hello Zayra, this is Zade's Arduino";
    digitalWrite (LED, LOW);
    Serial.println("SENDING");
    Serial.println();
    Serial.println("Message:");
    Serial.println("NIGHT GUARD ALERT: Senior has left his bed.");
   
    //sms.beginSMS("14082050308"); //assign phone number to send to.
    // send the message
    //sms.beginSMS(remoteNum);
    //sms.print("NIGHT GUARD ALERT: Senior has left his bed.");
    //sms.endSMS(); 
    Serial.println("\nCOMPLETE!\n");
    while (count>1){
      digitalWrite (LED, HIGH);
      delay(500);
      digitalWrite (LED, LOW);
      delay(500);
      count--;
    }
    count=resetcount;
  }
}

/*
  Read input serial
 */
int readSerial(char result[])
{
  int i = 0;
  Serial.println("I am in readSerial, before the while loop");
  while(1)
  {
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      if (inChar == '\n')
      {
        result[i] = '\0';
        Serial.flush(); 
        Serial.println("\n\nReturning from While");
        return 0;
      }
      if(inChar!='\r')
      {
        result[i] = inChar;
        i++;
      }
      //Serial.println("in readSerial Loop ");
      Serial.println(result[i]);
    }
  }
  
}
