// global variables
int setPin = -1;
unsigned long currentTime = millis();
unsigned long prevTime = 0;
const int inputPin = 7;
int timeoutTime = 150;

// Switches setPin value to new pin number
void switchPin(int pinNum){
  setPin = pinNum;
}

// Function that activates a pin as long as the pin number is valid
void activatePin(){<
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(setPin, LOW);
  }
  else{
    Serial.println("Invalid pin number set on activation");
  }
}

// Function that deactivates a pin as long as the pin number is valid
void deactivatePin(){
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(setPin, HIGH);
  }
  else{
    Serial.println("Invalid pin number set on deactivate");
  }
}

// changes timeout time
void changeTimeout(int newTime){
  if(newTime >= 150){
    timeoutTime = newTime;
  }
}

// a standard default button pressed function
void buttonPressedStandard(){
  currentTime = millis();
  prevTime = currentTime;
  activatePin();

  while(!(currentTime - prevTime < timeoutTime)){
    currentTime = millis();
  }

  deactivatePin();
}

// when the button is pressed in sequential mode. It will count the presses and select that pin
void buttonPressedSequential(){
  setPin = 2;
  currentTime = millis();
  prevTime = currentTime;

  // waits for button presses
  while(!(currentTime - prevTime <= 500)){
    currentTime = millis();
    if(digitalRead(inputPin) == LOW && setPin < 6){
      setPin += 1;
      prevTime = currentTime; // reset timer
    }
    else if(setPin == 6){
      break;
    }
  }

  activatePin();
  currentTime = millis();
  prevTime = currentTime;

  while(!(currentTime - prevTime < timeoutTime)){
    currentTime = millis();
  }

  deactivatePin();
}

