// global variables
int setPin[] = {-1, -1};
const int SwitLed = 8;
const int inputPin[] = {7, 11};
int defaultTimeoutTime = 150;
int sequentialCounter = 2;

// Switches setPin value to new pin number
void switchPin(int inputIndex, int pinNum){
  setPin[inputIndex] = pinNum;
  Serial.print("\nSwitchPin\noutput pin set to: ");
  Serial.println(setPin[inputIndex]);
}

// Function that activates a pin as long as the pin number is valid
void activatePin(int inputIndex){
  if(setPin[inputIndex] >= 2 && setPin[inputIndex] <= 6){
    digitalWrite(SwitLed, HIGH);
    digitalWrite(setPin[inputIndex], LOW);
    Serial.println("Pin Low");
  }
  else{
    Serial.println("ERROR: Invalid pin number set on activation");
  }
  return;
}

// Function that deactivates a pin as long as the pin number is valid
void deactivatePin(int inputIndex){
  if(setPin[inputIndex] >= 2 && setPin[inputIndex] <= 6){
    digitalWrite(SwitLed, LOW);
    digitalWrite(setPin[inputIndex], HIGH);
    Serial.println("pin High");
  }
  else{
    Serial.println("ERROR: Invalid pin number set on deactivate");
  }
  return;
}

// a standard default button pressed function
void buttonPressedStandard(unsigned long currentTime, unsigned long previousTime, int inputIndex){
  activatePin(inputIndex);

  while(currentTime - previousTime < defaultTimeoutTime){
    currentTime = millis();
  }

  deactivatePin(inputIndex);

  return;
}

// when the button is pressed in sequential mode. It will count the presses and select that pin
void buttonPressedSequential(unsigned long currentTime, unsigned long previousTime, int inputIndex){
  
  while(currentTime - previousTime < 500){
    currentTime = millis();

    if(digitalRead(inputPin[inputIndex]) == LOW){
      sequentialCounter++;
      previousTime = currentTime;
    }
  }

  switchPin(inputIndex, sequentialCounter);

  activatePin(inputIndex);

  while(currentTime - previousTime < defaultTimeoutTime){
    currentTime = millis();
  }

  deactivatePin(inputIndex);

  return;
}