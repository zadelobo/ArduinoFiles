int sensorpin = A0;
int checkcount = 1;
int greatestvalue = 0;
#define ARRAYNUM 250
int sensorvalues[ARRAYNUM];
int counttoarray = 0;
int counttocheck = 0;
int verified = 0;
boolean loudsound = false;


void setup()
{    
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
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
        if (sensorvalues[checkcount-1]>10)
        {
          verified++;
          Serial.print("inside loop Verified: ");
          Serial.println(verified);
          Serial.println(sensorvalues[checkcount]);
          Serial.println(sensorvalues[checkcount-1]);
        }
      }
      checkcount++;
    }
    Serial.print("Verified: ");
    Serial.println(verified);
    delay(1500);
    if (verified>ARRAYNUM/16.667)
    {
      //if (sensorvalues[0]>600)
      //{
        digitalWrite(13,HIGH);
        Serial.println("Gun! *****************");
      //}
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
