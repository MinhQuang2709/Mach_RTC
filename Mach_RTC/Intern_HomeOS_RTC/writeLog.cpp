#include "writeLog.h";
#include <SPI.h>
#include <SD.h>
File file;
char* logFile = "dateTime.txt";

void writeLog()
{
    file = SD.open(logFile, FILE_WRITE);
    file.print("the current date: ");
    file.print(days[weekDay - 2]);
    file.print(" - ");
    file.print(day);
    file.print('/');
    file.print(months[month - 1]);
    file.print('/');
    file.print("20");
    file.print(year);
    file.print(" - the current time: ");
    file.print(hour);
    file.print(':');
    file.print(bufferMinute);
    file.print(':');
    file.println(bufferSecond);
    file.close();
}