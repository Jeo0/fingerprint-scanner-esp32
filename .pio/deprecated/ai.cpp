  /*
  AS608-Optical-Fingerprint-Sensor-enroll
    Modified on 06 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  Home
    based on Adafruit Library

*/
/*
#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

volatile int finger_status = -1;

SoftwareSerial mySerial(2, 3); // TX/RX on fingerprint sensor

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");

  /////////////////////////////////////////
  
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(18, OUTPUT);
  
}

void loop()                     // run over and over again
{
  finger_status = getFingerprintIDez();
  if (finger_status!=-1 and finger_status!=-2){
    Serial.print("Match");


    digitalWrite(18, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(18, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    
    
  } else{
    if (finger_status==-2){
      for (int ii=0;ii<5;ii++){
        Serial.print("Not Match");
      }
    }
  }
  delay(50);            //don't ned to run this at full speed.
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p!=2){
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();
  if (p!=2){
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
*/