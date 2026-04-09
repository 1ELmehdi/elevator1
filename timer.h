/**
 * @file timer.h
 * @brief Simple non-blocking timer utility for managing durations and intervals.
 */
#ifndef _TIMER_H
#define _TIMER_H

/** @typedef timer_t
 * @brief Type definition for time tracking, based on Arduino's millisecond counter.
 */
typedef unsigned long timer_t;

/**
 * @brief Resets the timer to the current system uptime.
 * * Synchronizes the provided timer variable with the current value of millis().
 * This is typically used to start a new timing sequence.
 * * @param timer A reference to the timer_t variable to be reset.
 */
void timer_reset  (timer_t& timer);

/**
 * @brief Checks if a specific duration has passed since the last reset.
 * Compares the difference between the current time and the timer's start point 
 * against the provided limit. If the limit is reached or exceeded, the timer 
 * is automatically reset to the current time and the function returns true.
 * @param timer A reference to the timer_t variable being monitored.
 * @param limit The duration in milliseconds to check against.
 * @return true If the time elapsed is greater than or equal to the limit.
 * @return false If the duration has not yet been reached.
 */
bool timer_elapsed(timer_t& timer, unsigned long limit);

#endif
