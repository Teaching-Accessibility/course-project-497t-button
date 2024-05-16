# PlayPal Documentation
Written by Jack Stephens (5.15.24)
UI Section: Cameron Warnick

## button.h
### Global Variables
- int setPin - The pin that will be activated, selected by the user on the webpage

- const int SwitLed - Constant storing the LED pin

- const int inputPin - the pin the switch is plugged into

- int buttonTimeoutTime - how long (in ms) the button will timeout after being pressed


### Switch Pin Function
switchPin(int pinNum)


Description-

    Switches the setPin variable to the number stored in pinNum


Parameters-

    pinNum - the pin you want to swap to


Returns-

    N/A


### Activate Pin Function
activatePin()


Description-

    Turns on the LED and the set pin and then prints serial confirmation


Parameters-
    
    N/A


Returns-
    
    N/A


### Deactivate Pin Function
deactivatePin()


Description-
    
    Turns off the LED and the set pin and then prints serial confirmation


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
which is conveniently placed on top of the button on the image, to start the dance and song
associated with this number.  

## Design Principles

Given that we are running hardware that imposes tight limitations on memory and throughput,
the design for this page is purely functional. However, it maintains familiarity and cohesion with the official product
by displaying a sample Linkimals toy image and mapping the HTML button elements to their respective 
positions on the that image.  It also provides some temporary debugging information as a sanity check
for button state, which will be removed for the final product.  Our goal is to ensure that users enjoy a seamless
transition from the default toy to our modified hardware and engagement patterns, and we are actively working to 
further refine this process.
