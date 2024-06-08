#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Arduino.h>
#include "readByte.h"

File file;
const int DS1307 = 0x68;

bool check = false;

char bufferMinute[3];
char bufferSecond[3];

byte second = 0;
byte minute = 0;
byte hour = 0;
byte day = 0;
byte month = 0;
byte year = 0;

RTC_DS1307 rtc;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(4, OUTPUT);

    SD.remove("dateTime.txt");

    if (!SD.begin(4))
    {
        Serial.println("failed to connect with SD");
        return;
    }

    if (!rtc.begin())
    {
        Serial.println("failed to init RTC");
    }

    if (!rtc.isrunning())
    {
        Serial.println("RTC is not running! Make sure you have set the time for the RTC.");
    }

    Serial.println("The SD card and RTC have been initialized");
    readByte();
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

    rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

void printTime(DateTime dt)
{
    Serial.print(dt.year(), DEC);
    Serial.print('/');
    Serial.print(dt.month(), DEC);
    Serial.print('/');
    Serial.print(dt.day(), DEC);
    Serial.print(" ");
    Serial.print(dt.hour(), DEC);
    Serial.print(':');
    Serial.print(dt.minute(), DEC);
    Serial.print(':');
    Serial.print(dt.second(), DEC);
    Serial.println();
}

void loop()
{
    Serial.println("you want set time(y/n): ");
    while (!Serial.available()) delay(10);
    if (Serial.read() == 'y' || Serial.read() == 'Y')
    {
        Serial.read();
        setTime();
        check = true;
    }
    while (check == true)
    {
        DateTime now = rtc.now();
        Serial.print("The current dateTime: ");
        printTime(now);

        String dataString = "";
        dataString += String(now.year(), DEC);
        dataString += "/";
        dataString += String(now.month(), DEC);
        dataString += "/";
        dataString += String(now.day(), DEC);
        dataString += " ";
        dataString += String(now.hour(), DEC);
        dataString += ":";
        dataString += String(now.minute(), DEC);
        dataString += ":";
        dataString += String(now.second(), DEC);

        File dataFile = SD.open("dateTime.txt", FILE_WRITE);
        if (dataFile) {




            dataFile.println(dataString);
            dataFile.close();
        }
        else {
            Serial.println("failed to open dateTime.txt");
        }

        delay(1000);

        if (Serial.available() > 0)
        {
            check = false;
        }
    }

}
