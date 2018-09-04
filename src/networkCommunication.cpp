//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include "ESP8266HTTPClient.h"
#include <ESP8266WiFi.h>

static HTTPClient httpClient;

/* Check if we're still connected to the wifi. If we are not connected, reset the program to reconnect and reinitialize */
void connected() {
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(14, 0);
    }
}

/* initialze the ptz movement by moving the camera to its home position */
void setupPTZ() {
    connected();
    httpClient.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?move=home");
    httpClient.GET();
    delay(5);
    httpClient.end();
}

/* pan the camera by 60 degrees */
void panCamera() {
    httpClient.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?rpan=60");
    httpClient.GET();
    delay(5);
    httpClient.end();
}

/* activate port 10 to tell the camera to take a picture */
void activatePort10() {
    connected();
    httpClient.setAuthorization("root", "pass");
    httpClient.begin("http://192.168.20.253/axis-cgi/virtualinput/activate.cgi?schemaversion=1&port=10");
    httpClient.GET();
    delay(5);
    httpClient.end();
}

/* deactivate port 10 to prepare for next image */
void deActivatePort10() {
    connected();
    httpClient.setAuthorization("root", "pass");
    httpClient.begin("http://192.168.20.253/axis-cgi/virtualinput/deactivate.cgi?schemaversion=1&port=10");
    httpClient.GET();
    delay(5);
    httpClient.end();
}


/* initialize picture control by setting port 10 to deactivated and zoom to 0 */
void setupPictureControl() {
    connected();
    httpClient.begin("http://192.168.20.253/axis-cgi/virtualinput/deactivate.cgi?schemaversion=1&port=10");
    httpClient.GET();
    delay(5);
    httpClient.end();
    httpClient.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?zoom=0");
    httpClient.GET();
    delay(5);
    httpClient.end();
}