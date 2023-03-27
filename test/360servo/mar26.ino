#include <Servo.h>

const int SERVO_PIN = 9;

Servo servo;


void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  servo.write(180);
  delay(3000);
  servo.write(0);
  delay(3000);
}
