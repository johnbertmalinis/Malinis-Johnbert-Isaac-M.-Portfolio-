// Pin Definitions
const int redPin = 7;
const int greenPin = 6;
const int bluePin = 5;

const int btn1 = 12; // Controls Red
const int btn2 = 11; // Controls Green
const int btn3 = 10; // Controls Blue

void setup() {
  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Using PULLUP: button is LOW when pressed
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
}

void loop() {
  // 1. Handle Serial Commands (Inbound Signal)
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    
    // Case insensitivity check (though using numbers, this handles stray chars)
    incomingByte = tolower(incomingByte); 

    if (incomingByte == '1') {
      digitalWrite(redPin, !digitalRead(redPin));
    } 
    else if (incomingByte == '2') {
      digitalWrite(greenPin, !digitalRead(greenPin));
    } 
    else if (incomingByte == '3') {
      digitalWrite(bluePin, !digitalRead(bluePin));
    }
    else if (incomingByte == 'o') { // Command for "All On"
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
    }
    else if (incomingByte == 'f') { // Command for "All Off" (O for Off)
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
    }
  }

  // 2. Handle Manual Button Presses (Extra logic for hardware completeness)
  if (digitalRead(btn1) == LOW) { toggleLED(redPin); }
  if (digitalRead(btn2) == LOW) { toggleLED(greenPin); }
  if (digitalRead(btn3) == LOW) { toggleLED(bluePin); }
}

void toggleLED(int pin) {
  digitalWrite(pin, !digitalRead(pin));
  delay(250); // Debounce delay
}
