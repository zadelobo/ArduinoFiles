int sensorpin = A0;
int sensorvalue = 0;
int checkvalueone = 0;
int checkcount = 0;

void setup()
{    
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}



void loop()
{
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  checkcount=0;
  if (sensorvalue>500)
  {
    while(checkcount < 4000)
    {
      delay(1);
      checkvalueone=analogRead(sensorpin);
      Serial.println(checkvalueone);
      /*if (checkvalueone<(pow(sensorvalue,0.99)) && (checkvalueone>(pow(sensorvalue,0.85))))
      {
        Serial.println("Bullseye!");
        delay(5000);
        checkcount=42;
      }*/
      if (checkcount%200==0)
      {
        Serial.println("*********");
      }
      checkcount++;
    }
  }
}
