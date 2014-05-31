/*
Sets the brightness of an LED, based on the value of a potentiometer.
*/

// The LED's digital output pin number
int led = 9;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  // convert the input range (0-1023) to the output range (0-255)
  int brightness = sensorValue * (255.0 / 1023.0);
  analogWrite(led, brightness);
}
