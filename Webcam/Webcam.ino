#include <Bridge.h>
#include <Process.h>
#include <FileIO.h>

const String sdPath = "/mnt/sda1/pictures/";
const String picturesPath = "/www/slideshow/pictures/";
const String picturesListFile = "/www/slideshow/picturesList.txt";
const int potPin = 1;    // Analog ping for Potentiometer
const int sensor1Pin=0;  // Analog pin for sensor 1
int potValue = 0;  // variable to store the value coming from the potentiometer
const bool debugEnabled = false;  // enable debug logging
const String debugLogFile = "/www/slideshow/debuglog.txt";

Process process;
String filename;

void setup()
{
  Bridge.begin();
  FileSystem.begin();
  potValue = analogRead(potPin);
  
}

void loop() 
{
  potValue = analogRead(potPin);
  DebugLog("PotValue: " + String(potValue));
  int val= analogRead(sensor1Pin);
  DebugLog("SensorValue: " + String(val));
 
  if (val >= potValue)
  {
    DebugLog("Taking Picture");
    generateTimestampFilename();
 
    // Take picture
    processShellCommand("fswebcam " + sdPath + filename + " -r 1280x720");
    
    // Copy picture to /www/pictures/
    processShellCommand("cp " + sdPath + filename + " " + picturesPath);
    
    appendToFile(filename, picturesListFile);
    
    // Upload to Dropbox
    //process.runShellCommand("python " + sdPath + "upload_process.py " + sdPath + filename);
    //while(process.running());
    val = 0;
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

void DebugLog(String debugtext)
{
  if(debugEnabled) {
    File Debugfile = FileSystem.open(debugLogFile.c_str(), FILE_APPEND);
    if(Debugfile)
    {
      Debugfile.println(debugtext);
      Debugfile.close();
    }
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
