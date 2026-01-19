#define tempPin A0
#define photoPin A2
#define ledBuzzPin 12

const float TEMP_THRESHOLD = 50.0;
const int BRIGHTNESS_THRESHOLD = 220;

const float NOMINAL_RESISTANCE = 10000;
const float NOMINAL_TEMPERATURE_K = 298.15;
const float B_VALUE = 3950;
const float SERIES_RESISTOR = 10000;

void setup () {
  pinMode(ledBuzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop () {
  float currentTemp = readTemperature();
  int currentBrightness = readBrightness () / 3.6;
  
  Serial.print("Temperature: ");
  Serial.print(currentTemp);
  Serial.print(" C | Brightness: ");
  Serial.println(currentBrightness);
  
  if (currentTemp >= TEMP_THRESHOLD && currentBrightness >= BRIGHTNESS_THRESHOLD) {
    digitalWrite(ledBuzzPin, HIGH);
    delay(100); 
    digitalWrite(ledBuzzPin, LOW);
    delay(100);
    
    Serial.println("!!! 🔥 FIRE ALERT - THRESHOLDS CROSSED! 🔥 !!!");
    
  } else {
    digitalWrite(ledBuzzPin, LOW);
  }
  
  delay(1000); 
}

int readBrightness() {
  return analogRead(photoPin);
}

float readTemperature() {
  int analogReading = analogRead(tempPin);
  
  float resistance = SERIES_RESISTOR * ((1023.0 / analogReading) - 1);
  
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= B_VALUE;
  steinhart += 1.0 / NOMINAL_TEMPERATURE_K;
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;
  
  return steinhart;
}