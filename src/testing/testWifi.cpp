//
// @Author Anton Hellbe, Gustaf Bohlin
//

#include <ESP8266WiFiMulti.h>
#include "unittest.h"

void testwifi() {
    assertTrue(WiFi.isConnected(), "WIFI");
}
