#include "led_utils.h"

// 1. Create objects with PIN and NAME
LedController redLed(8, "Red");
LedController greenLed(9, "Green");
LedController blueLed(10, "Blue");

// 2. Create array of pointers
LedController* myLedArray[] = { &redLed, &greenLed, &blueLed };

// 3. Create Group Manager
LedGroup allLeds(myLedArray, 3);

bool running = true;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for connection
  Serial.println("\n======= SYSTEM MENU =======");
  Serial.println("[R] Red ON/OFF");
  Serial.println("[G] Green ON/OFF");
  Serial.println("[B] Blue ON/OFF");
  Serial.println("[A] Turn All LEDs ON");
  Serial.println("[O] Turn All LEDs OFF");
  Serial.println("[X] Exit System");
  Serial.println("===========================");
  Serial.println("System Ready. Waiting for input...");
}

void loop() {

  if (running && Serial.available() > 0) {


    char input = Serial.read();
    
    
    // Ignore newline characters (fixes double printing issues)
    if (input == '\n' || input == '\r') return;

    char command = tolower(input);

    switch (command) {
      case 'r': 
        redLed.toggle(); 
        break;
      case 'g': 
        greenLed.toggle(); 
        break;
      case 'b': 
        blueLed.toggle(); 
        break;
      case 'a': 
        allLeds.turnAllOn(); 
        break;
      case 'o': 
        allLeds.turnAllOff(); 
        break;
      case 'x':
        allLeds.turnAllOff(); 
        Serial.print("Goodbye");
        running = false;
        break;
      default: 
        Serial.print("Error: Unknown command '");
        Serial.print(command);
        Serial.println("'");
        break;
    }
  }
}