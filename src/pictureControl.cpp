//
// @Author Gustaf Bohlin, Anton Hellbe
//


#include "pictureControl.h"
#include "networkCommunication.h"


class pictureControl;
extern int triggered;
static int iterations = 0;
extern int pan;
long previouspic = 0;

/* setup the picture control */
void pictureControl :: setup(){
        Serial.println("PictureControl Setup");
        setupPictureControl();
        Serial.println("PictureControl Setup Done");
}


/* take a picture if we have triggered */
void pictureControl :: loop() {
    connected();
    if(triggered){
        if(iterations >= 6) {   //condition to make sure we take 6 pictures
            triggered = 0;
            iterations = 0;
        }else if (millis() - previouspic > 2000){   //only take picture every two seconds
            activatePort10();
            deActivatePort10();
            pan = 1;
            iterations++;
            previouspic = millis();
        }
    }
    delay(100);
}

/* Returns pointer to the task after the task is created */
pictureControl * getpictureControlTask() {
    static pictureControl task = pictureControl();
    return &task;
}