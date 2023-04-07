const int HALL_A_BOUT = A0;
const int HALL_B_BOUT = A1;

void setup() {
    Serial.begin(9600);
    pinMode(HALL_A_BOUT, INPUT);
    pinMode(HALL_B_BOUT, INPUT);
}

void loop() {
    Serial.print(analogRead(HALL_A_BOUT));
    Serial.print(" ");
    Serial.println(analogRead(HALL_B_BOUT));
    delay(100);
}
