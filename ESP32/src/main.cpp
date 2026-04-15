#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "data.cpp"
#include "effects.cpp"

#define PIN 13
#define NUM_PIXELS 9

// string that will be filled with the received string
String incomingString = "";

// initialize lights and effects
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
Effects effects;

void setup() {
   Serial.begin(115200);
}

void loop() {

   // Update effects
   effects.Update();

   // if there is something coming in on the serial port
   if (Serial.available() > 0)
   {
      // the string that came in on the serial port
      String incomingString = Serial.readStringUntil('\n');

      // send the string to be split
      EventData eventData(incomingString);
      
      // the split string used for light effects
      if (eventData.type == "Light")
      {
        
      }

      // the split string used for smoke effects
      else if (eventData.type == "Smoke")
      {
         effects.SmokeOn(eventData.targetId, eventData.duration);
      }
   }
}