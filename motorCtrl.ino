#include <Arduino.h>
#include <AFMotor.h>

// ADJUSTABLES

#define MAX_SPEED 400 // Max speed the motors will go

// MOTORS

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

boolean goesForward = false;
boolean lastTurnM1 = false;
int speedSet = 0;

void motorSetup()

{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void moveStop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  goesForward = false;
}

void accelerate()
{
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
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

void moveTurn()
{
  moveStop();

  delay(500);

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

  // RANDOM TURN TIME
  delay(random(100, 2500));

  moveStop();

  delay(500);
}
