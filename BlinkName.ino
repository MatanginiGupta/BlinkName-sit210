#include <string.h>

bool blinkingStatus = false;
String enteredText = "";
const int BUTTON_PIN = 7;
int buttonCounter;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

int getCharacterIndex(char character) {
  return (character - 'a');
}

String morseCodes[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

void flashMorse(String morseCode) {
  for (int k = 0; k < morseCode.length(); k++) {
    if (morseCode[k] == '.') {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    } else if (morseCode[k] == '-') {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
}

void loop() {
  if (digitalRead(3) == LOW) {
    if (!blinkingStatus) {
      blinkingStatus = true;

      if (enteredText == "") {
        Serial.println("Please input your name");
        while (!Serial.available()) {
          // Wait for serial data to be available
        }
        enteredText = Serial.readStringUntil('\n');
        Serial.println(enteredText);
      }

      for (int i = 0; i < enteredText.length(); i++) {
        int charIndex = getCharacterIndex(enteredText[i]);
        String morseCode = morseCodes[charIndex];
        flashMorse(morseCode);
        digitalWrite(LED_BUILTIN, LOW);
        delay(3000);
      }
    }
  } else {
    blinkingStatus = false;
  }
}
