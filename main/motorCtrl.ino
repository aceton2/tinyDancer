#include <AFMotor.h>
#include "avdweb_VirtualDelay.h"

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

VirtualDelay delayStartRotate, delayStopRotate, delayContinueForward;

int turningStep = 0; // 0 no turning, 1 preRotateStop, 2 rotating, 3 postRotateStop
boolean goesForward = false;
boolean lastTurnM1 = false;
int speedSet = 0;

// SETUP

void motorSetup()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

// BASIC MANEUVERS

void moveStop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  goesForward = false;
}

void accelerate()
{
  Serial.println("accelerate");

  // slowly bring the speed up to avoid loading down the batteries too quickly
  for (speedSet = 0; speedSet < MAX_DRIVE_SPEED; speedSet += 2) 
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    // delay(5);
  }
}

void moveForward()
{
  if (!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    accelerate();
  }
}

void rotate() {
    if (!lastTurnM1)
  {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    lastTurnM1 = true;
  }
  else
  {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    lastTurnM1 = false;
  }

  accelerate();
}


// DRIVING LOGIC

bool isTurning() {
  return turningStep > 0;
}

void doDriveCheck(boolean isObstacleDetected)
{
  if (isObstacleDetected || isTurning()) {
    doTurnChecks();
  }
  else {
    moveForward();
  } 
}

void doTurnChecks() {
  
  if(turningStep == 0) {
    moveStop();
    delayStartRotate.start(PRE_TURN_PAUSE);
    turningStep = 1;
  }

  if((turningStep == 1) && delayStartRotate.elapsed()) {
    rotate();
    delayStopRotate.start(random(TURN_TIME_MIN, TURN_TIME_MAX));
    turningStep = 2;
  }

  if((turningStep == 2) && delayStopRotate.elapsed()) {
    moveStop();
    delayContinueForward.start(PRE_TURN_PAUSE);
    turningStep = 3;
  }

  if((turningStep == 3) && delayContinueForward.elapsed()) {
    turningStep = 0;
  }
}
