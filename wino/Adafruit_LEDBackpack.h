#ifndef _ADAFRUIT_LEDBACKPACK_H
#define _ADAFRUIT_LEDBACKPACK_H

#include "ComponentBase.h"

#define SEVENSEG_DIGITS 5

class Adafruit_7segment : public ComponentBase {
public:
    Adafruit_7segment(void);

    bool begin(uint8_t _addr = 0x70);

    void writeDigitRaw(uint8_t x, uint8_t bitmask);
    void writeDigitAscii(uint8_t x, uint8_t c, bool dot = false);
    inline void writeDigitNum(uint8_t x, uint8_t num, bool dot = false);  
    inline void drawColon(bool state);
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

#endif
