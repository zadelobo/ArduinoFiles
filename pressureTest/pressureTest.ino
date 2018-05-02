#define photon 3
int sensorpin = A0;
int sensorvalue = 0;
int speakerPin = 8; //set up pin
int melodyhot[] = {
  4186, 0, 4186, 0, 4186};
int noteDurations[] = {
  8,16,8,16,8,16};  
void setup()
{ 
  Serial.begin(9600);
  pinMode (photon, OUTPUT);  // pin mode setup pin
  digitalWrite(photon, HIGH);
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  Serial.println(sensorvalue);
  if (sensorvalue<95){
    for (int thisNote = 0; thisNote < 6; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melodyhot[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
  } 
  delay(10);
  
}
