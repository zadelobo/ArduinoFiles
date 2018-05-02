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


void setup()
{    
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  sensorvalues[counttoarray]=analogRead(sensorpin);
  /*if (sensorvalues[counttoarray]==0)
  {
    counttoarray--;
  }
  if (sensorvalues[counttoarray]!=0)
  {*/
    Serial.println(sensorvalues[counttoarray]);
  //}
  delay(10);
  if (sensorvalues[counttoarray]>greatestvalue)
  {
    Serial.println("Reset");
    //delay(1000);
    greatestvalue=sensorvalues[counttoarray];
    sensorvalues[0]=sensorvalues[counttoarray];
    counttoarray=0;
    Serial.println(sensorvalues[counttoarray]);
  }
  if (counttoarray>ARRAYNUM-2)
  {
    while (checkcount<ARRAYNUM-1)
    {
      if (sensorvalues[checkcount]<(pow(sensorvalues[checkcount-1],0.99)) && (sensorvalues[checkcount]>(pow(sensorvalues[checkcount-1],0.85))))
      {
        if (sensorvalues[checkcount-1]>100)
        {
          verified++;
          /*Serial.print("inside loop Verified: ");
          Serial.println(verified);
          Serial.println(sensorvalues[checkcount]);
          Serial.println(sensorvalues[checkcount-1]);*/
        }
      }
      if (sensorvalues[checkcount]>=400)
      {
        superveri++;
        /*Serial.print("inside extra loop Verified: ");
        Serial.println(superveri);
        Serial.println(sensorvalues[checkcount]);*/
      }
      checkcount++;
    }
    Serial.print("Verified: ");
    Serial.println(verified);
    Serial.print("Superverified: ");
    Serial.println(superveri);
    delay(1500);
    if ((verified>ARRAYNUM/25) && (verified<ARRAYNUM/10))//between 4 and 15 [15 to ignore a consistently high sound]
    {
      gunwasfired=true;
    }
    if ((verified>ARRAYNUM/63) && (verified<ARRAYNUM/25) && (superveri>5))
    {
      gunwasfired=true;
    }
    if (gunwasfired)
    {
      digitalWrite(13,HIGH);
      Serial.println("Gun! *****************");
      delay(1500);
      digitalWrite(13,LOW);
    }
    Serial.println("Start");
    verified=0;
    superveri=0;
    checkcount=0;
    gunwasfired=false;
    counttoarray=-1;
    greatestvalue=0;
  }
  counttoarray++;
}
