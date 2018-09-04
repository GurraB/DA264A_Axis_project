//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include "Arduino.h"
#include "ESP8266HTTPClient.h"
#include "testHttp.h"
#include "unittest.h"

HTTPClient httpClient;

void testHttpCommand()
{
    httpClient.begin("http://192.168.20.253/axis-cgi/com/ptz.cgi?rpan=40");
    int httpCode = httpClient.GET();
    delay(5);
    httpClient.end();
    assertEqual(httpCode, 204, "HTTP request");

}
