/*********

  Modified by Steven Grubb 5.7.24, added a 3rd button and changed pin numbers, for use with Arduino Nano ESP32
  Modified by Cameron Warnick 5.10.24, styling/state change (web server HTML), made styling better 
  (removed extraneous comments, improved comment clarity, layout)

*********/
#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "button.h"
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"


// Replace with your network credentials
const char* ssid = "TestNet_24";
const char* password = "Redacted__Redacted";

AsyncWebServer server(80);

//store HTTP request
String header;

String button1State = "off";
String button2State = "off";
String button3State = "off";
String button4State = "off";
String button5State = "off";

// Assign output variables to GPIO pins
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
const int button5 = 6;
const int Switch1 = 7;
//const int SwitLed = 8;

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// Boolean variables for modes, default: off
bool sequentialMode = false;

//method declarations
String GetStyles();
String processor();
  // Replaces placeholder with Pin state value




void setup() 
{
  delay(1000); //reconnect delay, remove for prod
  //init port, set data rate (baud rate -- bits/second)
  Serial.begin(115200);

  // Initialize the output variables as pin outputs
  pinMode(button1, OUTPUT);
  pinMode(button2, OUTPUT);
  pinMode(button3, OUTPUT);
  pinMode(button4, OUTPUT);
  pinMode(button5, OUTPUT);
  pinMode(Switch1, INPUT_PULLUP);
  pinMode(SwitLed, OUTPUT);

  // turn off pins asssociated with output[2..4]
  // outputs are active low
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
  digitalWrite(button4, HIGH);
  digitalWrite(button5, HIGH);
  // init switch light to off, it is connected to comm on the other side
  digitalWrite(SwitLed, LOW);

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
    if(digitalRead(Switch1) == LOW)
    {
      Serial.print("press detected: ");
      if(sequentialMode == true){
        Serial.println("Sequential mode");
        buttonPressedSequential();
      }
      else{
        Serial.println("Standard mode");
        buttonPressedStandard();
      }
    }



}

String GetStyles() {
  String styles = "<style>"
                    ".Container {"
                        "display: flex;"
                        "flex-direction: column;"
                        "align-items: center;"
                        "width: 100vw;"
                        "height: 100vh;"
                        "position: absolute;"
                    "}"
                    ".TopContainer {"
                        "background-color: black;"
                        "width: 100%;"
                        "height: 20vh;"
                        "margin-left: -1vw;"
                        "margin-top: -1.5vh;"
                        "display: flex;"
                        "flex-direction: column;"
                        "justify-content: center;"
                    "}"
                    ".TopText {"
                        "color: white;"
                        "font-size: 4vmax;"
                    "}"
                    ".ContentContainer {"
                        "width: 100vw;"
                        "margin-top: 5vh;"
                        "display: flex;"
                        "flex-direction: column;"
                        "gap: 1vmax;"
                        "justify-content: center;"
                        "align-items: center;"
                    "}"
                    ".ControlContainer {"
                        "display: flex;"
                        "flex-direction: row;"
                        "justify-content: center;"
                        "background-color: #303030;"
                        "color: white;"
                        "border-radius: 20px;"
                        "padding: 1vmax;"
                    "}"
                    ".InnerContainer {"
                        "display: flex;"
                        "flex-direction: column;"
                        "position: absolute;"
                    "}"
                    "html {"
                        "background-color: #ffffff;"
                        "font-family: sans-serif;"
                        "display: block;"
                        "text-align: center;"
                        "overflow-y: hidden;"
                        "overflow-x: hidden;"
                    "}"
                    ".InnerText {"
                        "color: #d0d0d0;"
                        "font-size: 2vmax;"
                    "}"
                    ".ButtonGroupOrigin {"
                        "margin-top: 13vh;"
                        "position: absolute;"
                    "}"
                    ".StateContainer {"
                        "display: flex;"
                        "flex-direction: row;"
                        "background-color: #303030;"
                        "gap: 2vmax;"
                        "padding: 1vmax;"
                        "border-radius: 20px;"
                        "justify-content: center;"
                        "align-items: center;"
                    "}"
                    ".ImageStyle {"
                        "width: 25vmax;"
                        "height: 25vmax;"
                    "}"
                    ".ButtonStyle {"
                        "position: absolute;"
                        "width: 3vmax;"
                        "height: 3vmax;"
                        "background: none;"
                        "border: 1px solid white;"
                        "cursor: pointer;"
                    "}"
                    ".Button1 {"
                        "margin-left: -5vw;" 
                        "margin-top: 5.5vh;"
                    "}"
                    ".Button2 {"
                        "margin-left: -2vw;" 
                        "margin-top: 1.25vh;"
                    "}"
                    ".Button3 {"
                        "margin-left: 1.5vw;"  
                        "margin-top: 1.75vh;"
                    "}"
                    ".Button4 {"
                        "margin-left: 5vw;" 
                        "margin-top: 7vh;"
                    "}"
                    ".Button5 {"
                        "margin-left: 5vw;" 
                        "margin-top: 15vh;"
                    "}"
                    "@media(orientation: landscape) {"
                        "@media(max-aspect-ratio: 20/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 11vh;"
                                "position: absolute;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 18/10) and (min-aspect-ratio: 16/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 10.5vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 5vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 12vh;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 16/10) and (min-aspect-ratio: 15/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 9vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 5vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 12vh;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 14/10) and (min-aspect-ratio: 12/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 8vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 5vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 11vh;"
                            "}"
                            ".Button1 {"
                                "margin-top: 4vh;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 12/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 6vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 5vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 11vh;"
                            "}"
                            ".Button1 {"
                                "margin-top: 4vh;"
                            "}"
                        "}"
                    "}"
                    "@media(orientation: portrait) {"
                        "@media(min-aspect-ratio: 9/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 5vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 4vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 8vh;"
                            "}"
                            ".Button1 {"
                                "margin-top: 4vh;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 9/10) and (min-aspect-ratio: 7/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 5vh;"
                                "position: absolute;"
                            "}"
                            ".Button4 {"
                                "margin-left: 5vw;" 
                                "margin-top: 4vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 8vh;"
                            "}"
                            ".Button1 {"
                                "margin-top: 4vh;"
                            "}"
                            ".StateContainer {"
                                "scale: .7;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 7/10) and (min-aspect-ratio: 5/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 5vh;"
                                "position: absolute;"
                            "}"
                            ".Button1 {"
                                "margin-left: -9vw;"
                                "margin-top: 3.5vh;"
                            "}"
                            ".Button2 {"
                                "margin-left: -3vw;" 
                                "margin-top: 1.75vh;"
                            "}"
                            ".Button3 {"
                                "margin-left: 3vw;"  
                                "margin-top: 1.75vh;"
                            "}"
                            ".Button4 {"
                                "margin-left: 10.5vw;" 
                                "margin-top: 4vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 8vh;"
                                "margin-left: 9vw;" 
                            "}"
                            ".StateContainer {"
                                "scale: .7;"
                            "}"
                        "}"
                        "@media(max-aspect-ratio: 5/10) and (min-aspect-ratio: 3/10) {"
                            ".ButtonGroupOrigin {"
                                "margin-top: 5vh;"
                                "position: absolute;"
                            "}"
                            ".Button1 {"
                                "margin-left: -15vw;"
                                "margin-top: 3.5vh;"
                            "}"
                            ".Button2 {"
                                "margin-left: -6vw;" 
                                "margin-top: 1.75vh;"
                            "}"
                            ".Button3 {"
                                "margin-left: 4vw;"  
                                "margin-top: 1.75vh;"
                            "}"
                            ".Button4 {"
                                "margin-left: 14.5vw;" 
                                "margin-top: 4vh;"
                            "}"
                            ".Button5 {"
                                "margin-top: 8vh;"
                                "margin-left: 16vw;" 
                            "}"
                            ".StateContainer {"
                                "scale: .7;"
                            "}"
                        "}"
                    "}"
                "</style>";
  return styles;
}


String processor(const String& var)
  {
    Serial.println(var);
    if(var == "STATE"){
      if(digitalRead(ledPin)){
        ledState = "ON";
      }
      else{
        ledState = "OFF";
      }
      Serial.print(ledState);
      return ledState;
    }
    return String();
  }
