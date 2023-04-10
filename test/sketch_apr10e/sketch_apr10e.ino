#include "variables.h"
#include <Servo.h>

void setup() {
  Serial.begin(9600);
  pinMode(TOP_MOTOR_SPEED, OUTPUT);
  pinMode(TOP_MOTOR_IN1, OUTPUT);
  pinMode(TOP_MOTOR_IN2, OUTPUT);

  pinMode(BOTTOM_MOTOR_SPEED, OUTPUT);
  pinMode(BOTTOM_MOTOR_IN1, OUTPUT);
  pinMode(BOTTOM_MOTOR_IN2, OUTPUT);

  pinMode(SERVO_VCC, OUTPUT);
}

void loop() {
  digitalWrite(BOTTOM_MOTOR_IN1, HIGH);
  digitalWrite(BOTTOM_MOTOR_IN2, LOW);
  analogWrite(BOTTOM_MOTOR_SPEED, 255);
  delay(1000);
  digitalWrite(BOTTOM_MOTOR_IN1, LOW);
  digitalWrite(BOTTOM_MOTOR_IN2, HIGH);
  delay(1000);
}
