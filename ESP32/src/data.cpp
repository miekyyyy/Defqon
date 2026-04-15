#include <Arduino.h>
#include <vector>

class EventData
{
    public:
        // temporary storage of the string after its been split
        std::vector<String> tempStorage;

        // variables
        String type;
        int targetId;
        String lightEffectType;
        bool inverted;
        float colorR;
        float colorG;
        float colorB;
        float colorA;
        float duration;

        // sets the variables to a parsed light effect
        void parseLightEffect()
        {  
            if (tempStorage.size() >= 9)
            {
                type = tempStorage[0];
                targetId = tempStorage[1].toInt();
                lightEffectType = tempStorage[2];
                inverted = (tempStorage[3] == "1");
                colorR = tempStorage[4].toFloat();
                colorG = tempStorage[5].toFloat();
                colorB= tempStorage[6].toFloat();
                colorA = tempStorage[7].toFloat();
                duration = tempStorage[8].toFloat();
            }
        }

        // sets the variables to a parsed smoke effect
        void parseSmokeEffect()
        {  
            if (tempStorage.size() >= 3)
            {
                type = tempStorage[0];
                targetId = tempStorage[1].toInt();
                duration = tempStorage[2].toFloat();
            }
        }

        // Constructor that parses the send string
        EventData(String data)
        {
            String tempData;
            int index = 0;
            // splits string at ","
            while(data.indexOf(',') != -1)
            {
                tempData = data.substring(0, data.indexOf(','));
                tempStorage.push_back(tempData);
                data = data.substring(data.indexOf(',') + 1);
                index++; 
            }

            // temporary data is the current split string and then pushes it in the list
            tempData = data;
            tempStorage.push_back(tempData);

            // set variables to the parsed ones
            if (!tempStorage.empty())
            {
                if (tempStorage[0] == "Light")
                {
                    parseLightEffect();
                }
                else if (tempStorage[0] == "Smoke")
                {
                    parseSmokeEffect();
                }
            }
        }
};

