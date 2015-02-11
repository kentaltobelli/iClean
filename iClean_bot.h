#ifndef _ICLEAN_H
#define _ICLEAN_H

#include <Arduino.h>
#include "Motor.h"
#include "Nav.h"

// Physical meaurement values
#define WHEEL_CIR 8.05
#define WHEEL_BASE_CIR 2*5.5*3.141592653
#define ENCODER_TICKS 64
// Performance constraint settings
#define SLEW_RATE 75
#define LOOP_TIME 100
// Calculated once to save clock cycles later
#define TICK_DIST WHEEL_CIR/ENCODER_TICKS
#define THETA_FACTOR .0233 //(TICK_DIST/WHEEL_BASE_CIR)*6.2832;



void right_encoder();  // Right encoder interrupt routine
void left_encoder();  // Left encoder interrupt routine
void chill(int blink_delay, int chill_time);  // Sit and blink onboard LED

#endif  // #ifndef _ICLEAN_H
