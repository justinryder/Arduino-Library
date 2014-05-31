#include <Bridge.h>
#include <Process.h>

const int buttonPin = 8;
const String sdPath = "/mnt/sda1/";
const String picturesPath = "/www/slideshow/pictures/";

int buttonState = 0;

Process process;

String filename;

void setup()
{
  Bridge.begin();
  
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH)
  {
    // Generate filename with timestamp
    filename = "";
    processShellCommand("date +%s");
    while (process.available() > 0)
    {
      char c = process.read();
      filename += c;
    }
    filename.trim();
    filename += ".png";
 
    // Take picture
    processShellCommand("fswebcam " + sdPath + filename + " -r 1280x720");
    
    // Copy picture to /www/pictures/
    processShellCommand("cp " + sdPath + filename + " " + picturesPath);
    
    // Upload to Dropbox
    //process.runShellCommand("python " + sdPath + "upload_process.py " + sdPath + filename);
    //while(process.running());
  }
}

void processShellCommand(String command)
{
  process.runShellCommand(command);
  while(process.running());
}
