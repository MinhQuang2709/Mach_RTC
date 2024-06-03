#include "readTime.h"

const int DS1307 = 0x68;

byte bcdToDec(byte val)
{
    return ((val / 16 * 10) + (val % 16));
}

void readTime()
{
    Wire.beginTransmission(DS1307);
    Wire.write(byte(0));
    Wire.endTransmission();
    Wire.requestFrom(DS1307, 7);
    second = bcdToDec(Wire.read());
    minute = bcdToDec(Wire.read());
    hour = bcdToDec(Wire.read());
    weekDay = bcdToDec(Wire.read());
    day = bcdToDec(Wire.read());
    month = bcdToDec(Wire.read());
    year = bcdToDec(Wire.read());
}
