/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  

  Modified by Steven Grubb 5.7.24, added a 3rd button and changed pin numbers, for use with Arduino Nano ESP32
  Modified by Cameron Warnick 5.10.24, styling/state change (web server HTML), made styling better 
  (removed extraneous comments, improved comment clarity, layout)

*********/

#include <WiFi.h>
#include "button.h"

// Replace with your network credentials
const char* ssid = "TestNet_24";
const char* password = "Redacted__Redacted";

WiFiServer server(80);

//store HTTP request
String header;

String output2State = "off";
String output3State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output2 = 2;
const int output3 = 3;
const int output4 = 4;
const int ButtonSwitchPin = 7;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// Boolean variables for modes, default: off
bool sequentialMode = false;

void setup() 
{
  //init port, set data rate (baud rate -- bits/second)
  Serial.begin(115200);

  // Initialize the output variables as pin outputs
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(ButtonSwitchPin, INPUT);

  // turn off pins asssociated with output[2..4]
  // outputs are active low
  digitalWrite(output2, HIGH);
  digitalWrite(output3, HIGH);
  digitalWrite(output4, HIGH);

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
  server.begin();
}

void loop()
{
  // Listen for incoming clients
  WiFiClient client = server.available();   
    /*
      * Button Logic
    */
    // button is pressed (pin 7 = input pin)
    if(digitalRead(ButtonSwitchPin) == LOW)
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
  //handle client connection (invoked on connect)
  if (client) 
  {           



    //currentLine holds incoming client data
    currentTime = millis();
    previousTime = currentTime;
    String currentLine = "";        

    Serial.println("New Client.");

    while (client.connected() && currentTime - previousTime <= timeoutTime) 
    {  
      currentTime = millis();

      //check for bytes to receive from client
      if (client.available()) 
      {             
        //read 1 byte
        char c = client.read();             

        // print the byte out the serial monitor
        Serial.write(c);                    
        header += c;

        //handle end of line in HTTP request
        if (c == '\n') 
        {
          //check for blank line indicating end of HTTP request
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            /*
             * Pin switching and state swapping logic
            */
            if (header.indexOf("GET /2/on") >= 0) 
            {
              Serial.println("GPIO 2 on");
              switchPin(output2);

              if(output3State == "on" || output4State == "on"){ // turn others off, only one at a time
                Serial.println("turning off 3 or 4");
                output3State = "off";
                output4State = "off";
              }

              output2State = "on";
            } 
            //else if (header.indexOf("GET /2/off") >= 0) output2State = "off";
            else if (header.indexOf("GET /3/on") >= 0) 
            {
              Serial.println("GPIO 3 On");
              switchPin(output3);

              if(output2State == "on" || output4State == "on"){ // turn others off, only one at a time
                Serial.println("turning off 2 or 4");
                output2State = "off";
                output4State = "off";
              }

              output3State = "on";
            } 
            //else if (header.indexOf("GET /3/off") >= 0) output3State = "off";
            else if (header.indexOf("GET /4/on") >= 0) 
            {
              Serial.println("GPIO 4 on");
              switchPin(output4);

              if(output2State == "on" || output3State == "on"){ // turn others off, only one at a time
                Serial.println("turning off 2 or 3");
                output2State = "off";
                output3State = "off";
              }

              output4State = "on";
            } 
            //else if (header.indexOf("GET /4/off") >= 0) output4State = "off";


            
            /*
             * Webpage HTML Code
            */
            // Display the HTML web page
            client.println("<!DOCTYPE html>");

            client.println("<html>");
            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println(GetStyles());
            client.println("</head>");
            
            // Web Page Heading
            client.println("<body>");

            client.println("<div class = \"Container\">");

            client.println("<div class = \"TopContainer\">");
            client.println("<h1 class = \"TopText\">ESP32 Web Server");
            client.println("<a class = \"InnerText\"><br/>Linkamals Button Project</a></h1>");
            client.println("</div>");
            
            client.println("<div class = \"ControlContainer\">");

            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<div class = \"InnerContainer\">");
            client.println("<p class = \"OnOff\">GPIO 2 - State " + output2State + "</p>");
    
            if (output2State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/2/on\">");
              client.println("<button class=\"glowingButton\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/2/off\">");
              client.println("<button class=\"glowingButton\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            client.println("</div>");

            // Display current state, and ON/OFF buttons for GPIO 27 
            client.println("<div class = \"InnerContainer\">"); 
            client.println("<p class = \"OnOff\">GPIO 3 - State " + output3State + "</p>");      
            if (output3State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/3/on\">");
              client.println("<button class=\"glowingButton\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/3/off\">");
              client.println("<button class=\"glowingButton\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            }
            client.println("</div>");
            
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<div class = \"InnerContainer\">");
            client.println("<p class = \"OnOff\">GPIO 4 - State " + output4State + "</p>");
    
            if (output4State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/4/on\">");
              client.println("<button class=\"glowingButton\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/4/off\">");
              client.println("<button class=\"glowingButton\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            }
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");

            client.println("</body>");
            client.println("</html>");
            
            // The HTTP response ends with another blank line
            client.println();

            // Break out of the while loop
            break;
          } 
          // if you got a newline, then clear currentLine
          else 
          { 
            currentLine = "";
          }
        } 
        // if you got anything else but a carriage return character,
        else if (c != '\r') 
        {  
          // add it to the end of the currentLine
          currentLine += c;      
        }
      }
    }
  
  // Clear the header variable
  header = "";
  // Close the connection
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
  }
}

String GetStyles()
{
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
                    ".ControlContainer {"
                        "display: flex;"
                        "flex-direction: row;"
                        "justify-content: center;"
                        "gap: 3vw;"
                        "padding: 2vw;"
                        "background-color: #303030;"
                        "color: white;"
                        "margin-top: 25vh;"
                        "border-radius: 20px;"
                    "}"
                    ".InnerContainer {"
                        "display: flex;"
                        "flex-direction: column;"
                    "}"
                    ".OnOff {"
                        "font-weight: bolder;"
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
                    ".glowingButton {"
                        "transform: translate(-0%, 0%);"
                        "text-align: center;"
                        "padding: 0px;"
                        "padding-left: 2vw;"
                        "padding-right: 2vw;"
                        "line-height:  6vh;"
                        "color: #d0d0d0;"
                        "background: none;"
                        "font-size: 1.5vh;"
                        "text-transform: uppercase;"
                        "text-decoration: none;"
                        "box-sizing: border-box;"
                        "background-size: 0%;"
                        "background-size: 400%;"
                        "backdrop-filter: blur(30px);"
                        "border-radius: 5vw;"
                        "border: 0.1vh solid #8a8a8a;"
                    "}"
                    ".glowingButton:hover {"
                        "animation: animate 8s linear infinite;"
                        "cursor: pointer;"
                        "color: transparent;"
                    "}"
                    "@keyframes animate {"
                        "0% {"
                            "background-position: 0%;"
                        "}"
                        "100% {"
                            "background-position: 400%;"
                        "}"
                    "}"
                    ".glowingButton::before {"
                        "content: '';"
                        "text-align: center;"
                        "position: absolute;"
                        "top: -5px;"
                        "left: -5px;"
                        "right: -5px;"
                        "bottom: -5px;"
                        "z-index: -1;"
                        "background: linear-gradient(90deg, #03a9f4, #03a9f4, #f441a5, #ffeb3b, #03a9f4);"
                        "background-size: 400%;"
                        "border-radius: 30px;"
                        "opacity: 0;"
                        "transition: 0.5s;"
                    "}"
                    ".glowingButton:hover:before {"
                        "filter: blur(20px);"
                        "opacity: 1;"
                        "animation: animate 8s linear infinite;"
                    "}"
                "</style>";

  return styles;
            
}