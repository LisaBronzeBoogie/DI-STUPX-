#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <Servo.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 60

// Since microstepping is set externally, make sure this matches the selected mode
// Set the jumper to middle position when using MICROSTEPS 4, no jumper = MICROSTEPS 1
// 1=full step, 2=half step etc.
#define MICROSTEPS 4

// Driver in CNC shield X
#define DIR_X 5
#define STEP_X 2

// Driver in CNC shield Y
#define DIR_Y 6
#define STEP_Y 3

// Driver in CNC shield Z
#define DIR_Z 7
#define STEP_Z 4

// Define the pin for enable/disable functionality
#define SLEEP 8


int pos = 0;
float speed = 5;
float angle = 0;
int rotations = 3;
int rot = 5;

// Initialize the driver(s)
BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X, SLEEP);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y, SLEEP);

void setup()
{
  // Pass some config to the instances and begin
  stepperX.begin(RPM, MICROSTEPS);
  stepperY.begin(RPM, MICROSTEPS);

  // set speed profile with acceleration
  //stepper.setSpeedProfile(stepper.LINEAR_SPEED, 500, 500);
  
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  stepperX.setEnableActiveState(LOW);
   stepperY.setEnableActiveState(LOW);
}

void loop()
{
  // energize coils
  stepperX.enable();
  stepperY.enable();

for(int i = 0; i< rotations; i++)
{
  stepperX.rotate(350);
  stepperX.rotate(-180);
  stepperY.rotate(360);
  stepperY.rotate(-120);
}

for(int i = 0; i< rot; i++)
{
  stepperX.rotate(180);
  stepperX.rotate(-180);
  stepperY.rotate(290);
  stepperY.rotate(-180);
}
 
  // pause and allow the motor to be moved by hand
  stepperX.disable();
  stepperY.disable();

  delay(10); 
  
}