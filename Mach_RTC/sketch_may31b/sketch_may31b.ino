#include <Wire.h>
#include <SPI.h>
#include <SD.h>

File myFile;

bool check;
const int DS1307 = 0x68;
const char* days[] = 
{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char* months[] = 
{"January", "February", "Match", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekDay = 0;
byte day = 0;
byte month = 0;
byte year = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  while(!Serial)
  {

  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while(1);
  }

  Serial.println("initialization done");
  SD.remove("dateTime.txt");
  myFile = SD.open("dateTime.txt", FILE_WRITE);

  if (!myFile)
  {
    Serial.println("log file missing");
    while(1);
  }
  file.close();
}

void printTime()
{
  char bufferMinute[3];
  char bufferSecond[3];
  readTime();
  Serial.print("the current date: ");
  Serial.print(days[weekDay-2]);
  Serial.print(" - ");
  Serial.print(day);
  Serial.print('/');
  Serial.print(months[month-1]);
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

void writeLog()
{
  myFile = SD.open("dateTime.txt", FILE_WRITE);
  file.print("H/M/S: ");
  file.print()
}
byte decToBcd(byte val)
{
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val)
{
  return ((val/16*10) + (val%16));
}

byte readByte()
{
  while(!Serial.available() > 0)
  {
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
}
void loop() {
  // put your main code here, to run repeatedly:
  check = 1;
  Serial.println("You want settime: Y/N");
  while(!Serial.available())
  {
    delay(10);
  }
  if (Serial.read() == 'y' || Serial.read() == 'Y')
  {
    Serial.read();
    setTime();
    while (check == 1)
    {
      printTime();
      Serial.println();
      delay(1000);
      if(Serial.available() > 0)
      {
        check = 0;
      }
    } 
  }
  else
  {
    Serial.println("failed to set time");
    Serial.print("Enter again: ");
  }
}
