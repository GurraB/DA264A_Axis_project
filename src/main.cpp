/**
 * @Author Gustaf Bohlin, Anton Hellbe
 *
 */

#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include "../lib/ESP8266Scheduler/src/Scheduler.h"
#include "readAccelerometer.h"
#include "ptzcontrol.h"
#include "pictureControl.h"
#include "readButton.h"


int triggered = 0;
int pan = 0;

void setup() {
    pinMode(14, OUTPUT);
    digitalWrite(14, 1);    //Reset the reset pin
    Serial.begin(115200);
    const char *ssid = "vetinte";
    const char *password = "redbull123";
    Serial.println();
    Serial.println();
    Serial.println();

    /* Configuring IP-adress, gateway and subnetmask for WIFI */
    IPAddress ip(192, 168, 20, 199);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.mode(WIFI_STA);

    WiFi.config(ip, gateway, subnet); // Enable the configuration

    WiFi.begin(ssid, password); // Connect to WiFi

    Serial.println("Connecting to ");
    Serial.println(ssid);

    /* Program will be stuck here until a wifi connection is established */
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(1000);
        yield();
    }
    delay(2000);

    Serial.println("Connection established");

    /* Starting all tasks */
    Scheduler.start(getReadAccelerometerInTask());
    Scheduler.start(getptzTask());
    Scheduler.start(getpictureControlTask());
    Scheduler.start(getReadButtonTask());
    Scheduler.begin();
}


void loop() {

}
