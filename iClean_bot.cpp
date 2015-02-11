#include "iClean_bot.h"

CMotor Right(6,7,10);  // Initialize Right motor object
CMotor Left(8,9,11);  // Initialize Left motor object


// Interrupt routine for right encoder
void right_encoder() {
  Right.increment_ticks();
}

// Interrupt routine for left encoder
void left_encoder() {
  Left.increment_ticks();
}


// Sit and blink LED on pin 13
void chill(int blink_delay, int chill_time) {
  pinMode(13, OUTPUT);
  unsigned long time = millis();
  while (((int)(millis() - time) < chill_time) || (chill_time < 0)) {
    for (int i = 0; i < 2; i++) {
      digitalWrite(13, i%2);
      delay(blink_delay);
    }
  }
}
