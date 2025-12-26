#include "Adafruit_VL53L0X.h"
#include "MazeRepresentation.h"

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }
  
  setPins();

  Serial.println(F("Shutdown pins inited..."));

  Serial.println(F("All in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));
  setID();
 
}

void loop() {
  int counterForLeft = 0;
  int counterForRight = 0;
  while(counterForLeft <= 5000 && counterForRight <= 5000){
    move();
    counterForLeft = leftEncoderCount();
    counterForRight = rightEncoderCount();
  }
  readEncoders();
  /*
  move();
  readEncoders();
  Serial.print(F("1: ") );
  Serial.print(readLeftSensor());
  Serial.print(F("  "));
  Serial.print(F("2: "));
  Serial.print(readFrontSensor());
  Serial.print(F("  "));
  Serial.print(F("3: "));
  Serial.print(readRightSensor());
  Serial.println(F("  "));*/
  timer(1000);
}
