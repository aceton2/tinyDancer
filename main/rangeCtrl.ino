#include <NewPing.h>

NewPing sonar_L(TRIG_PIN_L, ECHO_PIN_L, MAX_DIST);
NewPing sonar_R(TRIG_PIN_R, ECHO_PIN_R, MAX_DIST);
NewPing sonar_B(TRIG_PIN_B, ECHO_PIN_B, MAX_DIST);

// DRIVE LOGIC

bool obstacleDetected()
{
    unsigned int distanceCM_L = sonar_L.ping_cm();
    unsigned int distanceCM_R = sonar_R.ping_cm();
    unsigned int distanceCM_B = sonar_B.ping_cm();

    Serial.print("DRS -");
    Serial.print(distanceCM_L);
    Serial.print("-");
    Serial.print(distanceCM_R);
    Serial.print("-");
    Serial.print(distanceCM_B);
    Serial.print("\n");

    boolean breached_L = (distanceCM_L > 0 && distanceCM_L <= MIN_TURNING_DISTANCE);
    boolean breached_R = (distanceCM_R > 0 && distanceCM_R <= MIN_TURNING_DISTANCE);
    boolean breached_B = (distanceCM_B > 0 && distanceCM_B <= MIN_TURNING_DISTANCE);

    return breached_L || breached_R || breached_B;
}

// VOLUME LOGIC

boolean wasOutOfRange = true;

boolean isObstacleOutOfRange() {
    unsigned int distanceNow = sonar_L.ping_cm();  

    if (distanceNow == 0) {
        distanceNow = MIN_VOL_RAISE_DISTANCE + 1000;
    }
    
    Serial.print("VCS -");
    Serial.println(distanceNow);

    return distanceNow > MIN_VOL_RAISE_DISTANCE;
}

// enter is 1, exit -1, no change 0
int isGateBreached() {

    int output = 0;
    boolean nowOutOfRange = isObstacleOutOfRange() ;

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
