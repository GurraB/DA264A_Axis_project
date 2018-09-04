//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include <c_types.h>
#include <Wire.h>
#include <Arduino.h>
#include "testADXL345.h"
#include "unittest.h"

#define ADDRESS_I2C 0x53
#define THRESH_TAP 0x1D
#define ADDRESS_DATA_FORMAT 0x31    //address for configuring the data format
#define POWER_CTL 0x2D              //address for configuring measure settings
#define FIFO_CTL 0x38               //address for configuring the FIFO mode
#define OFSX 0x1E                   //address for the X-axis offset
#define OFSY 0x1F                   //address for the Y-axis offset
#define OFSZ 0x20                   //address for the Z-axis offset

byte testbuffert[1];

void test_i2c_communication() {
    writeRegister(THRESH_TAP, 0x00);
    readRegister(THRESH_TAP, 1);
    assertEqual(testbuffert[0], 0x00, "i2c");
    writeRegister(THRESH_TAP, 0xFF);
    readRegister(THRESH_TAP, 1);
    assertEqual(testbuffert[0], 0xFF, "i2c");
}

void test_address_data_format() {
    readRegister(ADDRESS_DATA_FORMAT, 1);
    assertBits(testbuffert[0], 0xF, 0xF, "data format");
}

void test_power_ctrl() {
    readRegister(POWER_CTL, 1);
    assertBitHigh(testbuffert[0], 3, "power ctrl");
}

void test_fifo() {
    readRegister(FIFO_CTL, 1);
    assertBits(testbuffert[0], 0x80, 0xC0, "fifo");
}

void test_offset(sint8_t x_offset, sint8_t y_offset, sint8_t z_offset) {
    readRegister(OFSX, 1);
    assertEqual(x_offset, testbuffert[0], "xoffs");
    readRegister(OFSY, 1);
    assertEqual(y_offset, testbuffert[0], "yoffs");
    readRegister(OFSZ, 1);
    assertEqual(z_offset, (sint8_t)testbuffert[0], "zoffs");
}

void readRegister(char registerAddress, int numBytes){
    Wire.beginTransmission(ADDRESS_I2C);    //open write communications
    Wire.write(registerAddress);            //change read address to "registeraddress"
    Wire.endTransmission();                 //close write communication

    Wire.requestFrom(ADDRESS_I2C, numBytes); //Request number of bytes to read

    //Read the bytes
    int i = 0;
    while(Wire.available())
    {
        testbuffert[i] = Wire.read();
        i++;
    }
}

void writeRegister(byte registerAddress, byte val) {
    Wire.beginTransmission(ADDRESS_I2C);    //open write communication
    Wire.write(registerAddress);            //change write address to "address"
    Wire.write(val);                        //write value to register
    Wire.endTransmission();                 //close write communication
}