//
// @Author Gustaf Bohlin, Anton Hellbe
//

#ifndef ESPRESSO2_READBUTTON_H
#define ESPRESSO2_READBUTTON_H

#include "../lib/ESP8266Scheduler/src/Task.h"

class ReadButton : public Task {
protected:
    void setup();

    void loop();

};

ReadButton * getReadButtonTask();

#endif //ESPRESSO2_READBUTTON_H
