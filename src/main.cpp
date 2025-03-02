

#include "globals.h"
// from https://forum.arduino.cc/t/as608-fingerprint-sensor-not-working-with-esp32-serial-error-resolved/1305162/7


void setup() {
  pinMode(PIN_DOOR, OUTPUT);
  pinMode(PIN_STATE, INPUT_PULLUP); // use interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_STATE), getFingerprintIDez, HIGH); // 0 regis -> 1 auth


  Serial.begin(115200);
  while (!Serial);  // Wait for the serial port to open
  delay(100);
  Serial.println("\n\nFingerprint registration with Adafruit sensor");

  // Initialize Serial2 with the specified pins
  Serial2.begin(57600, SERIAL_8N1, RXD2, TXD2);

  // Start the fingerprint sensor
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
  } else {
    Serial.println("Fingerprint sensor not found :(");
    while (1) { delay(1); }
  }

  // display
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("System ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet length: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
}


void loop() {
  gl_state_auth_or_reg = digitalRead(PIN_STATE);

  switch (gl_state_auth_or_reg){
    case true: {    // 1 authentication
      getFingerprintIDez();
      delay(90); // don't need to run this at full speed.
      break;
    }

    case false: {   // 0 register
      Serial.println("Ready to register a fingerprint!");
      Serial.println("Please enter the ID # (from 1 to 127) where you want to save this fingerprint...");
      id = readnumber();
      if (id == 0) { // ID #0 not allowed, try again
        return;
      }
      Serial.print("Registering ID #");
      Serial.println(id);

      while (!getFingerprintEnroll());
      break;
    }
  }

}
