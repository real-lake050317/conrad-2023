#include <Servo.h>

Servo servo;

const int servoPin = 9;

void setup() {
  servo.attach(servoPin);
}

void loop() {
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(360);
  delay(1000);
}