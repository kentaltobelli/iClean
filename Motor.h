#ifndef _MOTOR_H
#define _MOTOR_H

#include <Arduino.h>

/*
 TB6612FNG Dual Channel H-bridge Driver
 
 INA - DPins 6&7
 INB - DPins 8&9
 PWMA - DPin 10
 PWMB - DPIN 11

-----+-----+-------------
 IN1 | IN2 |    MODE
=====+=====+=============
  H  |  H  | Short Brake
-----+-----+-------------
  L  |  H  |    CCW
-----+-----+-------------
  H  |  L  |     CW
-----+-----+-------------
  L  |  L  |    Stop
-----+-----+-------------
*/


class CMotor {
private:
  // Motor output pins
  struct motor_outputs {
    int Pwm;
    int IN1;
    int IN2;
  } pins;

  // Control system values
  struct control_system {
    float speed_coef;
    float P_coef;
    float I_coef;
    float D_coef;
    int ticks;  // Encoder ticks
    int last_ticks;
    float drive;  // Desired ticks/sec
    //float last_drive;
    float error;  // Error -> control response
    float last_error;
    float accum_error;
    int ctrl_pwm;  // Calculated control response
    int last_ctrl_pwm;
  } control;
  
  void update_motor(void);  // Send control response to motor

public:
  // Member Functions
  CMotor();
  CMotor(int IN1, int IN2, int Pwm);  // Assign pin values for motor
  ~CMotor();
  void increment_ticks()  { control.ticks++; }
  int get_last_ticks()  { return(control.last_ticks); }
  void control_motor(int desir_spd);  // Calculate control response
  void halt();
};

#endif  // #ifndef _MOTOR_H



