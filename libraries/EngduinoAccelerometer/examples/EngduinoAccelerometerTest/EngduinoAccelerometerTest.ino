#include <EngduinoAccelerometer.h>
#include <Wire.h>

void setup()
{
  EngduinoAccelerometer.begin();
}

void loop()
{ float xyz[3];

  // Read the acceleration
  //
  EngduinoAccelerometer.xyz(xyz);
  
  // And print the result, in g
  //
  Serial.print("XYZ: [");
  for (int i = 0; i < 3; i++) {
    Serial.print(xyz[i]);
    Serial.print(", ");
  }
  Serial.println("]");
  
  // Wait a bit, and loop
  //
  delay(1000);
}
