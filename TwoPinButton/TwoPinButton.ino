void setup() 
{
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  Serial.println("Reading...");
}

void loop() 
{
  if (digitalRead(8) == LOW)
  {
    Serial.println("TTTTTTTTTTTTTTTT   EEEEEEEEEEEEEE            AA            MM            MM                    11     ");
    Serial.println("       TT          EE                       AAAA           MMMM        MMMM                  1111     ");
    Serial.println("       TT          EE                      AA  AA          MM  MM    MM  MM                 11 11     ");
    Serial.println("       TT          EE                     AA    AA         MM   MM  MM   MM                11  11     ");
    Serial.println("       TT          EEEEEEEEE             AA      AA        MM     MM     MM                    11     ");
    Serial.println("       TT          EE                   AAAAAAAAAAAA       MM            MM                    11     ");
    Serial.println("       TT          EE                  AA          AA      MM            MM                    11     ");
    Serial.println("       TT          EE                 AA            AA     MM            MM                    11     ");
    Serial.println("       TT          EE                AA              AA    MM            MM                    11     ");
    Serial.println("       TT          EEEEEEEEEEEEEE   AA                AA   MM            MM               111111111111");
    Serial.println("Waiting for administrator...");
    while (digitalRead(5) == HIGH)
    {
      delay(1);
    }
    while (digitalRead(5) == LOW)
    {
      delay(1);
    }
    Serial.println("Reading...");
  }
  if (digitalRead(9) == LOW)
  {
    Serial.println("TTTTTTTTTTTTTTTT   EEEEEEEEEEEEEE            AA            MM            MM                  2222222  ");
    Serial.println("       TT          EE                       AAAA           MMMM        MMMM                 22     22 ");
    Serial.println("       TT          EE                      AA  AA          MM  MM    MM  MM               22        22");
    Serial.println("       TT          EE                     AA    AA         MM   MM  MM   MM               22        22");
    Serial.println("       TT          EEEEEEEEE             AA      AA        MM     MM     MM                       22  ");
    Serial.println("       TT          EE                   AAAAAAAAAAAA       MM            MM                     22    ");
    Serial.println("       TT          EE                  AA          AA      MM            MM                   22      ");
    Serial.println("       TT          EE                 AA            AA     MM            MM                 22        ");
    Serial.println("       TT          EE                AA              AA    MM            MM                22         ");
    Serial.println("       TT          EEEEEEEEEEEEEE   AA                AA   MM            MM               222222222222");
    Serial.println("Waiting for administrator...");
    while (digitalRead(5) == HIGH)
    {
      delay(1);
    }
    while (digitalRead(5) == LOW)
    {
      delay(1);
    }
    Serial.println("Reading...");
  }
  if (digitalRead(10) == LOW)
  {
    Serial.println("TTTTTTTTTTTTTTTT   EEEEEEEEEEEEEE            AA            MM            MM                 33333333333  ");
    Serial.println("       TT          EE                       AAAA           MMMM        MMMM                33         33 ");
    Serial.println("       TT          EE                      AA  AA          MM  MM    MM  MM               33           33");
    Serial.println("       TT          EE                     AA    AA         MM   MM  MM   MM                           33 ");
    Serial.println("       TT          EEEEEEEEE             AA      AA        MM     MM     MM                      333333  ");
    Serial.println("       TT          EE                   AAAAAAAAAAAA       MM            MM                           33 ");
    Serial.println("       TT          EE                  AA          AA      MM            MM                            33");
    Serial.println("       TT          EE                 AA            AA     MM            MM               33           33");
    Serial.println("       TT          EE                AA              AA    MM            MM                33         33 ");
    Serial.println("       TT          EEEEEEEEEEEEEE   AA                AA   MM            MM                 33333333333  ");
    Serial.println("Waiting for administrator...");
    while (digitalRead(5) == HIGH)
    {
      delay(1);
    }
    while (digitalRead(5) == LOW)
    {
      delay(1);
    }
    Serial.println("Reading...");
  }
  delay(1);
}
