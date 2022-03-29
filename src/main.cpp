#include "Keyboard.h"
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 0};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int NUM_SLIDERS = 4;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3};//, A1, A2, A3
int analogSliderValues[NUM_SLIDERS];

void setup() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
  pinMode(analogInputs[i], INPUT);
  }
  Serial.begin(9600);
  Keyboard.begin();
}
void sendMacroCommand(uint8_t key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}
void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    switch (key) {
      case '1':
        sendMacroCommand(KEY_F1);
        break;
      case '2':
        sendMacroCommand(KEY_F2);
        break;
      case '3':
        sendMacroCommand(KEY_F3);
        break;
      case '4':
        sendMacroCommand(KEY_F4);
        break;
      case '5':
        sendMacroCommand(KEY_F5);
        break;
      case '6':
        sendMacroCommand(KEY_F6);
        break;
      case '7':
        sendMacroCommand(KEY_F7);
        break;
      case '8':
        sendMacroCommand(KEY_F8);
        break;
      case '9':
        sendMacroCommand(KEY_F9);
        break;
      case '0':
        sendMacroCommand(KEY_F10);
        break;
      case '*':
        sendMacroCommand(KEY_F11);
        break;
      case '#':
        sendMacroCommand(KEY_F12);
        break;
      case 'A':
        sendMacroCommand('a');
        break;
      case 'B':
        sendMacroCommand('b');
        break;
      case 'C':
        sendMacroCommand('c');
        break;
      case 'D':
        sendMacroCommand('d');
        break;
    }

    delay(100);
    Keyboard.releaseAll();
  }
  updateSliderValues();
  sendSliderValues();
  delay(10);
}
//https://github.com/omriharel/deej usado como base para o controle
// do audio