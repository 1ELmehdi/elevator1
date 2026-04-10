/**
 * @file cabin.h
 * @brief Module for controlling elevator cabin movement and door mechanisms.
 */
#ifndef _CABIN_H
#define _CABIN_H

#include "timer.h"

#define PIN_MOTOR_CABIN_A  2
#define PIN_MOTOR_CABIN_B  3
#define PIN_MOTOR_DOORS_A  4
#define PIN_MOTOR_DOORS_B  5

/** @name Cabin Door Directions
 * Constants used for the cabin_door function to define motor direction.
 * @{ */
#define CABIN_DOOR_OPEN  -1 /**< Motor direction to open the doors. */
#define CABIN_DOOR_CLOSE  1 /**< Motor direction to close the doors. */
#define CABIN_DOOR_STOP   0 /**< Stop door motor movement. */
/** @} */

/**
 * @brief Initializes the cabin hardware and starting position.
 * Sets up the pins and drivers for the cabin traction motor and the door 
 * actuation system. Registers the initial floor position.
 * * @param start The index of the floor where the cabin is initially located.
 */
void cabin_init(int start);

/**
 * @brief Retrieves the current floor index.
 * * @return int The index of the floor where the cabin is currently positioned 
 * or was last stationed.
 */
int  cabin_current_floor();

/**
 * @brief Manages cabin movement logic within the main execution loop.
 * This function should be called repeatedly. It determines the required motor 
 * direction to reach the target floor. It monitors the elapsed time using the 
 * provided timer; once the duration exceeds `floor_duration`, it increments or 
 * decrements the current floor count toward the destination.
 * @param start Reference to a timer_t object tracking the time spent moving.
 * @param to_floor The index of the destination floor.
 * @param floor_duration The time (in milliseconds) required to travel between two floors.
 * @return int The updated current floor index.
 */
int  cabin_move(timer_ms& start, int to_floor, unsigned long floor_duration);

/**
 * @brief Stops the cabin traction motor immediately.
 * * Used when reaching a destination or during an emergency stop to halt 
 * vertical movement.
 */
void cabin_stop();

/**
 * @brief Controls the door mechanism at the current floor.
 * * Operates the landing doors based on the provided direction.
 * * @param dir The operation to perform:
 * - #CABIN_DOOR_OPEN (-1)
 * - #CABIN_DOOR_CLOSE (1)
 * - #CABIN_DOOR_STOP (0)
 */
void cabin_door(int dir);

#endif
