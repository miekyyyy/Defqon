#include <Arduino.h>
#include <vector>

class EventData
{
    private:
        // Parsed variables
        String type;
        int targetId;
        String lightEffectType;
        float colorR;
        float colorG;
        float colorB;
        float colorA;
        float duration;

    public:
        std::vector<String> tempStorage;
        
        void parseLightEffect()
        {  
            if (tempStorage.size() == 8 && tempStorage[0] == "Light")
            {
                type = tempStorage[0];
                targetId = tempStorage[1].toInt();
                lightEffectType = tempStorage[2];
                colorR = tempStorage[3].toFloat();
                colorG = tempStorage[4].toFloat();
                colorB= tempStorage[5].toFloat();
                colorA = tempStorage[6].toFloat();
                duration = tempStorage[7].toFloat();
            }
        }

        // Constructor that parses the send string
        EventData(String& data)
        {
            String tempData;
            int index = 0;
            while(data.indexOf(',') != -1)
            {
                tempData = data.substring(0, data.indexOf(','));
                tempStorage.push_back(tempData);
                data = data.substring(data.indexOf(',') + 1);
                index++; 
            }

            tempData = data;
            tempStorage.push_back(tempData);

            // set variables to the parsed ones
            parseLightEffect();
        }
};

