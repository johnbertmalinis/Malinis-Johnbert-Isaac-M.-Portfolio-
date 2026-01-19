int leds[] = {12, 11, 10, 9, 8};
int numLeds = 5;

int PWM[] = {8, 12};

void setup() {
  int i = 0;
  while (i < numLeds) {
    pinMode(leds[i], OUTPUT);
    i++;
  }
}

void loop() {
  for (int i = 0; i < numLeds; i++) {
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      analogWrite(leds[i], brightness);
      delay(20);
    }
  }

  for (int i = 0; i < numLeds; i++) {
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
      analogWrite(leds[i], brightness); 
      delay(20);
    }
  }
}