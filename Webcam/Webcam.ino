#include <Bridge.h>
#include <Process.h>
#include <FileIO.h>

const int buttonPin = 8;
const String sdPath = "/mnt/sda1/pictures/";
const String picturesPath = "/www/slideshow/pictures/";
const String picturesListFile = "/www/slideshow/picturesList.txt";

int buttonState = 0;
Process process;
String filename;

void setup()
{
  Bridge.begin();
  FileSystem.begin();
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH)
  {
    generateTimestampFilename();
 
    // Take picture
    processShellCommand("fswebcam " + sdPath + filename + " -r 1280x720");
    
    // Copy picture to /www/pictures/
    processShellCommand("cp " + sdPath + filename + " " + picturesPath);
    
    appendToFile(filename, picturesListFile);
    
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

void appendToFile(String text, String filename)
{
  File file = FileSystem.open(filename.c_str(), FILE_APPEND);
  if (file)
  {
    file.println(text);
    file.close();
  }
}

void generateTimestampFilename()
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
}
