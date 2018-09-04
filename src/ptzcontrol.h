//
// @Author Gustaf Bohlin, Anton Hellbe
//

#ifndef ESPRESSO2_PTZCONTROL_H
#define ESPRESSO2_PTZCONTROL_H

#include "../lib/ESP8266Scheduler/src/Task.h"

class PTZcontrol : public Task {

protected:
    void setup();

    void loop();
};

PTZcontrol * getptzTask();


#endif //ESPRESSO2_PTZCONTROL_H
