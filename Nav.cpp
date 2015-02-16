#include "Nav.h"
#include "iClean_bot.h"

extern CMotor Right;
extern CMotor Left;

// Initialize position data structure
pos_data pos = {};

// Initialize structure values
nav_control nav = { 
  60,  // P_coef
  0,   // I_coef
  40,   // D_coef
};



// Drive to specified coordinate location
void drive_to (float x_dest, float y_dest, float ang_dest, int throttle) {
  // Find error between current heading and desired heading
  float ang_error = atan2(pos.x-x_dest, pos.y-y_dest) - pos.ang - PI;
  float last_ang_error;

  // Calculate desired heading until within 1/2" of desired position
  while(abs(pos.x - x_dest) > .5 || abs(pos.y - y_dest) > .5) {
    last_ang_error = ang_error;
    ang_error = atan2(pos.x-x_dest, pos.y-y_dest) - pos.ang - PI;
    while (ang_error >= PI || ang_error < -PI) {
      if (ang_error >= PI)
        ang_error -= 2*PI;
      else if (ang_error < -1*PI)
        ang_error += 2*PI;
    }

    // Compute control response to achieve desired heading
    int des_turn = (int)((nav.P_coef * ang_error)
      + (nav.D_coef * (last_ang_error - ang_error)));

    // Disallow reverse turning of the wheels (TEMP hopefully)
    if (des_turn < -1*throttle)
      des_turn = -1*throttle;
    else if (des_turn > throttle)
      des_turn = throttle;

    // Send drive command
    drive(throttle, des_turn);
    delay(LOOP_TIME);
  }
  
  // Stop at destination
  drive(0,0);
  drive(0,0);
  drive(0,0);
}



// Calculate commands to send to motor controller
void drive(int go_val, int turn_val) {
  // Send desired values to the control system
  Right.control_motor(go_val - turn_val);
  Left.control_motor(go_val + turn_val);
  update_pos();
  Serial.print(pos.x);
  Serial.print("  ");
  Serial.print(pos.y);
  Serial.print("  ");
  Serial.println(pos.ang);
}



// Dead recon to update current position
void update_pos() {
  // Calculate distance and angle change from last position
  float mag = TICK_DIST*((float)(Right.get_last_ticks() + Left.get_last_ticks())/2.0);
  float theta = THETA_FACTOR*((float)(Left.get_last_ticks() - Right.get_last_ticks())/2.0);

  // Add angular change to current estimate
  pos.ang += theta;
  if (pos.ang < 0)
    pos.ang += 2*PI;
  else if (pos.ang > 2*PI)
    pos.ang -= 2*PI;

  // Add position change to current estimate
  pos.x += mag*sin(pos.ang);
  pos.y += mag*cos(pos.ang);
}
