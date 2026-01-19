// LED Pins
const int RED_LED = 7;
const int GREEN_LED = 6;
const int BLUE_LED = 5;

// Button Pins
const int BTN1 = 12;
const int BTN2 = 11;
const int BTN3 = 10;

// LED states
bool redState = false;
bool greenState = false;
bool blueState = false;

// Button states
bool lastBtn1 = HIGH;
bool lastBtn2 = HIGH;
bool lastBtn3 = HIGH;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  handleButtons();
  handleSerial();
}

void handleButtons() {
  bool b1 = digitalRead(BTN1);
  bool b2 = digitalRead(BTN2);
  bool b3 = digitalRead(BTN3);

  if (b1 == LOW && lastBtn1 == HIGH) {
    Serial.println("R");
    delay(50);
  }
  if (b2 == LOW && lastBtn2 == HIGH) {
    Serial.println("G");
    delay(50);
  }
  if (b3 == LOW && lastBtn3 == HIGH) {
    Serial.println("B");
    delay(50);
  }

  lastBtn1 = b1;
  lastBtn2 = b2;
  lastBtn3 = b3;
}

void handleSerial() {
  if (Serial.available()) {
    char c = Serial.read();
    c = tolower(c);

    if (c == '1') {
      redState = !redState;
      digitalWrite(RED_LED, redState);
    }
    else if (c == '2') {
      greenState = !greenState;
      digitalWrite(GREEN_LED, greenState);
    }
    else if (c == '3') {
      blueState = !blueState;
      digitalWrite(BLUE_LED, blueState);
    }
  }
}

