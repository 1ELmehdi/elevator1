#include <wino.h>

#include "timer.h"

void timer_reset(timer_t& timer) { 
  timer = millis();
}

bool timer_elapsed(timer_t& timer, unsigned long limit) {
  if(millis()-timer < limit) {
    return false;
  }
  timer_reset(timer);
  return true;
}