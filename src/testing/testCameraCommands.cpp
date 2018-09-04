//
// @Author Johnatan Sona
//

#include "Arduino.h"
#include "ESP8266HTTPClient.h"
#include "testCameraCommands.h"
#include "unittest.h"

HTTPClient testhttp;
int position;
int a = 0;
void testHome() {
    testhttp.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?move=home");
    testhttp.GET();
    delay(1500);
    testhttp.end();

    testhttp.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?query=position");
    testhttp.GET();
    delay(5);
    String str = testhttp.getString();
    String snipstr = str.substring(4,8);
    position = snipstr.toInt();
    testhttp.end();
    delay(1);
    assertEqual(position, 0, "HOME");
}

void testPTZ() {
    testhttp.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?rpan=90");
    testhttp.GET();
    delay(1500);
    testhttp.end();

    testhttp.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?query=position");
    testhttp.GET();
    delay(5);
    String str = testhttp.getString();
    String snipstr = str.substring(4,8);
    position = snipstr.toInt();
    testhttp.end();
    delay(1);
    assertEqual(position,90,"PAN");
}

void testPictureTrigger() {
    testhttp.setAuthorization("root","pass");
    testhttp.begin("http://192.168.20.253/axis-cgi/virtualinput/activate.cgi?schemaversion=1&port=10");
    testhttp.GET();
    delay(10);
    String str = testhttp.getString();
    for(int i = 0; i<=str.length() - 4; i++){
        if((a = (str.substring(i, i + 4) == "true"))) break;
    }
    assertTrue(a, "Virtual Input Activate");
    a = 0;
    testhttp.end();

    testhttp.setAuthorization("root","pass");
    testhttp.begin("http://192.168.20.253/axis-cgi/virtualinput/deactivate.cgi?schemaversion=1&port=10");
    testhttp.GET();
    delay(10);
    str = testhttp.getString();
    for(int i = 0; i<=str.length() - 4; i++){
        if((a = (str.substring(i, i + 4) == "true"))) break;
    }
    assertTrue(a, "Virtual Input Deactivate");
    testhttp.end();
}