// iClean Robot
// by Kent Altobelli

#include "iClean_bot.h"
#include <Arduino.h>


void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Blink onboard LED for 3 seconds
  chill(250, 3000);
  attachInterrupt(0, left_encoder, RISING);
  attachInterrupt(1, right_encoder, RISING);
}

void loop() {
  // Test things!
  drive_to(0,24,0,50);
  
  // circle?
  int circle_points = 13;
  float radius = 12;
  float centerx = -12;
  float centery = 24;
  for (int i = 1; i <= circle_points; i++)
  {
    float rad = ((float)i*2*PI)/(float)circle_points;
    Serial.println(rad);
    drive_to(centerx + radius*cos(rad), centery + radius*sin(rad), 0, 50);
  }
  
  // Drive back to origin
  drive_to(0.0, 0.0, 0.0, 50);

  // Chill out having accomplished a great thing
  chill(250, -1);  // -1 for infinite chill sesh
}


