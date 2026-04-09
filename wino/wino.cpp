#include "wino.h"

#include <emscripten/emscripten.h>
#include <cstdio>
#include "ComponentBase.h"

extern void setup();
extern void loop ();

static double start;

extern "C" {
    void wino_setup() { 
        EM_ASM(Module); 
        start = emscripten_get_now();
        setup(); 
    }
    void wino_loop () { 
        loop (); 
    }
}

#define IO_PWM      0b000001
#define IO_ANALOG   0b000010
#define IO_SDA      0b000100
#define IO_SCL      0b001000
#define IO_TX       0b010000
#define IO_RX       0b100000

class IOPin : public ComponentBase {
    int _pin;
    int _flags;
public:
    IOPin(int pin, int flags = 0) : 
        _pin(pin),
        _flags(flags)
    {} 
    inline int get() const {
        return EM_ASM_INT(return Module.Wino.byId($0)?.get?.($1) ?? 0, getId(), _pin);
    }
    void set(int val) {
        EM_ASM(Module.Wino.byId($0)?.set?.($1, $2), getId(), _pin, val);
    }
protected:
    void buildKeyName(char buf[], uint16_t cbuf) const override {
        snprintf(buf, cbuf, "io/%d", _pin);
    }
};

static IOPin _uno[] = {
   { 0, IO_RX }, { 1, IO_TX }, 
   { 2 }, { 3, IO_PWM }, { 4 }, { 5, IO_PWM }, { 6, IO_PWM }, { 7 },
   { 8 }, { 9, IO_PWM }, { 10, IO_PWM }, { 11, IO_PWM }, { 12 }, { 13 },
   { 14, IO_ANALOG }, { 15, IO_ANALOG }, { 16, IO_ANALOG }, { 17, IO_ANALOG }, 
   { 18, IO_ANALOG|IO_SDA }, { 19, IO_ANALOG|IO_SCL }, 
};

static bool _isValidPin(uint8_t pin) {
    return pin < sizeof(_uno)/sizeof(_uno[0]);
}

void pinMode(uint8_t pin, uint8_t mode) {

}

void digitalWrite(uint8_t pin, uint8_t val) {
    if(_isValidPin(pin)) {
        _uno[pin].set(val ? 1023 : 0);
    }
}

int digitalRead(uint8_t pin) {
    return _isValidPin(pin) && _uno[pin].get() 
        ? HIGH : LOW;
}

int analogRead(uint8_t pin) {
    return _isValidPin(pin) ? _uno[pin].get() : 0;
}
void analogReference(uint8_t mode) {

}
void analogWrite(uint8_t pin, int val) {
    if(_isValidPin(pin)) {
        _uno[pin].set(val);
    }
}

unsigned long millis(void) {
    return (unsigned long)(emscripten_get_now() - start);
}
unsigned long micros(void) {
    return (long)((emscripten_get_now() - start)*1000.);
}
void delay(unsigned long ms) {
    emscripten_sleep(ms);
}
void delayMicroseconds(unsigned int us) {
    emscripten_sleep(us*1000);
}

long random(long max) {
    return random(0, max);
}
long random(long min, long max) {
    return min + rand() % (max-min);
}
void randomSeed(unsigned long seed) {
    srand(seed);
}
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh) {
    return toLow + ((value - fromLow) * (toHigh - toLow)) / (fromHigh - fromLow);
}
