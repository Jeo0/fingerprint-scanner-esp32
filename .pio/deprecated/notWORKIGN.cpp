// #include <Arduino.h>
// #include <HardwareSerial.h>
// #include <Adafruit_Fingerprint.h>

// // Pin definitions
// const int PIN_DOOR = 18;
// const int PIN_STATE = 15;
// const int RXD2 = 16; // ESP32 RX2 pin (connect to the sensor TX)
// const int TXD2 = 17; // ESP32 TX2 pin (connect to the sensor RX)

// // Fingerprint sensor initialization
// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

// // Globals
// uint8_t id;
// const float gl_time_multiplier = 0.1;
// const int gl_duration_door_open = 10;
// bool gl_state_auth_or_reg = true; // 1 auth, 0 register
// volatile bool isInterruptTriggered = false;  // Flag to track interrupt state
// volatile bool isReadingID = false;          // Flag to track serial input state

// // Prototypes
// void turnOnDevice(const int, const float);
// void IRAM_ATTR getFingerprintIDez();
// uint8_t getFingerprintEnroll();
// uint8_t readnumber(void);

// void setup() {
//   pinMode(PIN_DOOR, OUTPUT);
//   pinMode(PIN_STATE, INPUT_PULLUP); // Use interrupts for PIN_STATE
//   attachInterrupt(digitalPinToInterrupt(PIN_STATE), getFingerprintIDez, HIGH); // Trigger on HIGH state change

//   Serial.begin(115200);
//   while (!Serial);  // Wait for serial port to be ready
//   delay(100);
//   Serial.println("\n\nFingerprint registration with Adafruit sensor");

//   // Initialize Serial2 with the specified pins
//   Serial2.begin(57600, SERIAL_8N1, RXD2, TXD2);

//   // Start the fingerprint sensor
//   finger.begin(57600);

//   if (finger.verifyPassword()) {
//     Serial.println("Fingerprint sensor found!");
//   } else {
//     Serial.println("Fingerprint sensor not found :(");
//     while (1) { delay(1); }
//   }
// }

// void loop() {
//   gl_state_auth_or_reg = digitalRead(PIN_STATE);

//   if (isInterruptTriggered) {
//     isInterruptTriggered = false;
//     gl_state_auth_or_reg = !gl_state_auth_or_reg;  // Toggle the state on interrupt
//   }

//   if (gl_state_auth_or_reg) {
//     // Authenticate
//     getFingerprintIDez();
//     delay(90); // Reduce the speed of the loop
//   } else {
//     // Register
//     if (isReadingID) {
//       Serial.println("Ready to register a fingerprint!");
//       Serial.println("Please enter the ID # (from 1 to 127) where you want to save this fingerprint...");
//       id = readnumber();  // Non-blocking call for reading number
//       if (id == 0) { // ID #0 not allowed, try again
//         return;
//       }
//       Serial.print("Registering ID #");
//       Serial.println(id);

//       while (!getFingerprintEnroll());
//     }
//   }
// }

// // Interrupt handler (non-blocking)
// void IRAM_ATTR getFingerprintIDez() {
//   isInterruptTriggered = true;  // Set the interrupt flag
// }

// // Non-blocking read number function (returns 0 if no valid input)
// uint8_t readnumber(void) {
//   static uint8_t num = 0;

//   if (Serial.available() > 0) {
//     num = Serial.parseInt();  // Read the integer input from Serial
//     if (num == 0) {
//       // If the input is 0, discard and ask again
//       return 0;
//     }
//   }
  
//   return num;  // Return the number entered by the user
// }

// // Fingerprint Enrollment
// uint8_t getFingerprintEnroll() {
//   int p = -1;
//   Serial.print("Waiting for a valid fingerprint to register as #"); Serial.println(id);
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image taken");
//       break;
//     case FINGERPRINT_NOFINGER:
//       Serial.print(".");
//       break;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       break;
//     case FINGERPRINT_IMAGEFAIL:
//       Serial.println("Error capturing image");
//       break;
//     default:
//       Serial.println("Unknown error");
//       break;
//     }
//   }

//   // Image captured successfully
//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Error converting image");
//     return p;
//   }

//   Serial.println("Remove your finger");
//   delay(2000);
//   p = 0;
//   while (p != FINGERPRINT_NOFINGER) {
//     p = finger.getImage();
//   }

//   Serial.print("ID "); Serial.println(id);
//   p = -1;
//   Serial.println("Place the same finger again");
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//   }

//   p = finger.image2Tz(2);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Error converting image");
//     return p;
//   }

//   // Create model from the two images
//   p = finger.createModel();
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Error creating model");
//     return p;
//   }

//   // Store the model at the specified position
//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Error saving model");
//     return p;
//   }

//   Serial.println("Saved!");
//   return true;
// }