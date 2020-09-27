#include <NewPing.h>

NewPing sonar_L(TRIG_PIN_L, ECHO_PIN_L, MAX_DIST);
NewPing sonar_R(TRIG_PIN_R, ECHO_PIN_R, MAX_DIST);
NewPing sonar_B(TRIG_PIN_B, ECHO_PIN_B, MAX_DIST);

unsigned int sanitizeReadout(unsigned int val) {
  if(val > 0) { return val; }
  return MAX_DIST;
}

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
    Serial.println(distanceCM_B);

    boolean breached_L = (sanitizeReadout(distanceCM_L) <= MIN_TURNING_DISTANCE);
    boolean breached_R = (sanitizeReadout(distanceCM_R) <= MIN_TURNING_DISTANCE);
    boolean breached_B = (sanitizeReadout(distanceCM_B) <= MIN_TURNING_DISTANCE);

    return breached_L || breached_R || breached_B;
}

// VOLUME LOGIC

boolean isObstacleInRange() {
    unsigned int distanceNow = sonar_L.ping_cm();  

    Serial.print("VCS -");
    Serial.println(distanceNow);

    return sanitzeReadout(distanceNow) < MIN_VOL_RAISE_DISTANCE;
}
