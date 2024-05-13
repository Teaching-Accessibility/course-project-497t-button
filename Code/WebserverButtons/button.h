// global variables
int setPin = -1;
unsigned long h_currentTime = millis();
unsigned long h_previousTime = 0;
const int inputPin = 7;
int buttonTimeoutTime = 150;

// Switches setPin value to new pin number
void switchPin(int pinNum){
  setPin = pinNum;
  Serial.println("\nSwitchPin\noutput pin set to: " + setPin);
}

// Function that activates a pin as long as the pin number is valid
void activatePin(){
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(setPin, LOW);
  }
  else{
    Serial.println("Invalid pin number set on activation");
  }
  return;
}

// Function that deactivates a pin as long as the pin number is valid
void deactivatePin(){
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(setPin, HIGH);
  }
  else{
    Serial.println("Invalid pin number set on deactivate");
  }
  return;
}

// changes timeout time
void changeTimeout(int newTime){
  if(newTime >= 150){
    buttonTimeoutTime = newTime;
  }
  return;
}

// a standard default button pressed function
void buttonPressedStandard(){
  h_currentTime = millis();
  h_previousTime = h_currentTime;
  activatePin();

  while(!(h_currentTime - h_previousTime < buttonTimeoutTime)){
    h_currentTime = millis();
  }

  deactivatePin();
  return;
}

// when the button is pressed in sequential mode. It will count the presses and select that pin
void buttonPressedSequential(){
  setPin = 2;
  h_currentTime = millis();
  h_previousTime = h_currentTime;

  // waits for button presses
  while(!(h_currentTime - h_previousTime <= 500)){
    h_currentTime = millis();
    if(digitalRead(inputPin) == LOW && setPin < 6){
      setPin += 1;
      h_previousTime = h_currentTime; // reset timer
    }
    else if(setPin == 6){
      break;
    }
  }

  activatePin();
  h_currentTime = millis();
  h_previousTime = h_currentTime;

  while(!(h_currentTime - h_previousTime < 150)){
    h_currentTime = millis();
  }

  deactivatePin();
  return;
}

