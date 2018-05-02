#include <GSM.h>
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } 
    else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");

  // sending part
  Serial.println("SENDING MESSAGE");
  Serial.println();

  // send the message
  sms.beginSMS("14083403241");
  sms.print("Relaying Coordinates from Body-Guard Backpack #42: ...");
  sms.endSMS();
  Serial.println("\nCOMPLETE!\n");
}

void loop() {
  
}

int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
