#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// Connection to local WiFi network
const char* ssid = "WiFi_name"; // Name of the newtrok
const char* password = "WiFi_pass";  // Password
 
int ledPin = 2; // GPIO2 of ESP-01S (low -> ON, high -> OFF)

// Max size of serial data
const byte numChars = 32; 

// Loop counter
int counter = 0;

 
void setup()
{
  // Set serial
  Serial.begin(9600);

  // Set LED pin and turn it off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // Set WiFi data
  WiFi.begin(ssid, password);

  // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
    
}

void loop()
{
  // Every 10 loops (~ 1x per second)
  if(counter == 10)
  {
    // Check LED status on API
    updateLED();
    counter = 0;
  }

  // Get data from serial
  int data = recvIntWithStartEndMarkers();

  // If we have data call API
  if(data >= 0)
  {
      addMoistureValue(data);
  }
  
  counter++;
  
  delay(100);  // Delay for 0.1 sec
}

// Function that checks API and turns LED ON/OFF
void updateLED()
{
  HTTPClient http;

  // Link to API
  String link = "http://[server]/ArduinoGarden/api/Garden/GetValue";
  http.begin(link);

  // Basic authentication
  http.addHeader("Authorization", "Basic [token]");

  // Get data from API
  int httpCode = http.GET();
  String payload = http.getString();

  //If data == "0" turn LED off, else turn LED on
  if(payload == "\"0\"")
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  http.end();
}

// Function for sending moisture value to the server
void addMoistureValue(int value)
{
  HTTPClient http;
  
  // Link to API
  String link = "http://[server]/ArduinoGarden/api/Garden/AddMoistureValue/"+ String(value);
  http.begin(link);

  // Basic authentication
  http.addHeader("Authorization", "Basic [token]");
  
  //Call API
  int httpCode = http.GET();
  http.getString();
  http.end();
}


// Function for reciving serial data
int recvIntWithStartEndMarkers()
{
  //Default value (end of string)
  char receivedChars[numChars] = "\0";
  
  boolean newData = false;
  
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  // If we are reciving serial data
  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();
    
    if (recvInProgress == true)
    {
      if (rc != endMarker)
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars)
        {
          ndx = numChars - 1;
        }
      }
      else
      {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    
    else if (rc == startMarker)
    {
      recvInProgress = true;
    }
  }

  // If we didn't recive anything return -1. Else return recived integer
  if(receivedChars[0] == '\0')
  {
    return -1;  
  }
  else
  {
    return atoi(receivedChars);
  }
}
