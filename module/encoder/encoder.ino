const int HALL_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(HALL_A_BOUT));
  delay(100);
}
