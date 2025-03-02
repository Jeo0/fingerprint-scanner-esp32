#include "globals.h"

const int PIN_DOOR = 18;
const int PIN_STATE = 15;
const int RXD2 = 16; // ESP32 RX2 pin (connect to the sensor TX)
const int TXD2 = 17; // ESP32 TX2 pin (connect to the sensor RX)

// Use the predefined Serial2 instance
// We do not need to create a new HardwareSerial instance
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

uint8_t id;
const float gl_time_multiplier = 0.4;
const int gl_duration_door_open = 10; // seconds
volatile bool gl_state_auth_or_reg = true; // 1 auth, 0 register