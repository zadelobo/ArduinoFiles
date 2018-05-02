#define LED 13
int sensorpin = A0;
int sensorvalue = 0;
int sensorvalue1 = 0;
int sensorvalue2 = 0;
int sensorvalue3 = 0;
boolean touchedgen;
int speakerPin =8; //set up pin
void setup()
{    
  Serial.begin(9600);
  pinMode (LED, OUTPUT);  // pin mode setup pin 
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  pinMode(A0, INPUT_PULLUP);
  if (sensorvalue<900)
  {
    Serial.println("<---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON--->"); 
  }
  /*sensorvalue3=sensorvalue2;
  sensorvalue2=sensorvalue1;
  sensorvalue1=sensorvalue;
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  touchedgen1=touchedgen;
  touchedgen=(sensorvalue3==sensorvalue2 && sensorvalue2==sensorvalue1 && sensorvalue1==sensorvalue); 
  Serial.println("<---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON---ON--->"); 
  */
}
