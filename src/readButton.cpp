//
// @Author Gustaf Bohlin, Anton Hellbe
// Task for reading the button
//

#include "Arduino.h"
#include "readButton.h"


class ReadButton;

extern int triggered;



void ReadButton::setup()
{
    Serial.println("Setup Button task");
    pinMode(16, INPUT_PULLDOWN_16); // Set pin 16 to Input with integrated pull-down

}

void ReadButton::loop() {
    if (digitalRead(16)) { // if button is pressed, set triggered to 1
        triggered = 1;
    }
    delay(5);
}


/* Returns pointer to the task after the task is created */
ReadButton * getReadButtonTask(){
    static ReadButton readButton_Task = ReadButton();
    return &readButton_Task;
}



