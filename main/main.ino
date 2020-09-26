
// FEATURE ACTIVATION

#define FEATURES_dynamicAcoustics true // mp3 player dynamic volume
#define FEATURES_motorDrives true // motor driving

// TWEAKS

#define MIN_VOL_RAISE_DISTANCE 100 // min distance before turning up volume
#define PEAK_VOLUME_PRESENCE 15000 // milliseconds peak volume is garuanteed to be held
#define MAX_DIST 400 // max dist measured

#define MAX_DRIVE_SPEED 400 // max drive speed
#define MIN_TURNING_DISTANCE 30 // min distance before turning driving direction
#define PRE_TURN_PAUSE 500 // millisecond to wait before rotating
#define POST_TURN_PAUSE 500 // millisecond to wait after rotating
#define TURN_TIME_MIN 400 // minimum millisecond to rotate
#define TURN_TIME_MAX 2500 // maximum millisecond to rotate

// AUDIO PINS

#define ARDUINO_RX_FROM_MP3 5
#define ARDUINO_TX_TO_MP3 6

// RANGE PINS

#define TRIG_PIN_L A0
#define ECHO_PIN_L A1
#define TRIG_PIN_R A2
#define ECHO_PIN_R A3
#define TRIG_PIN_B A4
#define ECHO_PIN_B A5

#define SOUND_DECREASE_PIN 12
#define SOUND_INCREASE_PIN 13

// ARDUINO

void setup()
{
  Serial.begin(9600);

  if(FEATURES_dynamicAcoustics) {
    volumeSetup();
  }

  if(FEATURES_motorDrives) {
    motorSetup();
  }
}

void loop()
{
  if(FEATURES_dynamicAcoustics) {
    runVolumeChange( isGateBreached() );
  }

  if(FEATURES_motorDrives) {
    doDriveCheck( obstacleDetected() );
  }
}
