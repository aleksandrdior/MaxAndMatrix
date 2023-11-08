#ifndef MaxAndMatrix_h
#define MaxAndMatrix_h
#include <Arduino.h>

class MaxAndMatrix {
  private :
    int din;
    int clk;
    int cs;
    int nturns = 0;                                 // Число поворотов на 90 против часовой
  public:
    MaxAndMatrix(int dinPin, int clkPin, int csPin);
    void begin(bool testMatrix = 0);                // зажечь все светодиоды если testMatrix = 1
    void loadByte(int addr, byte data = 0);         // загрузить одну строку addr = [0...7]
    void setRotation(int numberOFturns);            // установить число поворотов матрицы на 90
    void loadMatrix(byte matrix[]);                 // загрузить все 8 регистров LED матрицы
    void force(int powerOFlight);                   // яркость powerOFlight = [0...15]
    void onOff(bool HighLow);                       // включить/выключить LED
    void clear(void);                               // очистить все 8 регистров LED матрицы
};

#endif	//MaxAndMatrix.h
