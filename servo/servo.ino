const int MOTOR_PWM = 13;
const int MOTOR_IN1 = 7;
const int MOTOR_IN2 = 12;
const int UNDER_PWM = 10;
const int UNDER_IN1 = 6;
const int UNDER_IN2 = 11;
const int SERVO_VCC = 9;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(UNDER_PWM, OUTPUT);
  pinMode(UNDER_IN1, OUTPUT);
  pinMode(UNDER_IN2, OUTPUT);
}

void loop() {
  analogWrite(MOTOR_PWM, 51);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(UNDER_PWM, 255);
  digitalWrite(UNDER_IN1, LOW);
  digitalWrite(UNDER_IN2, HIGH);
  delay(1000);  
}
