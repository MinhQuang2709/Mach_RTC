#include "setTime.h"

const int DS1307 = 0x68;

byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekDay = 0;
byte day = 0;
byte month = 0;
byte year = 0;

byte decToBcd(byte val)
{
    return ((val / 10 * 16) + (val % 10));
}

void setTime()
{
    Serial.print("enter the year: ");
    year = readByte();
    while (year < 10 || year > 99)
    {
        Serial.println();
        Serial.print("enter again the year: ");
        year = readByte();
    }
    Serial.println(year);
    Serial.print("enter the month(1-12): ");
    month = readByte();
    while (month < 1 || month > 12)
    {
        Serial.println();
        Serial.print("enter again the month: ");
        month = readByte();
    }
    Serial.println(month);
    Serial.print("enter the day: ");
    day = readByte();
    while (day < 1 || day > 31)
    {
        Serial.println();
        Serial.print("enter again the day: ");
        day = readByte();
    }
    Serial.println(day);
    Serial.print("enter the weekday(2-8): ");
    weekDay = readByte();
    while (weekDay < 2 || weekDay > 8)
    {
        Serial.println();
        Serial.print("enter again the weekday: ");
        weekDay = readByte();
    }
    Serial.println(weekDay);
    Serial.print("enter the hour: ");
    hour = readByte();
    while (hour < 0 || hour > 23)
    {
        Serial.println();
        Serial.print("enter again the hour: ");
        hour = readByte();
    }
    Serial.println(hour);
    Serial.print("enter the minute: ");
    minute = readByte();
    while (minute < 0 || minute > 59)
    {
        Serial.println();
        Serial.print("enter again the minute: ");
        minute = readByte();
    }
    Serial.println(minute);
    second = 0;
    Serial.println("set time success");

    Wire.beginTransmission(DS1307);
    Wire.write(byte(0));
    Wire.write(decToBcd(second));
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour));
    Wire.write(decToBcd(weekDay));
    Wire.write(decToBcd(day));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.write(byte(0));
    Wire.endTransmission();
}