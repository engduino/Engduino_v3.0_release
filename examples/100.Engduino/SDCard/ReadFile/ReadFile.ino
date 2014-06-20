#include <EngduinoSD.h>

// Read content in file from SD Card
//
// In this sketch, content of the file stored on SD Card 
// is read and send to the serial terminal.
//

void setup()
{
  // See if the card is present and can be initialized:
  if(!EngduinoSD.begin())  
  {
    Serial.println("SD Card failed, or not present");
    while(1){;}; // don't do anything more
  }
  Serial.println("SD Card initialized.");
}

void loop() 
{  
  // Open the file for reading:
  EngduinoSD.open("logger.txt", FILE_READ);
  
  // read from the file until there's nothing else in it:
  while(EngduinoSD.available()) 
  {
    Serial.write(EngduinoSD.read());
    delay(1);
  }
  
  // close the file:
  EngduinoSD.close();
}

