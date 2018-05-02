const int button1 = 2;
int button1State = 0;
const int button2 = 3;
int button2State = 0;
const int button3 = 4;
int button3State = 0;
char byteRead;
String readString;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
}

void loop() {
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  Serial.print("Button 1: ");
  Serial.println(button1State);
  Serial.print("Button 2: ");
  Serial.println(button2State);
  Serial.print("Button 3: ");
  Serial.println(button3State);
  delay(1000);
  /*if (button1State == HIGH) 
  {
    Serial.println("Team 1 answered first.");
    Serial.println("Press <ENTER> key to continue.");
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    while (readString.length()==0) 
    {
      if (Serial.available()) 
      {
        byteRead = Serial.read();
        readString = byteRead;
      }
    }
    readString="";
    Serial.println("Reading: ");
  } 
  else if (button2State == HIGH) 
  {
    Serial.println("Team 2 answered first.");
    Serial.println("Press <ENTER> key to continue.");
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    while (readString.length()==0) 
    {
      if (Serial.available()) 
      {
        byteRead = Serial.read();
        readString = byteRead;
      }
    }
    readString="";
    Serial.println("Reading: ");
  }
  else if (button3State == HIGH) 
  {
    Serial.println("Team 3 answered first.");
    Serial.println("Press <ENTER> key to continue.");
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    while (readString.length()==0) 
    {
      if (Serial.available()) 
      {
        byteRead = Serial.read();
        readString = byteRead;
      }
    }
    readString="";
    Serial.println("Reading: ");
  }
  else {
    delay(1);
  }*/
}
