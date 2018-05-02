 #include "pitches.h"
const int temperaturePin = 0;
int melodyhot[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int noteDurations[] = {
  4,8,8,4,4,4,4,4 };
int noteDurationsc[] = {
  4,4,8,4,4,8,2,8,4,4};
int melodycold[] = {
  NOTE_A3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_D4, NOTE_A3, NOTE_F4};
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  float voltage, degreesC, degreesF;
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.println(degreesF);
  delay(2000);
  if (degreesF > 80)
  {
    Serial.print("Hot!");
    for (int thisNote = 0; thisNote < 8; thisNote++) {

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
  if (degreesF < 70)
  {
    Serial.print("Cold!");
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurationsc[thisNote];
    tone(8, melodycold[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
  }
}
float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

