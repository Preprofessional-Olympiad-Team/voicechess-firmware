//It doesn't work correctly: I'll do something with it at TOI

#include <Servo.h>
#include <Stepper.h>
Servo servo_check;
int buttonPin;
void setup() {
  servo_check.attach(7);
  servo_check.write(0);
  buttonPin = 11;
pinMode(buttonPin, INPUT);
}

void loop(){
  servo_check.write(0);
  if (digitalRead(buttonPin)==HIGH)
  {for (int i = 0; i<8; i++)
  {delay(3000);
  servo_check.write(servo_check.read()+ 180/8);
  }
  }
  else
  {
    delay (1000);
servo_check.write(180);
delay (1000);
  }
}
