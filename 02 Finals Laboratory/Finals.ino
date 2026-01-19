const int BUTTON_PIN = 2;   
const int GROUP_NUMBER = 5; 

int lastButtonState = HIGH;      // The previous stable state
int currentButtonState = HIGH;   // The current stable state
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  Serial.begin(9600);               
}

void loop() { 
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {
        Serial.println(GROUP_NUMBER);
      }
    }
  }

  lastButtonState = reading;
}