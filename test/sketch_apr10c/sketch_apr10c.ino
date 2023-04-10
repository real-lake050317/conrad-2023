// Define motor driver pins
const int motorIN1Pin = 4;
const int motorIN2Pin = 5;

// Define Hall effect sensor pins
const int hallSensorAPin = 2;
const int hallSensorBPin = 3;

// Define variables for angle calculation
const int numPoles = 6; // number of magnetic poles in the motor
const float degreesPerPole = 360.0 / numPoles; // number of degrees per magnetic pole
volatile long hallSensorCounter = 0; // counter for number of Hall sensor pulses
volatile float currentAngle = 0; // current angle of the motor in degrees

void setup() {
  // Set motor driver pins as output
  pinMode(motorIN1Pin, OUTPUT);
  pinMode(motorIN2Pin, OUTPUT);

  // Set Hall effect sensor pins as input with internal pullup resistors
  pinMode(hallSensorAPin, INPUT_PULLUP);
  pinMode(hallSensorBPin, INPUT_PULLUP);

  // Attach interrupt to Hall effect sensor A pin to count pulses
  attachInterrupt(digitalPinToInterrupt(hallSensorAPin), countHallSensorPulse, RISING);

  // Print header for angle data
  Serial.begin(9600);
  Serial.println("Angle (degrees)");
}

void loop() {
  // Move the motor for a short time
  digitalWrite(motorIN1Pin, HIGH);
  digitalWrite(motorIN2Pin, LOW);
  delay(1000); // change this value

  // Stop the motor and print the current angle
  digitalWrite(motorIN1Pin, LOW);
  digitalWrite(motorIN2Pin, LOW);
  delay(100); // wait for the motor to stop
  Serial.println(currentAngle);
}

void countHallSensorPulse() {
  // Determine the direction of rotation based on the state of Hall sensor B
  bool hallSensorBState = digitalRead(hallSensorBPin);
  float direction = (hallSensorBState == HIGH) ? 1 : -1;

  // Increment the counter and calculate the current angle
  hallSensorCounter++;
  currentAngle = fmod(currentAngle + direction * degreesPerPole / 2, 360);
}
