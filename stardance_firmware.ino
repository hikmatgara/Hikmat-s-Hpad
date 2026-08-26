// Stardance 3-Key Hackpad Firmware
// Seeeduino XIAO (SAMD21) with mechanical switches on D0, D1, D2

#include <Keyboard.h>

// Pin mapping (from schematic)
const int KEY1_PIN = 0;  // D0 - PA02
const int KEY2_PIN = 2;  // D2 - PA10
const int KEY3_PIN = 1;  // D1 - PA4

// Debounce time in milliseconds
const int DEBOUNCE_DELAY = 20;

// Button state tracking
int key1State = HIGH;
int key2State = HIGH;
int key3State = HIGH;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;

void setup() {
  // Set pin modes (INPUT_PULLUP for mechanical switches)
  pinMode(KEY1_PIN, INPUT_PULLUP);
  pinMode(KEY2_PIN, INPUT_PULLUP);
  pinMode(KEY3_PIN, INPUT_PULLUP);

  // Initialize keyboard library
  Keyboard.begin();

  // Small delay for stability
  delay(100);
}

void loop() {
  checkKey(KEY1_PIN, &key1State, &lastDebounceTime1, 1);
  checkKey(KEY2_PIN, &key2State, &lastDebounceTime2, 2);
  checkKey(KEY3_PIN, &key3State, &lastDebounceTime3, 3);

  delay(5);
}

void checkKey(int pin, int* lastState, unsigned long* lastTime, int keyNum) {
  int reading = digitalRead(pin);

  // Reset debounce timer if pin changed
  if (reading != *lastState) {
    *lastTime = millis();
  }

  // Register press/release after debounce period
  if ((millis() - *lastTime) > DEBOUNCE_DELAY) {
    if (reading == LOW && *lastState == HIGH) {
      // Button pressed (active LOW with pullup)
      handleKeyPress(keyNum);
      *lastState = LOW;
    } else if (reading == HIGH && *lastState == LOW) {
      // Button released
      *lastState = HIGH;
    }
  }
}

void handleKeyPress(int keyNum) {
  // Define shortcuts for each key (3-key combinations)
  switch(keyNum) {
    case 1:
      // Key 1 (D0): Screenshot - Ctrl+Shift+S
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      Keyboard.releaseAll();
      break;

    case 2:
      // Key 2 (D2): New Window/Incognito - Ctrl+Shift+N
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('n');
      Keyboard.releaseAll();
      break;

    case 3:
      // Key 3 (D1): Reopen Closed Tab - Ctrl+Shift+T
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      break;
  }
}
