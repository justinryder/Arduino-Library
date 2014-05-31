

const int button = 2;
const int dial = A0;

// These must be on digital PWN~ pins
const int ledRed = 9;
const int ledGreen = 10;
const int ledBlue = 11;

const int ledRedIndicator = 6;
const int ledGreenIndicator = 7;
const int ledBlueIndicator = 8;

int red = 0;
int green = 0;
int blue = 0;

int selectedColor = 0;

int buttonLast = 0;
int buttonCurrent = 0;

void setup()
{
  pinMode(button, INPUT);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  pinMode(ledRedIndicator, OUTPUT);
  pinMode(ledGreenIndicator, OUTPUT);
  pinMode(ledBlueIndicator, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  button1Last = buttonCurrent;
  
  int dialValue = analogRead(dial) * (255.0 / 1023.0);// convert from (0-1023) to (0-255)
  buttonCurrent = digitalRead(button);
  
  if (buttonCurrent && !buttonLast)
  {
    selectedColor++;
    if (selectedColor > 2)
    {
      selectedColor = 0;
    }
    debugSelectedColor();
  }
  
  digitalWrite(ledRedIndicator, LOW);  
  digitalWrite(ledGreenIndicator, LOW);  
  digitalWrite(ledBlueIndicator, LOW);
  
  switch(selectedColor)
  {
    case 0:
      //debugIfNotEqual(red, dialValue);
      red = dialValue;
      digitalWrite(ledRedIndicator, HIGH);
      break;
    case 1:
      //debugIfNotEqual(green, dialValue);
      green = dialValue;
      digitalWrite(ledGreenIndicator, HIGH);
      break;
    case 2:
      //debugIfNotEqual(blue, dialValue);
      blue = dialValue;
      digitalWrite(ledBlueIndicator, HIGH);
      break;
  };
  
  setLedColor(red, green, blue);
}

void debugSelectedColor()
{
  Serial.print(selectedColor);
  Serial.print(" (");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(blue);
  Serial.print(", ");
  Serial.print(green);
  Serial.println(")");
}

void debugIfNotEqual(int a, int b)
{
  if (a != b)
  {
    Serial.print(a);
    Serial.print("=>");
    Serial.println(b);
  }
}

bool isPressed(int buttonState)
{
  return buttonState == LOW;
}

void setLedColor(int red, int green, int blue)
{
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}
