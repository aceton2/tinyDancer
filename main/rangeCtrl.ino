#include <NewPing.h>

// ADJUSTABLES

#define MIN_DISTANCE 30 // MIN DISTANCE BEFORE TURNING
#define GATE_DISTANCE 100 // GATE DISTANCE FOR RAISING VOLUME
#define MAX_DIST 400 // MAX DIST MEASURED

// PINS

#define TRIG_PIN_L A0
#define ECHO_PIN_L A1
#define TRIG_PIN_R A2
#define ECHO_PIN_R A3
#define TRIG_PIN_B A4
#define ECHO_PIN_B A5

#define SOUND_DECREASE_PIN 12
#define SOUND_INCREASE_PIN 13

NewPing sonar_L(TRIG_PIN_L, ECHO_PIN_L, MAX_DIST);
NewPing sonar_R(TRIG_PIN_R, ECHO_PIN_R, MAX_DIST);
NewPing sonar_B(TRIG_PIN_B, ECHO_PIN_B, MAX_DIST);

boolean shouldTurn()
{
    unsigned int distanceCM_L = sonar_L.ping_cm();
    unsigned int distanceCM_R = sonar_R.ping_cm();
    unsigned int distanceCM_B = sonar_B.ping_cm();

    Serial.print(distanceCM_L);
    Serial.print("-");
    Serial.print(distanceCM_R);
    Serial.print("-");
    Serial.print(distanceCM_B);
    Serial.print("\n");

    boolean breached_L = (distanceCM_L > 0 && distanceCM_L <= MIN_DISTANCE);
    boolean breached_R = (distanceCM_R > 0 && distanceCM_R <= MIN_DISTANCE);
    boolean breached_B = (distanceCM_B > 0 && distanceCM_B <= MIN_DISTANCE);

    return breached_L || breached_R || breached_B;
}

// GATE LOGIC

boolean wasOutOfRange = true;
unsigned int distanceNow;

void setLatestDistance() {
    distanceNow = sonar_L.ping_cm();  

    if (distanceNow == 0) {
        distanceNow = GATE_DISTANCE + 1000;
    }

    Serial.print("D ");
    Serial.println(distanceNow);
}

// enter is 1, exit -1, no change 0
int gateBreached() {

    setLatestDistance();
    
    int output = 0;
    boolean nowOutOfRange = distanceNow > GATE_DISTANCE;

    if(nowOutOfRange) {
        output = -1;
        Serial.println(output);
    } else if (wasOutOfRange) {
        output = 1;
        Serial.println(output);
    }

    wasOutOfRange = nowOutOfRange;

    return output;
}
