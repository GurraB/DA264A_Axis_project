//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include <Arduino.h>
#include "readAccelerometer.h"
#include "Wire.h"


#define DATAX0 0x32     //address for X register 1

#define ADDRESS_I2C 0x53            //address for I2C protocol
#define ADDRESS_DATA_FORMAT 0x31    //address for configuring the data format
#define POWER_CTL 0x2D              //address for configuring measure settings
#define FIFO_CTL 0x38               //address for configuring the FIFO mode
#define OFSX 0x1E                   //address for the X-axis offset
#define OFSY 0x1F                   //address for the Y-axis offset
#define OFSZ 0x20                   //address for the Z-axis offset


TwoWire i2cwire;
byte buffert[6];    //buffert to hold the read values
int iterations = 0; //variable to control onboard LED
extern int triggered;

class ReadAccelerometer;

void ReadAccelerometer::setup() {
    sint8_t x_offset, y_offset, z_offset;   //the offset variables
    x_offset = 24;
    y_offset = 6;
    z_offset = -127;
    pinMode(2, OUTPUT); //set onboard LED to output
    i2cwire.begin(4, 5);//pin 4 is SDA and pin 5 is SCL

    writeRegister(ADDRESS_DATA_FORMAT, 0x0F);   //+-16g, justify so LSB is rightmost bit and full resolution (16 bit)
    writeRegister(POWER_CTL, 0x08); //set measure bit
    writeRegister(FIFO_CTL, 0x80);  //FIFO stream, overwrite old values

    writeRegister(OFSX, x_offset);  //write the offsets to the registers
    writeRegister(OFSY, y_offset);
    writeRegister(OFSZ, z_offset);

    digitalWrite(2, HIGH);  //Set the onboard LED to OFF (HIGH apparently?)
}

void ReadAccelerometer::loop() {
    sint16_t x, y, z;
    readRegister(DATAX0, 6);    //read the X axis which is represented by 2 bytes and put value in buffert

    /* Puts the DATAX0 part 0 in the 16 bit variable the take the second bit and shift it up by 8 so we can
     * merge the 2 parts (bytes) into one variable*/
    x = (((int) buffert[1] << 8) | ((int) buffert[0]));
    y = (((int) buffert[3] << 8) | ((int) buffert[2]));
    z = (((int) buffert[5] << 8) | ((int) buffert[4]));

    String data = String(x) + " " + String(y) + " " + String(z);    //put the values in a string to print
    Serial.println(data);                                           // print the values to MATLAB

    /* If the values exceed thresholds trigger the onboard LED and tell camera to take pictures since the
     * person has fallen*/
    if (x > 15000 || x < -15000 || y > 15000 || y < -15000 || z > 17000 || z < -13000) {
        digitalWrite(2, LOW);   //Set the onboard LED to ON (LOW apparently?)
        iterations = 0;         //set the iterations counter to 0
        triggered = 1;
    }
    if (iterations > 200) {     //if iterations is 200, 4 seconds has passed and turn off the LED
        digitalWrite(2, HIGH);  //Turn off the LED
    }
    iterations++;   //increment iterations
    delay(5);      //wait 20 ms for next iteration
}


void ReadAccelerometer::readRegister(char registerAddress, int numBytes) {
    Wire.beginTransmission(ADDRESS_I2C);    //open write communications
    Wire.write(registerAddress);            //change read address to "registeraddress"
    Wire.endTransmission();                 //close write communication

    Wire.requestFrom(ADDRESS_I2C, numBytes); //Request number of bytes to read

    //Read the bytes
    int i = 0;
    while (Wire.available()) {
        buffert[i] = Wire.read();
        i++;
    }
}

void ReadAccelerometer::writeRegister(byte registerAddress, byte val) {
    Wire.beginTransmission(ADDRESS_I2C);    //open write communication
    Wire.write(registerAddress);            //change write address to "address"
    Wire.write(val);                        //write value to register
    Wire.endTransmission();                 //close write communication
}

/* Returns pointer to the task after the task is created */
ReadAccelerometer *getReadAccelerometerInTask() {
    static ReadAccelerometer readAccelerometer_task = ReadAccelerometer();
    return &readAccelerometer_task;
}









