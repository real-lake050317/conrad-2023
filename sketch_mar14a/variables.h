#pragma once

#ifndef variables
#define variables

#define HMC5883L_ADDR 0b00011110
#define CONST_PI 3.141592

#define _BV(bit) (1 << (bit))

#define SERVO_ONE 9  // Servo 1 is the bottom servo
#define SERVO_TWO 10    // Servo 2 is the top servo
#define HMC5883L_SDA A4 // SDA pin for magnetometer
#define HMC5883L_SCL A5 // SCL pin for magnetometer
#define DC_IN1 2
#define DC_IN2 3
#define DC_SPEED 11
#define BT_RXD 6
#define BT_TXD 5
#define HALL_A_PIN 7
#define HALL_B_PIN 8

#endif
