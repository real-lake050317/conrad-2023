#define HALL_A_BOUT 2
#define HALL_B_BOUT 3

void setup() {
    Serial.begin(9600);
    pinMode(HALL_A_BOUT, INPUT);
    pinMode(HALL_B_BOUT, INPUT);
}

void loop() {
    Serial.print(digitalRead(HALL_A_BOUT));
    Serial.print(" ");
    Serial.println(digitalRead(HALL_B_BOUT));
    delay(100);
}