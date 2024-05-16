# PlayPal Documentation
Written by Jack Stephens (5.15.24)

## button.h
### Global Variables
int setPin - The pin that will be activated, selected by the user on the webpage

const int SwitLed - Constant storing the LED pin

const int inputPin - the pin the switch is plugged into

int buttonTimeoutTime - how long (in ms) the button will timeout after being pressed


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