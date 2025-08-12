#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define TRIGGER_PIN 2     // PB2
#define OUTPUT_PIN 3      // PB3
#define AUTO_SELECT_PIN 4 // PB4

bool ready = false;
bool ignoreCycleNum = false;   // Ignore number of desired revolutions if true
int cycleTime = 87;    // Time to spin once. Measured in milliseconds
int cycleNum = 3;      // Number of desired revolutions

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(AUTO_SELECT_PIN, INPUT_PULLUP);

  // Setup other pins as INPUT_PULLUP to decrease power
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void sleepMCU() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0, onWake, LOW);
  
  ADCSRA &= ~ bit(ADEN); // Disable analog-digital converter to reduce power
  power_all_disable();    // Turn all peripherals off
  power_timer0_enable();  // Enable tim0 to allow interrupts

  sleep_mode(); // Go to sleep

  sleep_disable();  // Execution resumes here on wakeup
  detachInterrupt(0); // Prevent further triggers while MCU is awake
}

void onWake() {
  ready = true;
  ignoreCycleNum = !digitalRead(AUTO_SELECT_PIN);
}

void loop() {
  static int currentTime = 0;
  if (ready) {
    if (ignoreCycleNum) {
      while(digitalRead(TRIGGER_PIN) == LOW) {
        digitalWrite(OUTPUT_PIN, HIGH); // Turn on FET while input is active
      }
      digitalWrite(OUTPUT_PIN, LOW);  // Turn off fet
    } else {
      digitalWrite(OUTPUT_PIN, HIGH);
      while(digitalRead(TRIGGER_PIN) == LOW) {
        if (currentTime < cycleNum * cycleTime) { // Keep track of how many ms has past since turn on
          currentTime += 1;   // Add a ms to the count
        } else {
          digitalWrite(OUTPUT_PIN, LOW);
        }
        delay(1); // wait a ms
      }
      digitalWrite(OUTPUT_PIN, LOW);
      currentTime = 0;
    }
  }
  sleepMCU();
}
