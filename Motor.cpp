#include "Motor.h"
#include "iClean_bot.h"


// Default Constructor
CMotor::CMotor() {
}

// Custom Constructor
CMotor::CMotor(int IN1, int IN2, int Pwm) {
  // Initialize control system structure components
  control.P_coef = 20;
  control.I_coef = 0;
  control.D_coef = 0;
  control.drive = 0;
  control.ticks = 0;
  control.ctrl_pwm = 0;

  // Initialize motor output structure
  pins.IN1 = IN1;
  pins.IN2 = IN2;
  pins.Pwm = Pwm;
  pinMode(pins.IN1, OUTPUT);
  pinMode(pins.IN2, OUTPUT);
  
  // Update motor with new values (should be all stopped)
  update_motor();
}

// Destructor
CMotor::~CMotor() {
}


// Control system for motor speed
void CMotor::control_motor(int desir_spd) {
  // Shift and enter new data
  //last_drive = drive;
  control.drive = (float)desir_spd;

  // Find error
  control.last_error = control.error;
  control.error = ((LOOP_TIME*control.drive)/1000) - (float)control.ticks;
  control.last_ticks = control.ticks;
  control.ticks = 0;

  // Calculate response
  control.last_ctrl_pwm = control.ctrl_pwm;
  control.ctrl_pwm = (int)((1.54*control.drive) + (control.P_coef * control.error)); // add D and I later

    // Limit response range
  if (control.ctrl_pwm < -255)
    control.ctrl_pwm = -255;
  else if (control.ctrl_pwm > 255)
    control.ctrl_pwm = 255;

  // Limit motor slew rate
  if (control.ctrl_pwm - control.last_ctrl_pwm > SLEW_RATE)
    control.ctrl_pwm = control.last_ctrl_pwm + SLEW_RATE;
  else if (control.ctrl_pwm - control.last_ctrl_pwm < -1*SLEW_RATE)
    control.ctrl_pwm = control.last_ctrl_pwm - SLEW_RATE;

  update_motor();
}



// Send bitwise and PWM commands to motor driver
void CMotor::update_motor() {
  // Forward
  if (control.ctrl_pwm < 0 && control.ctrl_pwm >= -255) {
    control.ctrl_pwm *= -1;
    digitalWrite(pins.IN1, HIGH);
    digitalWrite(pins.IN2, LOW);
    analogWrite(pins.Pwm, control.ctrl_pwm);
  }
  // Backward
  else if (control.ctrl_pwm >= 0 && control.ctrl_pwm <= 255) {
    digitalWrite(pins.IN1, LOW);
    digitalWrite(pins.IN2, HIGH);
    analogWrite(pins.Pwm, control.ctrl_pwm);
  }
  // Anything else puts on brake (should never happen)
  else {
    digitalWrite(pins.IN1, HIGH);
    digitalWrite(pins.IN2, HIGH);
    analogWrite(pins.Pwm, control.ctrl_pwm);
  }
}
