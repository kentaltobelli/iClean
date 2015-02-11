#ifndef _NAV_H
#define _NAV_H

#include <Arduino.h>


// iClean position data
struct pos_data {
  float x;
  float y;
  float ang;
};

// Navigation control system coefficients
struct nav_control {
  float P_coef;
  float I_coef;
  float D_coef;
};

// Navigation dedicated functions
void drive(int go_val, int turn_val);  // Generate motor commands given linear and rotational values
void update_pos();  // Dead recon from last data gathered
void drive_to (float x_dest, float y_dest, float ang_dest, int throttle);  // Navigates to desired location

#endif  // #define _NAV_H
