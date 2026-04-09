#ifndef _ADAFRUIT_LEDBACKPACK_H
#define _ADAFRUIT_LEDBACKPACK_H

#include "ComponentBase.h"
#include <cstdlib>

#define SEVENSEG_DIGITS 5

class Adafruit_7segment : public ComponentBase {
public:
    Adafruit_7segment(void);

    bool begin(uint8_t _addr = 0x70);

    size_t write(const char *buffer, size_t size);
    void writeDigitRaw(uint8_t x, uint8_t bitmask);
    void writeDigitAscii(uint8_t x, uint8_t c, bool dot = false);

    inline void writeDigitNum(uint8_t x, uint8_t num, bool dot = false);  
    inline void drawColon(bool state);
    inline void print(long n, int base);
    inline void printNumber(long n, uint8_t base);
    
    void printFloat(double n, uint8_t fracDigits, uint8_t base);
    void printError(void);

    void writeDisplay(void);
protected:
    void buildKeyName(char buf[], uint16_t cbuf) const override;
private:
    uint8_t addr;
    uint8_t display[SEVENSEG_DIGITS];
};

void Adafruit_7segment::writeDigitNum(uint8_t x, uint8_t num, bool dot) {
    writeDigitAscii(x, '0'+num, dot);
}
void Adafruit_7segment::drawColon(bool state) {
    writeDigitRaw(2, state ? 2 : 0);
}

void Adafruit_7segment::printNumber(long n, uint8_t base) {
    printFloat(n, 0, base);
}

void Adafruit_7segment::print(long n, int base) { 
    printNumber(n, base); 
}

#endif
