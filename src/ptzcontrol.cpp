//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include <Arduino.h>

#include "networkCommunication.h"
#include "../lib/ESP8266Scheduler/src/Scheduler.h"
#include "ptzcontrol.h"



class PTZcontrol;

extern int pan;

void PTZcontrol::setup() {

    Serial.println("Setup PTZ");
    setupPTZ();
    Serial.println("setup PTZ done\n");
}

void PTZcontrol::loop() {
    connected();
    if (pan) {
        panCamera();
        pan = 0;
    }
    delay(100);
}

/* Returns pointer to the task after the task is created */
PTZcontrol *getptzTask() {
    static PTZcontrol task = PTZcontrol();
    return &task;
}