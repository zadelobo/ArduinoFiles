#include <GSM.h>
#define PINNUMBER ""
#define LED 13
int sensorpin = A0;
int sensorvalue = 0;
unsigned long starttime;
int highvalue;
int lowvalue;
unsigned long time;
GSM gsmAccess;
GSM_SMS sms;
int count;
void setup()
{
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode (LED, OUTPUT);
  digitalWrite(LED, HIGH);//LED signals that the program has begun
  delay(500);
  digitalWrite(LED, LOW);
  
  // When the program starts, the shield has not connected to the cell phone 
  // tower yet. 
  boolean notConnected = true;

  // Start GSM shield
  // This checks whether the SIM card is able to send texts and connects it to 
  // the tower. 
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      delay(1000);
    }
  }
  digitalWrite(LED, HIGH); //LED signals that the GSM has been initialized
  delay(500);
  digitalWrite(LED, LOW);
}

void loop() //this part of the program loops itself
{
  sensorvalue=analogRead(sensorpin);//Reads in the value given by mat
  time=millis();//The amount of milliseconds since the program started is stored
  if (sensorvalue>800) // Checks for a high value
  {
     highvalue=sensorvalue;//Stores the high value in a variable
     starttime=millis();//Takes the time at that moment and records it as the 
                        //time that the high value was stored
     count=0;
     while (time - starttime < 10000)//Checks whether it has been 10 second 
                                     //since the high value was stored
     {
       time=millis();//Resets the current time value
       sensorvalue=analogRead(sensorpin);//Reads in the value given by the mat
       lowvalue=sensorvalue;//Takes in the sensor value and stores it
       if (count>0)//Once the program sends a text once, this is used to prevent
                   //it from sending multiple. 
       {
         break;
       }
       if (highvalue-lowvalue>600)//Checks if the gap between the two values are
                                  //great enough. 
       {
         digitalWrite (LED, HIGH);//LED signals that it has sensed the senior on
                                  //the mat
         delay(500);
         digitalWrite (LED, LOW);
         sms.beginSMS("14083403241"); //phone number the text is sent to
         sms.print("NIGHT GUARD ALERT: Senior has left his bed."); 
         //message sent out
         sms.endSMS(); 
         digitalWrite (LED, HIGH);//LED signals that text has been sent
         delay(500);
         count++;
       }
     }
     digitalWrite (LED, LOW);
  }
  
}
