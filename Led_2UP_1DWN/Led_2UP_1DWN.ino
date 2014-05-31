const int delayMS = 1000;
const int arraySize = 4;

int leds[20] = {2, 4, 3, 5, 4, 6, 5, 7, 6, 8, 7, 9, 8, 10, 9, 11, 10, 12, 11, 13};
int count = 0;

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < arraySize; i++) 
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for(int i = 2; i <= 13; i++)
  {
    digitalWrite(i, LOW);
  }
  
  for(int i = 0; i < 20 / 4; i++)
  {
    digitalWrite(leds[count + ((20/4)* i)], HIGH);
  }
  
  if(count >= 4)
  {
    count = 0;
  }
  else
  {
    count++;  
  }
    
  delay(delayMS);
}

/*void displayOnOff()
{
  String s = "";
  for(int i = 0; i < arraySize; i++)
  {
    s = s + leds[1][i] + ", ";
  }
  
  Serial.println(s);
}*/
