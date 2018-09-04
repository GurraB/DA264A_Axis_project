//
// @Author Gustaf Bohlin, Anton Hellbe
//

#ifndef ESPRESSO2_TESTADXL345_H
#define ESPRESSO2_TESTADXL345_H

#include "../../../../../../.platformio/packages/framework-arduinoespressif8266/tools/sdk/include/c_types.h"
#include "../../../../../../.platformio/packages/framework-arduinoespressif8266/cores/esp8266/Arduino.h"

void test_i2c_communication();

void test_address_data_format();

void test_power_ctrl();

void test_fifo();

void test_offset(sint8_t x_offset, sint8_t y_offset, sint8_t z_offset);

void readRegister(char registerAddress, int numBytes);

void writeRegister(byte registerAddress, byte val);

#endif //ESPRESSO2_TESTADXL345_H
