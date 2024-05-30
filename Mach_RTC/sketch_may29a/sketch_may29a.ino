void setup()
{
  Serial.begin(9600);

}

void loop()
{
  while(Serial.available() > 0)
  {
    static char hoursInput[8];
    static char minutesInput[8];
    static char secondsInput[8];
    static char message[128];
    static unsigned int dem = 0;
    static int cntMinute = 0;
    static int cntSecond = 0;
    char inByte = Serial.read();

    if(inByte != '\n')
    {
      message[dem] = inByte;   
      if(dem <= 2)
      {
        hoursInput[dem] = inByte;
      }

      if (dem > 2 && dem < 5)
      {
        minutesInput[cntMinute] = inByte;
        cntMinute++;
      }

      if (dem > 5 && dem <=7)
      {
        secondsInput[cntSecond] = inByte;
        cntSecond++;
      }
      dem++;
    }

    else
    {
      hoursInput[2] = '\0';
      minutesInput[2] = '\0';
      secondsInput[2] = '\0';
      message[dem] = '\0';
      Serial.println(message);
      // for(int i=0; i<2; i++){
      //   Serial.print(hoursInput[i]);
      // }
      // Serial.println();

      int hours = atoi(hoursInput);
      int minutes = atoi(minutesInput);
      int seconds = atoi(secondsInput);
      Serial.println(hours);
      Serial.println(minutes);
      Serial.println(seconds);
      dem = 0;
      cntMinute = 0;
      cntSecond = 0;
    }
  }
}

//12 25 24