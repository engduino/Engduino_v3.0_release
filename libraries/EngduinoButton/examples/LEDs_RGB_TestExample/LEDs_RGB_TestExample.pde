#include <LEDs_RGB.h>

// Engduino RGB LEDs test library
// by Jan Medvesek <jan.medvesek@gmail.com>
// Created 5 April 2013

// Functional test of the RGB LEDs on the Engduino board.


void setup()
{
  LEDs_RGB.begin(); 
}

void loop()
{
  LEDs_RGB.setRed(LED_RGB_10 | LED_RGB_11);
  delay(500);
  LEDs_RGB.setRGB(LED_RGB_10 | LED_RGB_11, LED_RGB_2 | LED_RGB_14, LED_RGB_7 | LED_RGB_1);
  delay(500);
  LEDs_RGB.toggleRGB();
  delay(500);
}

