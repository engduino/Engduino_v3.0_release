#include <EngduinoIR.h>
#include <EngduinoLEDs.h>

// Communications test
// Press button on the sender, and it will flash blue
// The receiver will flash green if it receives the msg
// correctly, and red if not.
//


int buttonState     = HIGH;  // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin

// the following variables are longs because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;   // the last time the output pin was toggled
long debounceDelay    = 50;  // the debounce time; increase if the output flickers

long count = 0;

void setup()
{
  EngduinoIR.begin();  
  EngduinoLEDs.begin();
  pinMode(BUTTON, INPUT);
  EngduinoLEDs.setAll(off);
}

void loop() {
  int      len = 0;
  uint8_t  buf[RAWBUF];
  char *msg = "Hello world";

  // Debounce button:
  int reading = digitalRead(BUTTON);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Send a message and flash the LEDs
        //
        EngduinoIR.send(msg, strlen(msg)+1);

        EngduinoLEDs.setAll(blue);
        delay(50);
        EngduinoLEDs.setAll(off);
        delay(50);
      }
    }
  }

  lastButtonState = reading;

  // See if there's a message to read - wait 50ms

  len = EngduinoIR.recv(buf, 1000);
  if (len < 0) {
    count++;
    if (count%1000 == 0) {
      Serial.print(".");
      if (count%80000 == 0) {
        count = 0;
        Serial.println("");
      }
    }
  }
  else {
    Serial.println("");
    Serial.print("Data [");
    Serial.print(len, DEC);
    Serial.print("]: ");  
    for (int i=0; i<len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(", ");
    }
    Serial.println("");

    if (len > 1) {
      Serial.println((char *)buf);
    }

    if (!strcmp((char *)buf, "Hello world")) {
      EngduinoLEDs.setAll(green);
      delay(50);
      EngduinoLEDs.setAll(off);
      delay(50);    
    }
    else {
      EngduinoLEDs.setAll(red);
      delay(50);
      EngduinoLEDs.setAll(off);
      delay(50);
    }

  }

}



