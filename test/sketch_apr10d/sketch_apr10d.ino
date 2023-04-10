// Motor pins
const int motor_pin_one = 4;
const int motor_pin_two = 5;

// Encoder pins
const int hall_a_pin = 2;
const int hall_b_pin = 3;

// Encoder variables
volatile long encoder_count = 0;
volatile bool hall_a_state = false;
volatile bool hall_b_state = false;

// Set up the encoder interrupts
void hall_a_isr() {
  hall_a_state = digitalRead(hall_a_pin);
  hall_b_state = digitalRead(hall_b_pin);
  if (hall_a_state == hall_b_state) {
    encoder_count++;
  } else {
    encoder_count--;
  }
}

void hall_b_isr() {
  hall_a_state = digitalRead(hall_a_pin);
  hall_b_state = digitalRead(hall_b_pin);
  if (hall_a_state == hall_b_state) {
    encoder_count--;
  } else {
    encoder_count++;
  }
}

void setup() {
  // Set up the motor pins
  pinMode(motor_pin_one, OUTPUT);
  pinMode(motor_pin_two, OUTPUT);

  // Set up the encoder pins
  pinMode(hall_a_pin, INPUT_PULLUP);
  pinMode(hall_b_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hall_a_pin), hall_a_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hall_b_pin), hall_b_isr, CHANGE);
}

void loop() {
  // Rotate the motor 360 degrees
  for (int i = 0; i < 360; i++) {
    // Wait for the motor to rotate
    delay(10);
    
    // Print the encoder count
    Serial.println(encoder_count);
  }
  
  // Stop the motor
}
