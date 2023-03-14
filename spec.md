# Specifications

## To-do
### Control Servo 
1. Control two servo motors.
  + Use digital pin 9, 10.
  + Use PWM
2. Receive x, y, z data from H5883L sensor module. Use analog pin 4 and 5.
3. Equations are:
  + $\theta_{bottom}=arctan(\frac{y}{x})$
  + $\theta_{top}=arccos(\frac{z}{\sqrt{x^2+y^2+z^2}})$

### Control DC motor RPM
1. Use L293N DC motor controller.
2. Receive rotation speed using bluetooth connection.
3. Use digital pin 2 and 3 for IN1, IN2, respectively.

### Bluetooth communication
1. Make bluetooth connection with mobile phone.
2. Receive serial data.
3. Use HC-06 bluetooth module.
4. Get RPM control, on, off commands.
