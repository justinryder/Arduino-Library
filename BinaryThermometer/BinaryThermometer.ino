
int leds[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

int temperature = 0;

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 8; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(leds[i], getBit(temperature, i));
  }
  
  debugBinary(temperature);
  Serial.println("");
}

int getBit(int number, int bitIndex)
{
  return number >> bitIndex & 1;
}

void debugBinary(int value)
{
  Serial.print(value);
  Serial.print(" = ");
  for (int i = 7; i >= 0; i--)
  {
    Serial.print(getBit(value, i));
  }
}
