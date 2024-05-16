
# Project Documentation
WebserverButtons.ino/button.h Documentation: Jack Stephens 5.15.24

UI Documentation: Cameron Warnick 5.15.24

Hardware: Steven Grubb 5.15.24

## WebserverButtons.ino
### Global Variables
- String button#State - Either "off" or "on", holds the current state of that button
- const int button# - constant that holds the pin number for the specified button
- unsigned long currentTime - holds the current time, updated using millis() function
- unsigned long previousTime - used as a temp holder for time, used in delta time calculations
- const long timeoutTime - constant holding the time (in ms) for user connection time out
- bool sequentialMode - tells whether the code is in sequentialMode, either true or false

### Features implemented
- Initialize Arduino pins
- Connect to WiFi
- Create local webserver
- Allow user connection
- Detects button presses on serial monitor
- Change switch button number via user web page interaction
- Only one state can be "on" at one time
- When the Switch is pressed, the chosen button is activated on the toy


## button.h
### Global Variables
- int setPin - The pin that will be activated, selected by the user on the webpage

- const int SwitLed - Constant storing the LED pin

- const int inputPin - the pin the switch is plugged into

- int buttonTimeoutTime - how long (in ms) the button will timeout after being pressed


### Switch Pin Function
switchPin(int pinNum)


Description-

    Switches the setPin variable to the number passed by pinNum


Parameters-

    pinNum - the pin you want to swap to


Returns-

    N/A


### Activate Pin Function
activatePin()


Description-

    Turns on the switch LED and the set pin and then prints serial confirmation


Parameters-
    
    N/A


Returns-
    
    N/A


### Deactivate Pin Function
deactivatePin()


Description-
    
    Turns off the switch LED and the set pin and then prints serial confirmation


Parameters-
    
    N/A


Returns-
    
    N/A


### Change Timeout Function
changeTimeout(int newTime)


Description-
    
    Changes the current buttonTimeoutTime to the new specified time


Parameters-
    
    newTime - The new time you want the timeout to be


Returns-
    
    N/A

# UI Documentation

## Design Screenshot
![Control interface](/design.png)

## Screen ID
Screen1

## Title
Sample Control Interface

## Description

The control interface allows users to select inputs which are propagated 
to all Linkimals toys within a valid radius.  For instance, a user can tap the "3" HTML button,
which is conveniently placed on top of the button on the image, to enable the switch to start the dance and song
associated with this number.  

## Design Principles

Given that we are running hardware that imposes tight limitations on memory and throughput,
the design for this page is purely functional. However, it maintains familiarity and cohesion with the official product
by displaying a sample Linkimals toy image and mapping the HTML button elements to their respective 
positions on the that image.  It also provides some temporary debugging information as a sanity check
for button state, which will be removed for the final product.  Our goal is to ensure that users enjoy a seamless
transition from the default toy to our modified hardware and engagement patterns, and we are actively working to 
further refine this process.


# Hardware Layout
![System Diagram](/PlayPalDiagram.png)


# Simulated Backend

The original project scope was to emulate the wireless communication of these toys with an NRF24l01 module to eliminate 
the need to modify toys to achieve this functionality, however, for this R1 an alternate route was taken of reusing the 
mainboard from a disassembled toy to achieve the wireless component between toys. There are some advantages to this aproach, 
ease of implementation, and the speaker in the button from the original toy. Further evaluation of wether moving to the nrf 
module will outweigh the benifits of using the FYK58 mainboard. 

