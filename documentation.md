
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

# Individual Contributions (Comprehensive)

## Cameron Warnick  
• Learned how the hardware functions and conducted preliminary project research, despite hardware-based projects being outside my field of specialization.  
• Wrote the entire Project Proposal.  
• Contributed to the Button Design and Requirements Template.  
• Refactored the initial code base: WebserverButtons.ino: also involved researching a completely new domain of programming until I actually understood how it works through-and-through.  
• Built a prototype in bare HTML/CSS for the digital interface.  
• First redesign of the project interface: created a separate stylesheet, restyled and rebuilt the entire HTML/CSS layout, and tediously converted it to print statements.  
• Built another HTML/CSS prototype and tediously converted it to serial print statements. Second redesign of the interface: changed the interface style to support five buttons and extended the logic to use five buttons.  Streamlined the existing UI logic.  
• Wrote all of the R1 UI Documentation.  
• Built a third HTML/CSS prototype.  Third redesign of the interface: moved from serial print statements to actual HTML/CSS, completely revamped the entire design, mapped buttons to an image of the product, used extensive media queries to make it responsive, and created a new menu to display the state for each button.  
• Researched the JS Fetch API to handle completely new constraints for the application.  Now, the central methodology we were using (rerouting based on button clicks to manage state) was no longer valid, as we changed the overarching medium we were working with.  This was a huge curveball and required a complete rethinking of the project in addition to the third redesign.  Notably, there is no handbook that tells you how to solve this problem: I just had to figure something out, in a completely unfamiliar domain.  
• Modified the system to use HTTP queries in a JavaScript section within the HTML file to manage button state updates and track state based on user input.  
• Fourth redesign, revamped entire website HTML / CSS structure  
• Used a new technique to fix button positions on toy image with only one CSS rule.  
• Used images of the buttons themselves overlaid on the toy image buttons, making the application look significantly better.  
• Added button-highlight mode  
• Added image expand mode  
• Added new menu to control accessibility features  
• Revamped heading, added new tagline  
• Revamped background: moving colored gradient with dark filter overlaid, keeping it un-intrusive while highlighting interactive elements.  
• Re-implemented glowing buttons, added a dynamic gradient for the title (PlayPal).   
• Refactored HTML/CSS layout  
• Refactored HTML/CSS layout  
