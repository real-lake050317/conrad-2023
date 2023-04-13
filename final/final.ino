#include <Servo.h>

const int MOTOR_PWM = 11;
const int MOTOR_IN1 = 7;
const int MOTOR_IN2 = 13;
const int UNDER_PWM = 10;
const int UNDER_IN1 = 6;
const int UNDER_IN2 = 12;
const int SERVO_VCC = 9;

bool flag = false;

Servo servo;

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(UNDER_PWM, OUTPUT);
  pinMode(UNDER_IN1, OUTPUT);
  pinMode(UNDER_IN2, OUTPUT);
  servo.attach(SERVO_VCC);
}

void loop()
{
  /*
    analogWrite(MOTOR_PWM, 255);
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(UNDER_PWM, 255);
    digitalWrite(UNDER_IN1, LOW);
    digitalWrite(UNDER_IN2, HIGH);
    delay(1000);
    analogWrite(MOTOR_PWM, 255);
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(UNDER_PWM, 255);
    digitalWrite(UNDER_IN1, HIGH);
    digitalWrite(UNDER_IN2, LOW);
    delay(1000);
  */
  /*
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(45);
    delay(1000);
  */
  analogWrite(MOTOR_PWM, 255);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);

  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(1500);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(1700);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(1200);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(800);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(700);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, LOW);
  delay(800);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, LOW);
  delay(2800);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(1300);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(1400);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(800);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(1700);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, LOW);
  delay(3900);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(300);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(900);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, HIGH);
  digitalWrite(UNDER_IN2, LOW);
  delay(1200);
}
