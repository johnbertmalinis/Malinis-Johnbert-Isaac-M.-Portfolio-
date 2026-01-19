const int SENSOR_PIN = A0;
const int LED_PIN = 8;
int sensorValue = 0;
bool shouldBlink = false;
String userInput = "";

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("System Ready. Type 'stop' to stop blinking.");
}

void loop() {
  sensorValue = analogRead(SENSOR_PIN);
  Serial.print("Brightness: ");
  Serial.println(sensorValue);
  delay(200);

  if (sensorValue >= 220) {
    shouldBlink = true;
  }

  if (shouldBlink) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  if (Serial.available() > 0) {
    userInput = Serial.readStringUntil('\n');
    userInput.trim(); 
    userInput.toLowerCase();

    if (userInput == "stop") {
      shouldBlink = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("Blinking stopped.");
    }
  }
}
