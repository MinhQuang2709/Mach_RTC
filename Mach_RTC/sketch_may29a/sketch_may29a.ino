void setup()
{
  Serial.begin(9600);

}

void loop()
{
  while(Serial.available() > 0)
  {
    static char hoursInput[8];
    static char message[128];
    static unsigned int dem = 0;
    char inByte = Serial.read();

    if(inByte != '\n')
    {
      message[dem] = inByte;     
      hoursInput[dem] = inByte;
      dem++;
    }

    else
    {
      message[dem] = '\0';
      Serial.println(message);
      for(int i=0; i<2; i++){
        Serial.print(hoursInput[i]);
      }
      Serial.println();
      // Serial.println(hoursInput);
      // int number = atoi(message);
      // int val = number+10;
      // Serial.println(val);
      dem = 0;
    }
  }
}

// 12  25 24