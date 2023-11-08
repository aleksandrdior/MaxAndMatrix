#include "MaxAndMatrix.h"

int dataPin = 12;                // DIN
int clockPin = 11;               // CLK
int csPin = 10;                  // LOAD (CS)
MaxAndMatrix led88 = MaxAndMatrix(dataPin, clockPin, csPin);

byte matrix[8] = {0b01110001,
                  0b11011011,
                  0b10001110,
                  0b10001100,
                  0b10001000,
                  0b11111111,
                  0b10000001,
                  0b11111111
                 };

void setup() {
  led88.begin(0);
  led88.force(0);
}

void loop() {
  for (int i=0; i<4; i++) {
  led88.setRotation(i);
  led88.loadMatrix(matrix);
  delay(700);
  }
}
