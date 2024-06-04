/*********

  Modified by Steven Grubb 5.7.24, added a 3rd button and changed pin numbers, for use with Arduino Nano ESP32
  Modified by Cameron Warnick 5.10.24, styling/state change (web server HTML), made styling better 
  (removed extraneous comments, improved comment clarity, layout)

*********/
#include <Arduino.h>
#include <iostream>
#include <SPIFFS.h>
#include <WiFi.h>
#include "button.h"
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <stdio.h>
//#include <AsyncJson.h>
//#include <ArduinoJson.h>

// Replace with your network credentials
 //const char* ssid = "TestNet_24";
 //const char* password = "Redacted__Redacted";

//credentials used for demo network
const char* ssid = "Linkimals_Net";
const char* password = "uh887jw3t0";

AsyncWebServer server(80);

//store HTTP request
String header;
String buttonState[] = {"-1", "off", "off", "off", "off", "off", "off", "off", "off"};

//Array holding button to pin mapping, [0] is -1 to match index with button ID, [6] skips 7 as that is the switch pin
int button[] = {-1,2,3,4,5,6,8,9,10};

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;
// Set switch GPIO
const int Switch[] = {7,11};


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// Boolean variables for modes, default: off
bool sequentialMode = false;
bool timeout = false;
unsigned long buttonTimeoutTime = 150;

//method declarations
bool updatePins(int, String);
  // Replaces placeholder with Pin state value

const char* PARAM_MESSAGE = "buttonID";



void setup() 
{
  delay(1000); //reconnect delay, remove for prod
  //init port, set data rate (baud rate -- bits/second)
  Serial.begin(115200);

  // Initialize the output variables as pin outputs
  pinMode(button[1], OUTPUT); // GPIO1, button 1
  pinMode(button[2], OUTPUT); // GPIO2, button 2
  pinMode(button[3], OUTPUT); // GPIO3, button 3
  pinMode(button[4], OUTPUT); // GPIO4, button 4
  pinMode(button[5], OUTPUT); // GPIO5, button 5
  pinMode(button[6], OUTPUT); // SP1, move
  pinMode(button[7], OUTPUT); // SP2, dance
  pinMode(button[8], OUTPUT); // SP3
  pinMode(Switch[0], INPUT_PULLUP); // Main PlayPal button
  pinMode(Switch[1], INPUT_PULLUP); // External switch input
  pinMode(SwitLed, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);


  // turn off pins asssociated with output[2..4]
  // outputs are active low
  digitalWrite(button[1], HIGH); // GPIO1, button 1
  digitalWrite(button[2], HIGH); // GPIO2, button 2
  digitalWrite(button[3], HIGH); // GPIO3, button 3
  digitalWrite(button[4], HIGH); // GPIO4, button 4
  digitalWrite(button[5], HIGH); // GPIO5, button 5
  digitalWrite(button[6], HIGH); // SP1, move
  digitalWrite(button[7], HIGH); // SP2, dance
  digitalWrite(button[8], HIGH); // SP3
  // init switch light to off, it is connected to comm on the other side
  digitalWrite(SwitLed, LOW);

  digitalWrite(LED_RED, LOW);
  

  //Init button 1 to on, and pin 2 (b1) to enabled
  buttonState[1] = "on";
  switchPin(0, 2);
  //Set Status LED to Red


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }


  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Set Status LED to dim green

  analogWrite(LED_RED, 255);

  
  //Server setup

  //Init Spiffs
    if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS mounting error");
    return;
  }
  else{
    Serial.println("SPIFFS mounted");
  }

  
    // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });

// Images

    //hedgehog
  server.on("/images/hedgehog.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/hedgehog.png", String(), false);
  });
  
    //button1
  server.on("/images/1.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/1.png", String(), false);
  });

      //button 2
  server.on("/images/2.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/2.png", String(), false);
  });

      //button 3
  server.on("/images/3.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/3.png", String(), false);
  });

      //button 4
  server.on("/images/4.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/4.png", String(), false);
  });

      //button 5
  server.on("/images/5.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/images/5.png", String(), false);
  });
  
//css stylesheets

      //buttonStyles
  server.on("/css/buttonStyles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/buttonStyles.css", String(), false);
  });

    //containerStyles
  server.on("/css/containerStyles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/containerStyles.css", String(), false);
  });

    //glowButton
  server.on("/css/glowButton.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/glowButton.css", String(), false);
  });
    
    //pageStyles
  server.on("/css/pageStyles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/pageStyles.css", String(), false);
  });

    //styles
  server.on("/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/styles.css", String(), false);
  });

    //stylesBackup
  server.on("/css/stylesBackup.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/stylesBackup.css", String(), false);
  });


      // button1 pressed
  server.on("/update1", HTTP_GET, [](AsyncWebServerRequest *request){
    //request->send(SPIFFS, "/index.html", String(), false);
    Serial.println("button1 pressed");
    request->send(200, "text/plain", "OK");
  });

  //TODO: change 'SERVER_ADDRESS' to something more meaningfull
  server.on("/SERVER_ADDRESS", HTTP_POST, [](AsyncWebServerRequest *request){
      String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
            updatePins(0, message);
        } else {
            message = "No message sent";
        }

        request->send(200, "JSON", "{\"ButtonRecv\":\"" + message+ "\"}");
    });
  
    server.on("/ButtonPinStatus", HTTP_POST, [](AsyncWebServerRequest *request){
      String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            Serial.println("Got pin status request");
            message = request->getParam(PARAM_MESSAGE, true)->value();
            Serial.println("message Recv: " + message);
        } else {
            message = "No message sent";
        }
        //get pin state and return it
        String response;

        response = buttonState[message.toInt()];
        Serial.println("button state: " + response);

        request->send(200, "JSON", "{\"buttonState\":\"" + response + "\"}");
    });
  
  server.begin();

}


void loop()
{
  // Listen for incoming clients
  //WiFiClient client = server.available();   
    /*
      * Button Logic
    */
    // button is pressed (pin 7 = input pin)
    currentTime = millis();

    if(timeout && currentTime - previousTime > buttonTimeoutTime){
        timeout = false;
    }

    if(digitalRead(Switch[0]) == LOW)
    {
      Serial.print("press on switch0 detected: ");
      if(!timeout){
        if(sequentialMode == true){
            previousTime = currentTime;
            Serial.println("Sequential mode");
            buttonPressedSequential(currentTime, previousTime, 0);
        }
        else{
            previousTime = currentTime;
            Serial.println("Standard mode");
            buttonPressedStandard(currentTime, previousTime, 0);
            timeout = true;
        }
      }
      else{
        Serial.println("button in timeout, ignoring press");
      }
    if(digitalRead(Switch[1]) == LOW)
    {
      Serial.print("press on switch1 detected: ");
      if(!timeout){
        if(sequentialMode == true){
            previousTime = currentTime;
            Serial.println("Sequential mode");
            buttonPressedSequential(currentTime, previousTime, 1);
        }
        else{
            previousTime = currentTime;
            Serial.println("Standard mode");
            buttonPressedStandard(currentTime, previousTime, 1);
            timeout = true;
        }
      }
      else{
        Serial.println("button in timeout, ignoring press");
      }
    }
  }
}

bool updatePins(int inputIndex, String buttonID){
  Serial.println("updating state of button: " + buttonID);


  int pinID = button[buttonID.toInt()];

  switchPin(inputIndex, pinID);
  Serial.println("loop?");
  for (int i = 0; i < 9; i++){
    Serial.print(i);
    buttonState[i] = "off";
  }
    
  Serial.println("Turning all states off");

  buttonState[buttonID.toInt()] = "on";
  Serial.println("successfully updated state of button: " + buttonID);
  return true;
}