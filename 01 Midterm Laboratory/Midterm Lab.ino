
void checkSerial();
void processCommand(String command);
void updateAutoMode();
void readSensorAndPrintData();


const int SENSOR_PIN = A0;  // Photoresistor
const int GREEN_PIN = 11;
const int YELLOW_PIN = 12;
const int RED_PIN = 13;

bool isManualMode = true; 
int lowThreshold = 40;    
int highThreshold = 70;   

String commandString = ""; 


unsigned long lastAutoChange = 0;
const long autoInterval = 10000; 

void setup() {
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  commandString.reserve(100); 
  
  Serial.println("System Initialized.");
  Serial.println("Mode: Manual (Default)");
  Serial.println("Thresholds: Low=40, High=70");
}

void loop() {
  checkSerial(); 
  updateAutoMode();
  readSensorAndPrintData();
  delay(1000);
}


void checkSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') { // Command received (end of line)
      processCommand(commandString);
      commandString = ""; // Clear the buffer
    } else {
      commandString += c;
    }
  }
}


void processCommand(String command) {
  command.trim();
  command.toUpperCase(); 

  if (command == "MODE AUTO") {
    isManualMode = false;
    lastAutoChange = millis(); 
    Serial.println("Mode set to: Automatic");

  } else if (command == "MODE MANUAL") {
    isManualMode = true;
    Serial.println("Mode set to: Manual");

  } else if (command.startsWith("SET LOW ")) {
    if (isManualMode) {
      int newLow = command.substring(8).toInt();
      if (newLow >= 0 && newLow < highThreshold) {
        lowThreshold = newLow;
        Serial.print("Low threshold set to: ");
        Serial.println(lowThreshold);
      } else {
        Serial.println("Error: Invalid value. Low threshold must be >= 0 and < high threshold.");
      }
    } else {
      Serial.println("Error: Wrong command (Cannot set thresholds in Automatic mode)");
    }
  }

  else if (command.startsWith("SET HIGH ")) {
    if (isManualMode) {
      int newHigh = command.substring(9).toInt();
      if (newHigh > lowThreshold && newHigh <= 100) {
        highThreshold = newHigh;
        Serial.print("High threshold set to: ");
        Serial.println(highThreshold);
      } else {
        Serial.println("Error: Invalid value. High threshold must be > low threshold and <= 100.");
      }
    } else {
      Serial.println("Error: Wrong command (Cannot set thresholds in Automatic mode)");
    }
  } 

  else {
    Serial.println("Error: Wrong command");
  }
}


void updateAutoMode() {
  if (isManualMode) {
    return; 

  if (millis() - lastAutoChange > autoInterval) {
    lastAutoChange = millis();
    int weather = random(3);

    Serial.println("\n--- Simulating environmental change ---");

    switch (weather) {
      case 0: // Cloudy 
        lowThreshold = 0;
        highThreshold = 40;
        Serial.println("Condition: Cloudy (Thresholds 0-40)");
        break;
      case 1: // Normal 
        lowThreshold = 41;
        highThreshold = 70;
        Serial.println("Condition: Normal (Thresholds 41-70)");
        break;
      case 2: // Bright Sunlight 
        lowThreshold = 71;
        highThreshold = 100;
        Serial.println("Condition: Bright Sunlight (Thresholds 71-100)");
        break;
    }
    Serial.println();
  }
}
}
/**
 * Reads the photoresistor, updates LEDs, and prints all data.
 */
void readSensorAndPrintData() {
  // 1. Read sensor and convert to percentage
  int sensorValue = analogRead(SENSOR_PIN);
  int intensityPercent = map(sensorValue, 0, 1023, 0, 100);

  // --- Local variables for display ---
  String activeLED;
  String currentMode = isManualMode ? "Manual" : "Automatic";
  String environment;

  // 2. Control LEDs based on thresholds (Req #2, #3)
  if (intensityPercent <= lowThreshold) {
    // LOW intensity
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
    activeLED = "Green";
  } else if (intensityPercent > lowThreshold && intensityPercent <= highThreshold) {
    // MED intensity
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
    activeLED = "Yellow";
  } else {
    // HIGH intensity
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    activeLED = "Red";
  }

  if (intensityPercent <= 40) {
    environment = "Cloudy";
  } else {
    environment = "Clear";
  }

  Serial.print("Light Intensity: ");
  Serial.print(intensityPercent);
  Serial.print("%");

  Serial.print(" Active LED: ");
  Serial.print(activeLED);

  Serial.print(" Current Mode: "); 
  Serial.print(currentMode);

  if (currentMode == "Automatic"){
    Serial.print(" Environment: ");
    Serial.print(environment);
  };

  Serial.println();
}