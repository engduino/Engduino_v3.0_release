#include <EngduinoSD.h>
#include <EngduinoThermistor.h>
#include <EngduinoLEDs.h>

// Data logger
//
// In this sketch, temperature value is saved on the SD Card every
// second. SD Card is initialized in auto open-close mode, which
// takes care on opening and closing file before and after write.
//
// The sketch illustrates the use of both SD Card and thermistor.
//

void setup()
{
  // See if the card is present and can be initialized:
  // Card is initializeed in auto open-close mode.
  // Driver itself will takes care to open and close file
  // before and after write.
  EngduinoLEDs.begin();
  if(!EngduinoSD.begin("logger.txt", FILE_WRITE))  
  {
    EngduinoLEDs.setAll(RED);
    Serial.println("SD Card failed, or not present");
    while(1){;}; // don't do anything more
  }
  Serial.println("SD Card initialized.");
  
  // Initialize thermistor.
  EngduinoThermistor.begin();
}

void loop() 
{  
  // Make a string for assembling the data to log:
  String dataString = "Temp is: ";
  
  // Get the temperature:
  float t = EngduinoThermistor.temperature();

  // Append value to the string:
  dataString += String((int)t);

  
  if(EngduinoSD.writeln(dataString))
  {
    Serial.println("Write done!");
    EngduinoLEDs.setAll(GREEN);
    }
  else
  {
    Serial.println("Write error!");
    EngduinoLEDs.setAll(RED);
  }
  
  delay(500);
  EngduinoLEDs.setAll(OFF);
}

