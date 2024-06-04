#include "readByte.h"

byte readByte()
{
    while (!Serial.available() > 0) delay(10);

    byte reading = 0;
    byte inputByte = Serial.read();
    while (inputByte != '\n')
    {
        if (inputByte >= '0' && inputByte <= '9')
        {
            reading = reading * 10 + (inputByte - '0');
        }
        else;
        inputByte = Serial.read();
    }
    Serial.flush();
    return reading;
}