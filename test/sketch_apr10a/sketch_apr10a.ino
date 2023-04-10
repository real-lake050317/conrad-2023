const int motor_pin_one = 4;
const int motor_pin_two = 5;

void setup() {
  Serial.begin(9600);
  pinMode(motor_pin_one, OUTPUT);
  pinMode(motor_pin_two, OUTPUT);
}

void loop() {
  digitalWrite(motor_pin_one, HIGH);
  digitalWrite(motor_pin_two, LOW);
  delay(1000);
}
