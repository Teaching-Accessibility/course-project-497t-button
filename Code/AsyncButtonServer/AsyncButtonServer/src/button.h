// global variables
int setPin = -1;
const int SwitLed = 8;
const int inputPin = 7;
int defaultTimeoutTime = 150;
int sequentialCounter = 2;

// Switches setPin value to new pin number
void switchPin(int pinNum){
  setPin = pinNum;
  Serial.print("\nSwitchPin\noutput pin set to: ");
  Serial.println(setPin);
}

// Function that activates a pin as long as the pin number is valid
void activatePin(){
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(SwitLed, HIGH);
    digitalWrite(setPin, LOW);
    Serial.println("Pin Low");
  }
  else{
    Serial.println("ERROR: Invalid pin number set on activation");
  }
  return;
}

// Function that deactivates a pin as long as the pin number is valid
void deactivatePin(){
  if(setPin >= 2 && setPin <= 6){
    digitalWrite(SwitLed, LOW);
    digitalWrite(setPin, HIGH);
    Serial.println("pin High");
  }
  else{
    Serial.println("ERROR: Invalid pin number set on deactivate");
  }
  return;
}

// a standard default button pressed function
void buttonPressedStandard(unsigned long currentTime, unsigned long previousTime){
  activatePin();

  while(currentTime - previousTime < defaultTimeoutTime){
    currentTime = millis();
  }

  deactivatePin();

  return;
}

// when the button is pressed in sequential mode. It will count the presses and select that pin
void buttonPressedSequential(unsigned long currentTime, unsigned long previousTime){
  
  while(currentTime - previousTime < 500){
    currentTime = millis();

    if(digitalRead(inputPin) == LOW){
      sequentialCounter++;
      previousTime = currentTime;
    }
  }

  switchPin(sequentialCounter);

  activatePin();

  while(currentTime - previousTime < defaultTimeoutTime){
    currentTime = millis();
  }

  deactivatePin();

  return;
}