const int pin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(analogRead(pin));
  delay(300);
}
