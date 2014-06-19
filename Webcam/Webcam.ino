#include <Bridge.h>
#include <Process.h>
#include <FileIO.h>

const String sdPath = "/mnt/sda1/pictures/";
const String picturesPath = "/www/slideshow/pictures/";
const String picturesListFile = "/www/slideshow/picturesList.txt";
const String debugLogFile = "/www/slideshow/debuglog.txt";
const int potPin = 1;    // select the input pin for the potentiometer
const int sensor1Pin=0;  // Analog pin for sensor 1
int sensorValue = 0;  // variable to store the value coming from the potentiometer

Process process;
String filename;

void setup()
{
  Bridge.begin();
  FileSystem.begin();
  sensorValue = analogRead(potPin);
  
}

void loop() 
{
  sensorValue = analogRead(potPin);
  DebugLog("PotValue: " + String(sensorValue));
  int val= analogRead(sensor1Pin);
  DebugLog("SensorValue: " + String(val));
 
  if (val >= sensorValue)
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
  if (file && text.length()>1)
  {
    file.println(text);
    file.close();
  }
}

void DebugLog(String debugtext)
{
  File Debugfile = FileSystem.open(debugLogFile.c_str(), FILE_APPEND);
  if(Debugfile)
  {
    Debugfile.println(debugtext);
    Debugfile.close();
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
