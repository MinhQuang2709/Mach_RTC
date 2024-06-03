#include "readByte.h"
#include "setTime.h"
#include "readTime.h"
#include "WriteLog.h";
#include <WIRE.h>;
#include <SD.h>
#include <SPI.h>

File file;
char* logFile = "dateTime.txt";

const int DS1307 = 0x68;

bool flag = false;
bool check = false;

const char* days[] =
{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
const char* months[] =
{ "January", "February", "Match", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

char bufferMinute[3];
char bufferSecond[3];

byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekDay = 0;
byte day = 0;
byte month = 0;
byte year = 0;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    while (!Serial)
    {

    }
    Serial.println("Initializing SD card...");
    delay(1000);
    if (!SD.begin(4))
    {
        Serial.println("faile to connect with SD card");
    }
    else
    {
        Serial.println("initialization done");
    }

    delay(1000);
    SD.remove(logFile);
    file = SD.open(logFile, FILE_WRITE);
    if (!file)
    {
        Serial.println("log file missing");
        flag = false;
    }
    else
    {
        Serial.println("prepare to receive data");
        flag = true;
    }
    file.close();
}

void printTime()
{
    readTime();
    Serial.print("the current date: ");
    Serial.print(days[weekDay - 2]);
    Serial.print(" - ");
    Serial.print(day);
    Serial.print('/');
    Serial.print(months[month - 1]);
    Serial.print('/');
    Serial.print("20");
    Serial.print(year);
    Serial.print(" - the current time: ");
    Serial.print(hour);
    Serial.print(':');
    sprintf(bufferMinute, "%02d", minute);
    sprintf(bufferSecond, "%02d", second);
    Serial.print(bufferMinute);
    Serial.print(':');
    Serial.print(bufferSecond);
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
        printTime();
        Serial.println();

        // if (flag == true)
        // {
        //     writeLog();

        // }

        delay(1000);
        if (Serial.available() > 0)
        {
            check = false;
        }
    }
}