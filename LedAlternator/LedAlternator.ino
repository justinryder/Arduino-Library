const int ledCount = 10;
int ledPins[ledCount] = { 1, 2, 3, 4, 5, 6, 9, 10, 11, 12 };
int mod = 3;
int offset = 0;
int delayMS = 200;

void setup()
{
  for (int i = 0; i < ledCount; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < ledCount; i++)
  {
    if ((i + offset) % mod == 0)
    {
      digitalWrite(ledPins[i], HIGH);
    }
    else
    {
      digitalWrite(ledPins[i], LOW);
    }
  }
  
  offset++;
  if (offset == mod)
  {
    offset = 0;
  }
  
  delay(delayMS);
}
