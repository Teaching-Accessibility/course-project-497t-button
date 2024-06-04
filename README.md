# The PlayPal
Steven Grubb, Cameron Warnick, and Jack Stephens


### Description:

This project leverages the functionality of an inexpensive ESP32 microcontroller to connect an accesibility switch to the Fisher-Price
Linkimals line of childrens toys. This connection is done wirelessly, so that there is no modification required to the target toy, and the user has far more freedom of movment, not constrained by wires. The greatest expantion of functionality comes from the single switch being able to operate multiple toy functions, the active function selectable via a web interface hosted on the ESP controller within the switch housing. The approach taken of not modifying the target toy, allows the user to purchase readily available off the shelf toys, and without any further effort those toys are 'switch enabled', ready for use. 

Further information on exact implementations can be found in our [documentation](documentation.md)

1.	Install [Arduino IDE](https://www.arduino.cc/en/software)
2.	Install the latest release of [PlayPal software](https://github.com/Teaching-Accessibility/course-project-497t-button/releases)
3.	Extract the contents of the release to a safe location
4.	Run Arduino IDE
5.	Open the WebserverButtons.cpp file in Arduino IDE
    a. Located in the extracted files at Code/AsyncButtonServer/AsyncButtonServer/src/WebserverButtons.cpp
6.	Update the credentials found on line 24 and 25 with your network credentials
7.	Upload the files to your Arduino ESP32
8.	Turn on PlayPal
9.	An LED will light up to signify a WiFi connection
10.	Enjoy


### Bugs and Issues:
[PlayPal Issue Reporting](https://github.com/Teaching-Accessibility/course-project-497t-button/issues)

### License:
All intellectual property (IP)-related activities at Western are managed by RSP, including initial assessment, 
protection, and development through licensing and other third-party agreements.
