//
// @Author Gustaf Bohlin, Anton Hellbe
//

#include "../lib/ESP8266Scheduler/src/Task.h"

#ifndef ESPRESSO2_PICTURECONTROL_H
#define ESPRESSO2_PICTURECONTROL_H

#endif //ESPRESSO2_PICTURECONTROL_H

class pictureControl : public Task {
protected:
    void setup();

    void loop();

};

pictureControl * getpictureControlTask();