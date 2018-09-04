//
// @Author Gustaf Bohlin, Anton Hellbe
//
#include <Arduino.h>
#include "testADXL345.h"
#include "unittest.h"
#include "Wire.h"
#include "testWifi.h"
#include "testHttp.h"
#include "testCameraCommands.h"
#include "ESP8266HTTPClient.h"

#define DATAX0 0x32     //address for X register 1

#define ADDRESS_I2C 0x53            //address for I2C protocol
#define ADDRESS_DATA_FORMAT 0x31    //address for configuring the data format
#define POWER_CTL 0x2D              //address for configuring measure settings
#define FIFO_CTL 0x38               //address for configuring the FIFO mode
#define OFSX 0x1E                   //address for the X-axis offset
#define OFSY 0x1F                   //address for the Y-axis offset
#define OFSZ 0x20                   //address for the Z-axis offset

HTTPClient httpclienT;

void test_setup() {

    TwoWire i2cwire2;
    sint8_t x_offset, y_offset, z_offset;   //the offset variables
    x_offset = 24;      //trial and error configured variables
    y_offset = 6;
    z_offset = -127;
    pinMode(2, OUTPUT); //set onboard LED to output
    i2cwire2.begin(4, 5);//pin 4 is SDA and pin 5 is SCL

    writeRegister(ADDRESS_DATA_FORMAT, 0x0F);   //+-16g, justify so LSB is rightmost bit and full resolution (16 bit)
    writeRegister(POWER_CTL, 0x08); //set measure bit
    writeRegister(FIFO_CTL, 0x80);  //FIFO stream, overwrite old values

    writeRegister(OFSX, x_offset);  //write the offsets to the registers
    writeRegister(OFSY, y_offset);
    writeRegister(OFSZ, z_offset);

    httpclienT.setAuthorization("root","pass");
    httpclienT.begin("http://192.168.20.253/axis-cgi/virtualinput/deactivate.cgi?schemaversion=1&port=10");
    httpclienT.GET();
    delay(10);
    httpclienT.end();


}

void test_main() {
    test_setup();

    testBegin("ADXL345");
    test_i2c_communication();
    test_address_data_format();
    test_power_ctrl();
    test_fifo();
    test_offset(24, 6, -127);
    testEnd();

    testBegin("Connectivity");
    testwifi();
    testHttpCommand();
    testEnd();

    testBegin("Camera");
    testHome();
    testPTZ();
    testPictureTrigger();
    testEnd();

    while(1) {
        yield();
    }
}