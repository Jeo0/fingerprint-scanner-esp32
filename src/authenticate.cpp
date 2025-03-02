#include "globals.h"


// auth
// {{{{{{{{// returns -1 if failed, otherwise returns ID #}}}}}}}}}}}} void*
// also interrupt
void IRAM_ATTR getFingerprintIDez() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)
    {
        Serial.println("Waiting For Valid Finger");
        //return -1;
        return ;
    }

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)
    {
        Serial.println("Prateek Image Try Again");
        delay(3000);
        // return -1;
        return ;
    }

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)
    {
        Serial.println("Not Valid Finger");
        delay(3000);
        // return -1;
        return ;
    }

    // found a match!
    Serial.println("door unlocked\n");



    // use the device
    turnOnDevice(PIN_DOOR, gl_duration_door_open);




    Serial.println("Door Unlocked Welcome");

    // return finger.fingerID;
}