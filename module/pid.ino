#include <PID_v1.h>

#define PIN_INPUT A1;
#define PIN_OUTPUT 9

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  // bottom servo angle given
  Setpoint = angle_bottom;
  
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
}
