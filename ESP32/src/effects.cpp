#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//smoke backside
#define K2 32
//smoke frontside
#define K1 15

class Effects
{
   public:
        // smoke variables
        unsigned long smokeStartTimeK1 = 0;
        unsigned long smokeStartTimeK2 = 0;
        unsigned long smokeOffTimeK1 = 0;
        unsigned long smokeOffTimeK2 = 0;
        bool smokeActiveK1 = false;
        bool smokeActiveK2 = false;

        Effects()
        {   
            // intitializes smoke
            pinMode(K1, OUTPUT);
            pinMode(K2, OUTPUT);
            digitalWrite(K1, HIGH);
            digitalWrite(K2, HIGH);
        }

        // tracks the time so it knows when to turn smoke off
        void Update()
        {
            unsigned long now = millis();

            // if the time has passed or is equal to the time it needs to turn off, it turns off the smoke
            if (smokeActiveK1 && now >= smokeOffTimeK1)
            {
                digitalWrite(K1, HIGH);
                smokeActiveK1 = false;
            }

            // if the time has passed or is equal to the time it needs to turn off, it turns off the smoke
            if (smokeActiveK2 && now >= smokeOffTimeK2)
            {
                digitalWrite(K2, HIGH);
                smokeActiveK2 = false;
            }
        }

        // turns the smoke on, looks at where and how long to turn it on
        void SmokeOn(int targetId, float duration)
        {
            // keeps track of the current time that has passed
            unsigned long now = millis();
            // 160ms delay because of hardware limitations
            unsigned long warmup = 160;
            unsigned long onTime = now + warmup;
            // how long it takes to turn off 
            unsigned long offTime = onTime + (unsigned long)(duration * 1000);

            // turns all smoke on
            if (targetId == 0)
            {
                digitalWrite(K1, LOW);
                digitalWrite(K2, LOW);

                smokeOffTimeK1 = offTime;
                smokeOffTimeK2 = offTime;

                smokeActiveK1 = true;
                smokeActiveK2 = true;
            }

            // turns on smoke in the front
            else if (targetId == 1)
            {
                digitalWrite(K1, LOW);

                smokeOffTimeK1 = offTime;
                smokeActiveK1 = true;
            }

            // turns on smoke in the back
            else if (targetId == 2)
            {
                digitalWrite(K2, LOW);

                smokeOffTimeK2 = offTime;
                smokeActiveK2 = true;
            }
        }
};