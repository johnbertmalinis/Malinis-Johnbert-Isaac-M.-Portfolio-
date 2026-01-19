#ifndef LED_UTILS_H
#define LED_UTILS_H

#include <Arduino.h>

// --- CLASS 1: Individual LED Controller ---
class LedController {
  private:
    int pin;
    bool state;
    String name; // Added to identify the LED in logs

  public:
    // Constructor now takes a Name string
    LedController(int p, String n) {
      pin = p;
      name = n;
      state = false;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    void toggle() {
      state = !state;
      digitalWrite(pin, state ? HIGH : LOW);
      
      // LOGGING ADDED HERE
      Serial.print(name);
      Serial.print(" is now ");
      Serial.println(state ? "ON" : "OFF");
    }

    void turnOn() {
      state = true;
      digitalWrite(pin, HIGH);
      // No log here to avoid spamming when using "All On"
    }

    void turnOff() {
      state = false;
      digitalWrite(pin, LOW);
      // No log here to avoid spamming when using "All Off"
    }
};

// --- CLASS 2: Group Manager ---
class LedGroup {
  private:
    LedController** leds;
    int count;

  public:
    LedGroup(LedController* ledArray[], int size) {
      leds = ledArray;
      count = size;
    }

    void turnAllOn() {
      for (int i = 0; i < count; i++) {
        leds[i]->turnOn();
      }
      // LOGGING ADDED HERE
      Serial.println("System: All LEDs turned ON");
    }

    void turnAllOff() {
      for (int i = 0; i < count; i++) {
        leds[i]->turnOff();
      }
      // LOGGING ADDED HERE
      Serial.println("System: All LEDs turned OFF");
    }
};

#endif