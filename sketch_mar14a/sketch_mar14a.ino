#include <Wire.h> // I2C arduino lib
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Math.h>

#define HMC5883L_ADDR 0b00011110

#define _BV(bit) (1 << (bit))

const int SERVO_ONE = 9; // Servo 1 is the bottom servo
const int SERVO_TWO = 10; // Servo 2 is the top servo
const int HMC5883L_SDA = A4; // SDA pin for magnetometer
const int HMC5883L_SCL = A5; // SCL pin for magnetometer
const int DC_IN1 = 2;
const int DC_IN2 = 3;
const int DC_SPEED = 11;
const int BT_RXD = 6;
const int BT_TXD = 5;

int currentDCSpeed = 0;

int bottomServoDegrees = 0;
int topServoDegrees = 0;

bool isHMC5883LReady = false;
bool isSystemOn = false;

SoftwareSerial HC_60(BT_RXD, BT_TXD);
Servo bottomServo;
Servo topServo;


bool detectHMC5883L () {
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0b1010);
  Wire.endTransmission();
  Wire.requestFrom(HMC5883L_ADDR, 3);

  if (3 == Wire.available()) {
    char a = Wire.read();
    char b = Wire.read();
    char c = Wire.read();

    if (a == 'H' && b == '4' && c == '3') return true;
  }
  return false;
}

void stopDC() {
  digitalWrite(DC_IN1, LOW);
  digitalWrite(DC_IN2, LOW);
}

void runDC() {
  digitalWrite(DC_IN1, HIGH);
  digitalWrite(DC_IN2, LOW);
}

void setDCSpeed(int sp) { // sp is the speed variable which has values in range of 0~255
  analogWrite(DC_SPEED, sp);
}

int topServoAngle(int x, int y, int z){
  return 90 - (int)(180.0*atanf((float)(y)/x)/PI); //range: [-pi/2, pi/2]
}

int bottomServoAngle (int x, int y, int z){
  int tempAngle = 180.0*acosf((float)(z)/sqrt(x*x+y*y+z*z))/PI;
  /*
  if (angle >=0 && angle <=90){
    return 90 - angle;
  }
  else{
    return 
  } */
  return 90 - (int)(180.0*acosf((float)(z)/sqrt(x*x+y*y+z*z))/PI); //range: [0,pi]
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  HC_60.begin(9600);
  TWBR = 78; // 25 kHz
  TWSR |= 1 << (TWPS0);
  pinMode(DC_IN1, OUTPUT);
  pinMode(DC_IN2, OUTPUT);
  pinMode(DC_SPEED, OUTPUT);
  bottomServo.attach(SERVO_ONE);
  topServo.attach(SERVO_TWO);
}

void loop() {
  if (Serial.available()) {
    char val = Serial.read();
    if (val == 'I') { // Turn on the system
      isSystemOn = true;
    } else if (val == 'O') { // Turn off the system
      isSystemOn = false;
      stopDC();
    } else if ((int)val >= 48 && (int)val <= 57) {
      currentDCSpeed = ((int)val - 48) * 28;
    }
  }

  bool isMagnetoReady = detectHMC5883L();
  if (isSystemOn) {
    if (!isHMC5883LReady) {
      if (isMagnetoReady) {
        isHMC5883LReady = true;
        Serial.println("HMC5883L is ready.");
        Wire.beginTransmission(HMC5883L_ADDR);
        Wire.write(0x02); // select register mode
        Wire.write(0x00); // continuous mesurement mode
        Wire.endTransmission();
      } else {
        Serial.println("HMC5883L is not ready.. Trying again");
        delay(2000);
        return;
      }
    }
    else {
      if (!isMagnetoReady) {
        isHMC5883LReady = false;
        Serial.println("HMC5883L connection is lost.. Trying again");
        delay(2000);
        return;
      }
    }

    int mag_X, mag_Y, mag_Z;

    Wire.beginTransmission(HMC5883L_ADDR);
    Wire.write(0x03);
    Wire.endTransmission();

    Wire.requestFrom(HMC5883L_ADDR, 6); // 2 registers per axis; total of 6
    if (6 <= Wire.available()) {
      mag_X = Wire.read() << 8; // X msb
      mag_X |= Wire.read(); // X lsb
      mag_Z = Wire.read() << 8; // Z msb
      mag_Z |= Wire.read(); // Z lsb
      mag_Y = Wire.read() << 8; // Y msb
      mag_Y |= Wire.read(); // Y lsb
    }

    /*
      Serial.print(mag_X);
      Serial.print(",");
      Serial.print(mag_Y);
      Serial.print(",");
      Serial.print(mag_Z);
      Serial.println();
    */

    topServoDegrees = topServoAngle(mag_X, mag_Y, mag_Z);
    bottomServoDegrees = bottomServoAngle(mag_X, mag_Y, mag_Z);

    

    delay(250);
  }
}
