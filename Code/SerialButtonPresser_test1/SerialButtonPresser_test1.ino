int redPin = 2;
int bluePin = 3;
int greenPin = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  digitalWrite(redPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(1000);
    
}

void loop() {

  Serial.print("\nwaiting for input; \n'red', \n'blue', \n'green'");
  while(Serial.available() == 0){
    //do nothing?
  }
  String buttonChoice = Serial.readString();
  Serial.print("\nButton Choice: " + buttonChoice);
  if (buttonChoice == "red\n"){
      Serial.print("pressing red button for 100ms");
      digitalWrite(redPin, LOW);
      delay(100);
      digitalWrite(redPin, HIGH);
  }
  else if (buttonChoice == "blue\n"){
      Serial.print("pressing blue button for 100ms");
      digitalWrite(bluePin, LOW);
      delay(100);
      digitalWrite(bluePin, HIGH);
  }
  else if (buttonChoice == "green\n"){
      Serial.print("pressing green button for 100ms");
      digitalWrite(greenPin, LOW);
      delay(100);
      digitalWrite(greenPin, HIGH);
  }
  else{
    Serial.print("\ninvalid input, try again");
  }
}
