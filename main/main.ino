#include <Arduino.h>

void setup()
{
  Serial.begin(9600);

  // comment out to deactivate mp3 player
  volumeSetup();

  // comment out to deactivate motors
  // motorSetup();
}

// control motors based on distance measures
void checkDrive()
{
  if (shouldTurn())
  {
    moveTurn();
  }
  else
  {
    moveForward();
  } 
}

// control volume based on distance measures
void checkVolume() 
{  
  setVolumeChangeDirection( gateBreached() );
  delay(60);
  runVolumeChange();
}

void loop()
{
  delay(60);

  // comment out to deactivate volume changes
  checkVolume();

  // comment out to deactivate driving
  // checkDrive();
}
