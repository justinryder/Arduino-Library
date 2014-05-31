
// These must be on digital PWM~ input pins
int ledR = 9;
int ledG = 10;
int ledB = 11;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

const int COLOR_MIN = 0;
const int COLOR_MAX = 255;

int red = 0;
int green = 127;
int blue = 255;

int speedR = 1;
int speedG = 2;
int speedB = 3;

void loop()
{
  red = calcColor(red, speedR);
  green = calcColor(green, speedG);
  blue = calcColor(blue, speedB);
  
  speedR = calcSpeed(speedR, red);
  speedG = calcSpeed(speedG, green);
  speedB = calcSpeed(speedB, blue);
  
  debugColor(red, green, blue);
  
  analogWrite(ledR, red);
  analogWrite(ledG, green);
  analogWrite(ledB, blue);
  delay(30);
}

int calcColor(int color, int delta)
{
  color += delta;
  if (color < COLOR_MIN)
  {
    color = COLOR_MIN;
  }
  if (color > COLOR_MAX)
  {
    color = COLOR_MAX;
  }
  return color;
}

int calcSpeed(int speed, int color)
{
  if (color + speed < COLOR_MIN || color + speed > COLOR_MAX)
  {
    return -speed;
  }
  return speed;
}

void debugColor(int red, int green, int blue)
{
  Serial.print("(");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(blue);
  Serial.print(", ");
  Serial.print(green);
  Serial.println(")");
}
