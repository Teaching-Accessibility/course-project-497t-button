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
// const char* ssid = "TestNet_24";
// const char* password = "Redacted__Redacted";
const char* ssid = "Linkimals_Net";
const char* password = "uh887jw3t0";

AsyncWebServer server(80);

//store HTTP request
String header;
String buttonState[] = {"-1", "off", "off", "off", "off", "off"};
// String button1State = "off";
// String button2State = "off";
// String button3State = "off";
// String button4State = "off";
// String button5State = "off";



//Array holding button to pin mapping, [0] is -1 to match index with button ID
int button[] = {-1,2,3,4,5,6};

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;
// Set switch GPIO
const int Switch1 = 7;


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// Boolean variables for modes, default: off
bool sequentialMode = false;
bool timeout = false;
unsigned long buttonTimeoutTime = 150;

//method declarations
bool updatePins(String);
  // Replaces placeholder with Pin state value

const char* PARAM_MESSAGE = "buttonID";



void setup() 
{
  delay(1000); //reconnect delay, remove for prod
  //init port, set data rate (baud rate -- bits/second)
  Serial.begin(115200);

  // Initialize the output variables as pin outputs
  pinMode(button[1], OUTPUT);
  pinMode(button[2], OUTPUT);
  pinMode(button[3], OUTPUT);
  pinMode(button[4], OUTPUT);
  pinMode(button[5], OUTPUT);
  pinMode(Switch1, INPUT_PULLUP);
  pinMode(SwitLed, OUTPUT);

  // turn off pins asssociated with output[2..4]
  // outputs are active low
  digitalWrite(button[1], HIGH);
  digitalWrite(button[2], HIGH);
  digitalWrite(button[3], HIGH);
  digitalWrite(button[4], HIGH);
  digitalWrite(button[5], HIGH);
  // init switch light to off, it is connected to comm on the other side
  digitalWrite(SwitLed, LOW);

  //Init button 1 to on, and pin 2 (b1) to enabled
  buttonState[1] = "on";
  switchPin(2);


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
  








  
  //Server setup

  //Init Spiffs
    if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS mounting error");
    return;
  }
  else{
    Serial.println("SPIFFS mounted");
  }


  
  //image setup
  server.on("/hedgehog.png", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/hedgehog.png", "image/png");
  });
  
    // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
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
            updatePins(message);
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

    if(digitalRead(Switch1) == LOW)
    {
      Serial.print("press detected: ");
      if(!timeout){
        if(sequentialMode == true){
            previousTime = currentTime;
            Serial.println("Sequential mode");
            buttonPressedSequential(currentTime, previousTime);
        }
        else{
            previousTime = currentTime;
            Serial.println("Standard mode");
            buttonPressedStandard(currentTime, previousTime);
            timeout = true;
        }
      }
      else{
        Serial.println("button in timeout, ignoring press");
      }
    }

}

bool updatePins(String buttonID){
  Serial.println("updating state of button: " + buttonID);


  int pinID = button[buttonID.toInt()];

  switchPin(pinID);
  Serial.println("loop?");
  for (int i = 0; i < 6; i++){
    Serial.print(i);
    buttonState[i] = "off";
  }
    
  Serial.println("Turning all states off");

  buttonState[buttonID.toInt()] = "on";
  Serial.println("successfully updated state of button: " + buttonID);
  return true;
}

