
# Project Documentation
WebserverButtons.ino/button.h Documentation: Jack Stephens 5.15.24

UI Documentation: Cameron Warnick 5.15.24

Hardware: Steven Grubb 5.15.24


## WebserverButtons.ino
### Global Variables
- String buttonState[] - Either "off" or "on", array that holds the current state of that button, size = number of buttons
- int button[] - array that holds the pin number for the specified button
- const int ledPin - contains pin number of led
- String ledState - hold state of led, either "off" or "on"
- const int Switch1 - holds the value of the pin the switch is plugged into
- unsigned long currentTime - holds the current time, updated using millis() function
- unsigned long previousTime - used as a temp holder for time, used in delta time calculations
- bool timeout - tells whether or not button is currently in timeout
- bool sequentialMode - tells whether the code is in sequentialMode, either true or false
- unsigned long buttonTimeoutTime - timeout time for button, in ms, increase for larger timeout

### Features implemented
- Initialize Arduino pins
- Connect to WiFi
- Create local async webserver
- Allow user connection
- Detects button presses on serial monitor
- Change switch button number via user web page interaction
- Only one state can be "on" at one time
- When the Switch is pressed, the chosen button is activated on the toy

### Update Pins Function
updatePins(String buttonID)


Description-
    
    Updates the active set pin to the pin selected by the user on the webpage

Parameters-

    buttonID - the pin to swap to

Returns-

    true if successful
    false if unsuccessful
    

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


### Button Pressed Function (Standard)
buttonPressedStandard(unsigned long currentTime, unsigned long previousTime)


Description-

    Activates the pin, waits 150ms, then deactivates it and sets the button to timeout

Parameters-

    currentTime - Holds the current time the program has been running
    previousTime - Used to hold temp time values to measure change in time

Returns-

    N/A


### Button Pressed Function (Sequential Mode)
buttonPressedSequential(unsigned long currentTime, unsigned long previousTime)


Description-

    Counts button presses from user (500ms window) and then activates that pin

Parameters-

    currentTime - Holds the current time the program has been running
    previousTime - Used to hold temp time values to measure change in time

Returns-

    N/A


# UI Documentation

## Design Screenshot
![Control interface](/fegif.gif)

## Screen ID
Screen1

## Title
Control Interface

## Description

The control interface allows users to select inputs which are propagated 
to all Linkimals toys within a valid radius.  For instance, a user can tap the "3" HTML button,
which is conveniently placed on top of the button on the image, to enable the switch to start the dance and song
associated with this number.  Additionally, users have a clear view of the button state, and are able to 
utilize special accessibilty features from the bottom menu.  These features are: button-highlight mode, which 
creates a thick, bright-red border around each button for clarity, and expanded mode, which increases the image
and button scales by 25%, making them even easier to see.  Additionally, buttons expand on hover, allowing 
users to easily avoid incorrect input.

## Design Principles

We are working with tight hardware constraints -- for instance, the previous version was too slow purely because of the 
inefficient button-placement styling, despite its lower visual quality.  The updated design strikes a balance between 
simplicity and fun, creating an engaging visual environment supported by bright animated colors designed to appeal 
to a younger demographic, contrasting with our previous purely-functional interface.  Every avenue for engagement is designed 
with accessibility in mind: the buttons grow on hover, they can be highlighted for further clarity, and the image/buttons 
can be expanded to make them even easier to interact with.  A large side menu also shows button states, making it easy 
for users to track the current state that they have loaded their red button with.  


# Hardware Layout
![System Diagram](/PlayPalDiagram.png)


# Simulated Backend

The original project scope was to emulate the wireless communication of these toys with an NRF24l01 module to eliminate 
the need to modify toys to achieve this functionality, however, for this R1 an alternate route was taken of reusing the 
mainboard from a disassembled toy to achieve the wireless component between toys. There are some advantages to this aproach, 
ease of implementation, and the speaker in the button from the original toy. Further evaluation of wether moving to the nrf 
module will outweigh the benifits of using the FYK58 mainboard. 

