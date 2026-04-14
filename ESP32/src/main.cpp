#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "data.cpp"
#define PIN 13 // Pin connected to DIN
#define NUM_PIXELS 9 // Number of LEDs in the strip

String faaah;

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   Serial.begin(115200);
   EventData("je,moeder,is,bol");
}
void loop() {
   for (int i = 0; i < NUM_PIXELS; i++) {
       strip.setPixelColor(i, strip.Color(255, 255, 0)); // Red color
       strip.show();
       delay(100);
   }
   delay(1000);
   strip.clear();
   strip.show();
   delay(1000);
}