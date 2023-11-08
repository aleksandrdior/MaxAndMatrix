#include "MaxAndMatrix.h"

//      Register    Address-1
#define DECODEMODE  0x9-1
#define INTENSITY   0xA-1
#define SCANLIMIT   0xB-1
#define SHUTDOWN    0xC-1
#define DISPLAYTEST 0xF-1

MaxAndMatrix:: MaxAndMatrix(int dinPin, int clkPin, int csPin) {
  din = dinPin;
  clk = clkPin;
  cs = csPin;
}

void MaxAndMatrix::loadByte(int addr, byte data = 0) {       // загрузка байта в регистры микросхемы MAX7219
  digitalWrite(cs, LOW);
  shiftOut(din, clk, MSBFIRST, addr + 1);   // В MAX7219 нумерация аресов регистров строк LED начинается с 1
  shiftOut(din, clk, MSBFIRST, data);
  digitalWrite(cs, HIGH);
}

void MaxAndMatrix::setRotation(int numberOFturns) {
  nturns = numberOFturns % 4;               // Вращаем только 3 раза. numberOFturns=0 без вращения
}                                           // 1 на 90° против часовой стрелки, 2 на 180°, 3 на 270°

void MaxAndMatrix::loadMatrix(byte matrix[]) {
  byte rmatrix[8];                          // вспомогательная матрица.
  byte zmatrix[8];                          // копия матрицы пользователя, пользовательскую не портим.
  
  for (int i = 0 ; i < 8; i++) {
    zmatrix[i] = matrix[i];                 // создание копии матрицы пользователя
  }
  for (int r = 1; r <= nturns; r++) {       // вращение матрицы nturns раз
    for (int i = 0; i < 8; i++) {           // вращение на 90° против часовой стрелки один раз
      rmatrix[i] = 0;
      for (int j = 0; j < 8; j++) {
        rmatrix[i] |= ((zmatrix[7 - j] & (1 << i)) >> i) << j;
      }
    }
    for (int i = 0; i < 8; i++) {
      zmatrix[i] = rmatrix[i];              // копирование повёрнутой матрицы в исходную
    }                                       // после каждого поворота
  }
  for (int i = 0 ; i < 8; i++) {
    loadByte(i, zmatrix[i]);                // загрузка матрицы в микросхему MAX7219
  }
}

void MaxAndMatrix::clear(void) {
  for (int i = 0 ; i < 8; i++) {
    loadByte(i, 0);                         // загрузка 0 в регистры микросхемы MAX7219 по адресам LED
  }
}

void MaxAndMatrix::begin(bool testMatrix = 0) {
  pinMode(din , OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(cs, OUTPUT);
  clear();                                  // очистить LED регистры микросхемы MAX7219
  loadByte(DECODEMODE, 0);                  // 0 для матриц, остальное для семисегментных индикаторов
  loadByte(INTENSITY, 7);                   // средняя яркость
  loadByte(SCANLIMIT, 7);                   // количество рядов в LED матрице
  loadByte(SHUTDOWN , 1);                   // включить матрицу
  loadByte(DISPLAYTEST, 0);                 // запретить тест LED матрицы
  if (testMatrix) {                         // тестировать LED матрицу 3сек. если begin(1)
    loadByte(DISPLAYTEST, 1);
    delay(3000);
    loadByte(DISPLAYTEST, 0);
  }
}

void MaxAndMatrix::force(int powerOFlight) {
  loadByte(INTENSITY, powerOFlight);        // меняем яркость свечения светодиодов powerOFlight=[0...15]
}

void MaxAndMatrix::onOff(bool HighLow) {
  loadByte(SHUTDOWN, HighLow);              // включить/выключить LED матрицу
}
