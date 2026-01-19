int leds[] = {12,11,10,9,8};

void setup(){
    for (int i = 0; i < 5; i++){
      pinMode(leds[i], OUTPUT);
  }
}

void loop(){
  for (int i = 0; i < 5; i++){
    digitalWrite(leds[i], HIGH);
    delay(1000);
  }
  
   for (int i = 0; i < 5; i++){
    digitalWrite(leds[i], LOW);
    delay(1000);
  }

}
