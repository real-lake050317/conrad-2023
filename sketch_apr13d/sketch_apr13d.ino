#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9);
}

void loop() {
  servo.write(30);
  delay(1000);
  servo.write(0);
  delay(1000);
}
