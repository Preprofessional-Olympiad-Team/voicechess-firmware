#include <Stepper.h>
Stepper stepper_check = Stepper(64, 3,4,5,6);
void setup() {
  stepper_check.setSpeed(200);
}

void loop() {
  stepper_check.step(100);
}
