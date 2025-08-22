// main program file

#include "irrigation/irrigation.h"
#include "shades/shades.h"    
#include "wifi/wifi_mqtt.h"   

void setup {
    setupWifi();
    setupSinric();
    setupMQTT();
    setupIrrigation();
    setupShading();
}


void loop() {
  wifiLoop(); 
  mqttLoop(); 
  sinricLoop();        
  irrigationLoop();     
  shadingLoop();     
}
