#include <wino.h>

#include "cabin.h"

static int _current_floor;

static void motor(int pinA, int pinB, int dir); 
static int  motor_dir(int to_floor);

void cabin_init(int start) {
  pinMode(PIN_MOTOR_CABIN_A, OUTPUT);
  pinMode(PIN_MOTOR_CABIN_B, OUTPUT);
  pinMode(PIN_MOTOR_DOORS_A, OUTPUT);
  pinMode(PIN_MOTOR_DOORS_A, OUTPUT);
  _current_floor = start;
}

int cabin_current_floor() {
  return _current_floor;
}

void cabin_stop() {
  motor(PIN_MOTOR_DOORS_A, PIN_MOTOR_DOORS_B, 0);
}

void cabin_door(int dir) {
  motor(PIN_MOTOR_DOORS_A, PIN_MOTOR_DOORS_B, dir);
}

int cabin_move(timer_ms& start, int to_floor, unsigned long duration) {
  if(to_floor != _current_floor) {
    auto dir = motor_dir(to_floor);

    if(timer_elapsed(start, duration)) {
      _current_floor += dir;
    }
  }
  motor(PIN_MOTOR_CABIN_A, PIN_MOTOR_CABIN_B, motor_dir(to_floor));
  return _current_floor;
}

/**
 * @brief Computes the vertical trajectory required to reach a target.
 * Compares the internal cabin state with the requested destination to determine 
 * the necessary movement vector.
 * @param to_floor The index of the target floor.
 * @return int The movement orientation:
 * - 1: Ascending (target is above).
 * - -1: Descending (target is below).
 * - 0: Stationary (target reached).
 */
int motor_dir(int to_floor) {
  // TODO
  return 0;
}

/**
 * @brief Controls the physical H-bridge hardware interface.
 * Translates abstract direction commands into logic levels for a dual-pin motor 
 * driver. This function handles the electrical switching required to change 
 * motor polarity or bring the cabin to a complete halt.
 * @param pinA The GPIO pin connected to the first input of the H-bridge.
 * @param pinB The GPIO pin connected to the second input of the H-bridge.
 * @param dir The desired rotation polarity:
 * - Positive value: Activates forward/upward rotation.
 * - Negative value: Activates reverse/downward rotation.
 * - Zero: Disables both outputs to brake/stop the motor.
 */
void motor(int pinA, int pinB, int dir) {
  // TODO
} 
