#include "printTime.h"
#include "readTime.h"

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