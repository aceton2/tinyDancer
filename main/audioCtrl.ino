#include <SoftwareSerial.h>
#include "avdweb_VirtualDelay.h"

SoftwareSerial mySerial(ARDUINO_RX_FROM_MP3, ARDUINO_TX_TO_MP3);
static int8_t Send_buf[8] = {0};

// CMDS to control MP3
// https://arduinoplusplus.wordpress.com/2018/07/23/yx5300-serial-mp3-player-catalex-module/

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define SNG_CYCL_PLAY 0x08
#define CMD_VOLUME_UP 0x04
#define CMD_VOLUME_DOWN 0x05

VirtualDelay delayPeak;

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e;               //starting byte
  Send_buf[1] = 0xff;               //version
  Send_buf[2] = 0x06;               //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command;            //
  Send_buf[4] = 0x00;               //0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8); //datah
  Send_buf[6] = (int8_t)(dat);      //datal
  Send_buf[7] = 0xef;               //ending byte
  for (uint8_t i = 0; i < 8; i++)   //
  {
    mySerial.write(Send_buf[i]);
  }
}

void volumeSetup()
{

  mySerial.begin(9600);
  delay(500);                          //Wait chip initialization is complete
  sendCommand(CMD_SEL_DEV, DEV_TF);    //select the TF card
  delay(200);                          //wait for 200ms
  sendCommand(CMD_PLAY_W_VOL, 0X1E01); //play the first song with volume 30 class
  sendCommand(SNG_CYCL_PLAY, 0X01); // play 01 on loop
  Serial.println("audio start complete..");
}

boolean raisingToPeak = false;
boolean increaseVolume = false;
int steps = 0;

void runVolumeChange(bool objectInRange)
{
  manageVolumeChangeDirection(objectInRange);
  
  if (increaseVolume) {
    Serial.println("----- +");
    sendCommand(CMD_VOLUME_UP, 0);
    steps++;
  }
  else {
    Serial.println("----- -");
    sendCommand(CMD_VOLUME_DOWN, 0);
  }

  if (steps > 50 && increaseVolume) {
      delayedPeakReset();
  }
}

void manageVolumeChangeDirection(bool objectInRange) {
  if(objectInRange) {
    raisingToPeak = true;
    increaseVolume = true;
  } else if(!raisingToPeak) {
    increaseVolume = false;
  }
}

void delayedPeakReset() {
  if (!delayPeak.running) {
    Serial.print("////// PEAK START");

    delayPeak.start(PEAK_VOLUME_PRESENCE);
  }

  if (delayPeak.elapsed()) {
    Serial.println("////// PEAK END");

    raisingToPeak = false;
    steps = 0;
  }
}
