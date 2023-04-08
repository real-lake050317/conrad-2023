// Define motor driver pins
const int motorDirectionPin = 8;
const int motorPWMPin = 9;

// Define Hall effect sensor pins
const int hallSensorAPin = 2;
const int hallSensorBPin = 3;

// Define variables for motor speed and direction
int motorSpeed = 100; // change this value to adjust motor speed
bool motorDirection = true; // true = clockwise, false = counterclockwise

// Define variables for angle calculation
const int numPoles = 6; // number of magnetic poles in the motor
const float degreesPerPole = 360.0 / numPoles; // number of degrees per magnetic pole
volatile long hallSensorCounter = 0; // counter for number of Hall sensor pulses
volatile float currentAngle = 0; // current angle of the motor in degrees

void setup() {
  // Set motor driver pins as output
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);

  // Set Hall effect sensor pins as input with internal pullup resistors
  pinMode(hallSensorAPin, INPUT_PULLUP);
  pinMode(hallSensorBPin, INPUT_PULLUP);

  // Attach interrupt to Hall effect sensor A pin to count pulses
  attachInterrupt(digitalPinToInterrupt(hallSensorAPin), countHallSensorPulse, RISING);

  // Set motor direction and speed
  setMotorDirection(motorDirection);
  setMotorSpeed(motorSpeed);

  // Print header for angle data
  Serial.begin(9600);
  Serial.println("Angle (degrees)");
}

void loop() {
  // Move the motor for a short time
  delay(1000); // change this value to adjust the duration of motor movement

  // Stop the motor
  setMotorSpeed(0);

  // Print current angle
  Serial.println(currentAngle);

  // Reverse motor direction
  motorDirection = !motorDirection;
  setMotorDirection(motorDirection);

  // Restart motor
  setMotorSpeed(motorSpeed);
}

void setMotorDirection(bool direction) {
  digitalWrite(motorDirectionPin, direction);
}

void setMotorSpeed(int speed) {
  analogWrite(motorPWMPin, speed);
}

void countHallSensorPulse() {
  // Read Hall effect sensor B pin to determine direction of rotation
  if (digitalRead(hallSensorBPin) == HIGH) {
    // counterclockwise rotation
    hallSensorCounter--;
  } else {
    // clockwise rotation
    hallSensorCounter++;
  }
  // Update current angle based on number of pulses
  currentAngle = hallSensorCounter * degreesPerPole;
}
