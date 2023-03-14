#include <Wire.h> // I2C arduino lib

#define HMC5883L_ADDR 0b0001110

#define _BV(bit) (1 << (bit))

const int SERVO_ONE = 9; // Servo 1 is the bottom servo
const int SERVO_TWO = 10; // Servo 2 is the top servo
const int HMC5883L_SDA = A4; // SDA pin for magnetometer
const int HMC5883L_SCL = A5; // SCL pin for magnetometer
const int DC_IN1 = 2;
const int DC_IN2 = 3;

bool isHMC5883LReady = false;

bool detectHMC5883L () {
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0b1010);
  Wire.endTransmission();
  Wire.requestFrom(HMC5883L_ADDR, 3);

  if (3 == Wire.available()) {
    char a = Wire.read();
    char b = Wire.read();
    char c = Wire.read();

    if (a == 'H' && b == '4' && c == '3') {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  TWBR = 78; // 25 kHz
  TWSR |= 1 << (TWPS0);
}

void loop() {
  bool isMagnetoReady = detectHMC5883L();

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

  Serial.print(mag_X);
  Serial.print(",");
  Serial.print(mag_Y);
  Serial.print(",");
  Serial.print(mag_Z);
  Serial.println();

  delay(250);
}
