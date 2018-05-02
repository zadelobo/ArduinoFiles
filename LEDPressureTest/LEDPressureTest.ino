
#define LEDgreen 13
#define LEDred 12
int sensorpin = A0;
int sensorvalue = 0;
int speakerPin =8; //set up pin
void setup()
{    
  Serial.begin(9600);
  pinMode (LEDgreen, OUTPUT);  // pin mode setup pin 
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  while (sensorvalue>1000)
  {
    digitalWrite (LEDgreen, HIGH);
    sensorvalue=analogRead(sensorpin);
    Serial.println(sensorvalue);
  }
  digitalWrite (LEDgreen, LOW);
  
  while (sensorvalue<10)
  {
    digitalWrite (LEDred, HIGH);
    sensorvalue=analogRead(sensorpin);
    Serial.println(sensorvalue);
  }
  digitalWrite (LEDred, LOW);
  
}
