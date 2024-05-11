/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  

  Modified by Steven Grubb 5.7.24, added a 3rd button and changed pin numbers, for use with Arduino Nano ESP32
  Modified by Cameron Warnick 5.10.24, styling/state change (web server HTML), made styling better 
  (removed extraneous comments, improved comment clarity, layout)

*********/

#include <WiFi.h>

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

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() 
{
  //init port, set data rate (baud rate -- bits/second)
  Serial.begin(115200);

  // Initialize the output variables as pin outputs
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);

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
            
            // turns the GPIOs on and off based on the request
            if (header.indexOf("GET /2/on") >= 0) 
            {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, LOW);
            } 
            else if (header.indexOf("GET /2/off") >= 0) 
            {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, HIGH);
            } 
            else if (header.indexOf("GET /3/on") >= 0) 
            {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, LOW);
            } 
            else if (header.indexOf("GET /3/off") >= 0) 
            {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, HIGH);
            } 
            else if (header.indexOf("GET /4/on") >= 0) 
            {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, LOW);
            } 
            else if (header.indexOf("GET /4/off") >= 0) 
            {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, HIGH);
            }

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
            client.println("<h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
    
            if (output2State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/2/on\">");
              client.println("<button class=\"button\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/2/off\">");
              client.println("<button class=\"button button2\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 3 - State " + output3State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output3State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/3/on\">");
              client.println("<button class=\"button\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/3/off\">");
              client.println("<button class=\"button button2\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
    
            if (output4State=="off") 
            {
              client.println("<p>");
              client.println("<a href=\"/4/on\">");
              client.println("<button class=\"button\">");
              client.println("ON");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            } 
            else 
            {
              client.println("<p>");
              client.println("<a href=\"/4/off\">");
              client.println("<button class=\"button button2\">");
              client.println("OFF");
              client.println("</button>");
              client.println("</a>");
              client.println("</p>");
            }

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
                    "html"
                    "{"
                      "font-family: Helvetica;"
                      "display: inline-block;"
                      "margin: 0px auto;"
                      "text-align: center;"
                    "}"

                    ".button"
                    "{"
                      "background-color: #4CAF50;"
                      "border: none;"
                      "color: white;"
                      "padding: 16px 40px;"
                      "text-decoration: none;"
                      "font-size: 30px;"
                      "margin: 2px;"
                      "cursor: pointer;"
                    "}"

                  ".button2"
                  "{"
                    "background-color: #555555;"
                  "}"
                "</style>";

  return styles;
            
}