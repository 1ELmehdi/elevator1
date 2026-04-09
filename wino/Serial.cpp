#include "Serial.h"

#include <emscripten/emscripten.h>

SerialType Serial;

void SerialType::begin(int baud) {
    enabled = true;    
}

void SerialType::end() {
    enabled = false;
}

template<typename T>
void log(bool enabled, T val) {
    if(enabled) EM_ASM(console.log("Serial : " + $0), val);
}

void SerialType::println(uint8_t  val) const { log(enabled, val); }
void SerialType::println(uint16_t val) const { log(enabled, val); }
void SerialType::println(uint32_t val) const { log(enabled, val); }
void SerialType::println(int8_t   val) const { log(enabled, val); }
void SerialType::println(int16_t  val) const { log(enabled, val); }
void SerialType::println(int32_t  val) const { log(enabled, val); }

template<>
void log(bool enabled, const char* val) {
    if(enabled) EM_ASM(console.log("Serial : " + UTF8ToString($0)), val);
}

void SerialType::println(const char *msg) const { log(enabled, msg); }
