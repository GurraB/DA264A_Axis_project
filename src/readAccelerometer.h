//
// @Author Gustaf Bohlin, Anton Hellbe
//

#ifndef ESPRESSO2_READANALOGIN_H
#define ESPRESSO2_READANALOGIN_H

#include "../lib/ESP8266Scheduler/src/Task.h"

class ReadAccelerometer : public Task {

protected:
    void setup();

    void loop();
    /* Writes 'val' to specified register */
    void writeRegister(byte registerAddress, byte val);
    /* Reads a register via I2C protocol and puts the values in a buffert */
    void readRegister(char registerAddress, int numBytes);
};

/* Returns pointer to the Task */
ReadAccelerometer * getReadAccelerometerInTask();


#endif //ESPRESSO2_READANALOGIN_H
