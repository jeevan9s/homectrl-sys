// shades module 
// stepper motor control

#include "shading.h"
#include "wifi/wifi_mqtt.ino"
#include "wifi/wifi_mqtt.h"

// timing vars 
unsigned long lastPublishMs = 0;
unsigned long lastMoveStartMs = 0;

// states n actions (position vars)
bool motorRunning = false;
int currentPositionSteps = 0;  
int targetPositionSteps = 0;

unsigned long shadingGetLastMoveMs() { return lastMoveStartMs; }
bool shadingMotorIsRunning() { return motorRunning; }

void publishStatus(const char* status) {
    mqttPublish(SHADE_TOPIC_STATUS, status);
    Serial.println(status);
}

void publishShadeState() {
    uint8_t positionPct = shadingGetPositionPct();
    bool isOpen = positionPct > 50; 
    
    char buf[32];
    snprintf(buf, sizeof(buf), "%d,%d", isOpen ? 1 : 0, positionPct);
    mqttPublish(SHADE_TOPIC_STATE, buf);
    
    Serial.print("shade state: "); Serial.print(isOpen ? "open" : "closed"); 
    Serial.print(" at "); Serial.print(positionPct); Serial.println("%");
}

void setupShading() {
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  currentPositionSteps = 0;
  targetPositionSteps = 0;

  setupWiFi();
  setupMQTT();

  // binary 
  mqttSubscribe(SHADE_TOPIC_CMD, [](String msg){
      if (msg == "1") {
          openBlinds();  
      } else if (msg == "0") {
          closeBlinds(); 
      }
  });

   // pct
   mqttSubscribe(SHADE_TOPIC_POSITION, [](String msg){
      uint8_t targetPct = msg.toInt();
      if (targetPct >= 0 && targetPct <= 100) {
          moveToPositionPct(targetPct);
      } else {
          publishStatus("invalid position - use 0-100");
      }
  });

    mqttSubscribe(SHADE_TOPIC_TELEM_REQ, [](String msg){
      if (msg == "state") {
          publishShadeState(); 
      }
  });

  
  mqttSubscribe(SHADE_TOPIC_CALIBRATE, [](String msg){
      if (msg == "close" || msg == "reset") calibrateHandler();
  });

  addAlexaBlinds();

  publishStatus("shade control ready");
  publishShadeState(); 
}

// actuation 
void moveToPositionPct(uint8_t targetPct) {
    targetPct = constrain(targetPct, 0, 100);
    targetPositionSteps = map(targetPct, 0, 100, 0, MAX_POSITION_STEPS);
    
    if (abs(targetPositionSteps - currentPositionSteps) > POS_TOLERANCE) {
        motorRunning = true;
        lastMoveStartMs = millis();
        
        char buf[64];
        snprintf(buf, sizeof(buf), "moving to %d%% (%d steps)", targetPct, targetPositionSteps);
        publishStatus(buf);
    } else {
        char buf[32];
        snprintf(buf, sizeof(buf), "already at %d%%", targetPct);
        publishStatus(buf);
    }
}

void openBlinds() {
    publishStatus("opening blinds");
    moveToPositionPct(100);
}

void closeBlinds() {
    publishStatus("closing blinds");
    moveToPositionPct(0);
}

void stopMotorHandler() {
    if (motorRunning) {
        motorRunning = false;
        targetPositionSteps = currentPositionSteps;
        publishStatus("motor stopped");
        publishShadeState();
    }
}

void calibrateHandler() {
    publishStatus("calibrating - closing fully");
    
    digitalWrite(DIR_PIN, LOW);
    
    for (int i = 0; i < MAX_POSITION_STEPS * 1.2; i++) { 
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_SPEED_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_SPEED_DELAY);
    }
    
    currentPositionSteps = 0;
    targetPositionSteps = 0;
    motorRunning = false;
    publishStatus("calibration complete - position reset to 0% (closed)");
    publishShadeState();
}

uint8_t shadingGetPositionPct() {
    int pct = map(currentPositionSteps, 0, MAX_POSITION_STEPS, 0, 100);
    return constrain(pct, 0, 100);
}

void publishPosition() {
    uint8_t positionPct = shadingGetPositionPct();
    
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", positionPct);
    
    Serial.print("shade position: "); Serial.print(positionPct); Serial.println("%");
    mqttPublish(SHADE_TOPIC_POSITION, String(positionPct).c_str());
}

void handleMotorMovement() {
    if (!motorRunning) return;
    
    
    if (millis() - lastMoveStartMs > SHADE_TIMEOUT_MS) {
        publishStatus("motor timeout - stopping for safety");
        stopMotorHandler();
        return;
    }
    
    int stepsToMove = targetPositionSteps - currentPositionSteps;
    
    if (abs(stepsToMove) > POS_TOLERANCE) {
        
        digitalWrite(DIR_PIN, (stepsToMove > 0) ? HIGH : LOW);
        
        
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_SPEED_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_SPEED_DELAY);
        
        
        currentPositionSteps += (stepsToMove > 0) ? 1 : -1;
        currentPositionSteps = constrain(currentPositionSteps, 0, MAX_POSITION_STEPS);
    } else {
        currentPositionSteps = targetPositionSteps;
        stopMotorHandler();
        
        char buf[32];
        snprintf(buf, sizeof(buf), "reached %d%%", shadingGetPositionPct());
        publishStatus(buf);
    }
}

void addAlexaBlinds() {
    sinricAddCustomDevice(SWITCH_ID_MOTOR,
        [](const String& deviceId, const String& action, const String& value, String& response) -> bool {
            if (action == "getPosition") {
                uint8_t pct = shadingGetPositionPct();
                response = String(pct) + " percent open";
                Serial.print("ALEXA blind position: ");
                Serial.println(response);
                return true;
            } 
            else if (action == "setPosition") {
                uint8_t targetPct = value.toInt();
                if (targetPct >= 0 && targetPct <= 100) {
                    moveToPositionPct(targetPct);
                    response = "setting blinds to " + String(targetPct) + " percent";
                    return true;
                } else {
                    response = "invalid position - use 0 to 100 percent";
                    return false;
                }
            }
            else if (action == "open") {
                openBlinds();
                response = "opening blinds";
                return true;
            }
            else if (action == "close") {
                closeBlinds();
                response = "closing blinds";
                return true;
            }
            else if (action == "stop") {
                stopMotorHandler();
                response = "stopping blinds";
                return true;
            }
            return false;
        }
    );
}

void shadingLoop() {
    handleMotorMovement();
    
    unsigned long now = millis();
    if (now - lastPublishMs >= SHADE_PUBLISH_MS) {
        lastPublishMs = now;
        publishShadeState(); 
    }
}