// iClean Robot
// by Kent Altobelli

#include "iClean_bot.h"
#include <Arduino.h>


void setup() {
  // Start serial communication
  //Serial.begin(115200);

  // Blink onboard LED for 3 seconds
  chill(250, 3000);
  attachInterrupt(0, left_encoder, RISING);
  attachInterrupt(1, right_encoder, RISING);
}

void loop() {
  // Test things!
  drive_to(0,24,0,60);
  drive_to(24,24,0,60);
  drive_to(24,0,0,60);

  // Drive back to origin
  drive_to(0.0, 0.0, 0.0, 50);

  // Chill out having accomplished a great thing
  chill(250, -1);  // -1 for infinite chill sesh
}

