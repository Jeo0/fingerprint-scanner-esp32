#pragma once
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Adafruit_Fingerprint.h>

extern const int PIN_DOOR;
extern const int PIN_STATE;
extern const int RXD2; // ESP32 RX2 pin (connect to the sensor TX)
extern const int TXD2; // ESP32 TX2 pin (connect to the sensor RX)

// Use the predefined Serial2 instance
// We do not need to create a new HardwareSerial instance
extern Adafruit_Fingerprint finger;

extern uint8_t id;
extern const float gl_time_multiplier;
extern const int gl_duration_door_open; // seconds
extern volatile bool gl_state_auth_or_reg; // 1 auth, 0 register



///////////////////////////
// prototypes
void turnOnDevice(const int, const float);

// auth
void IRAM_ATTR getFingerprintIDez();

// regis
uint8_t getFingerprintEnroll();
uint8_t readnumber(void);