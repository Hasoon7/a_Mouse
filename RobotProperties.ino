#include "MazeRepresentation.h"
#include "Adafruit_VL53L0X.h"
#include <Arduino.h>
#include <ESP32Encoder.h>


//left encoder
#define ENC_L_A  4
#define ENC_L_B 16
ESP32Encoder leftEncoder;

//right encoder
#define ENC_R_A  0
#define ENC_R_B  2
ESP32Encoder rightEncoder;

//right motor
#define IN1 26
#define IN2 12
#define ENA 27

//left motor
#define IN3 33
#define IN4 32
#define ENB 13


//ToF XSHUT pins
#define SHT_LOX1 19
#define SHT_LOX2 5
#define SHT_LOX3 17

//ToF Addresses
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32


// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// this holds the measurement of the ToF sensors
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;


void move(){
  
  Serial.println("Moving forward...");

  // Forward direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  ledcWrite(ENA, 150);   // right motor
  ledcWrite(ENB, 150);   // left motor

  timer(200);  // short movement

  // Stop motors
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);

  timer(2000); // wait before next test
}

void moveUntil(int threshold){
  int counterForLeft = 0;
  int counterForRight = 0;
  while(counterForLeft <= threshold && counterForRight <= threshold){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(ENA, 100);
    ledcWrite(ENB, 100);
    counterForLeft = leftEncoder.getCount();
    counterForRight = rightEncoder.getCount();
  }
}

int leftEncoderCount(){
  return leftEncoder.getCount();
}

int rightEncoderCount(){
  return rightEncoder.getCount();
}
void timer(int duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    
  }
}

void readEncoders(){

  Serial.print("Left Enc: ");
  Serial.print(leftEncoder.getCount());

  Serial.print(" | Right Enc : ");
  Serial.println(rightEncoder.getCount());
}

void setPins(){

  pinMode(ENC_L_A, INPUT_PULLUP);
  pinMode(ENC_L_B, INPUT_PULLUP);
  pinMode(ENC_R_A, INPUT_PULLUP);
  pinMode(ENC_R_B, INPUT_PULLUP);

  leftEncoder.attachFullQuad(ENC_L_B, ENC_L_A);
  leftEncoder.clearCount();

  rightEncoder.attachFullQuad(ENC_R_A, ENC_R_B);
  rightEncoder.clearCount();

  // Motor pins
  
  // right motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // left motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Encoder pins
  
  // left encoder
  pinMode(ENC_L_A, INPUT_PULLUP);
  pinMode(ENC_L_B, INPUT_PULLUP);
  
  //right encoder
  pinMode(ENC_R_A, INPUT_PULLUP);
  pinMode(ENC_R_B, INPUT_PULLUP);

  ledcAttach(ENA, 1000, 8);  // pin, freq, resolution
  ledcAttach(ENB, 1000, 8);

  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);

  // ToF XSHUT pins
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  
}

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
}

int readLeftSensor(){
  lox1.rangingTest(&measure1, false);
  if(measure1.RangeStatus != 4) {     // if not out of range
    return measure1.RangeMilliMeter;
  } else {
    return -1;
  }
}

int readFrontSensor(){
  lox2.rangingTest(&measure2, false);
  if(measure2.RangeStatus != 4) {     // if not out of range
    return measure2.RangeMilliMeter;
  } else {
    return -1;
  }
}

bool checkIfWallIsInDirection(int d){
  if(d == Left){
    return (readLeftSensor() < 40 && readLeftSensor() != -1);
  }
  else if(d == Front){
    return (readFrontSensor() < 40 && readFrontSensor() != -1);
  }
  else if(d == Right){
    return (readRightSensor() < 40 && readRightSensor() != -1);
  }
}

int readRightSensor(){
  lox3.rangingTest(&measure3, false);
  if(measure3.RangeStatus != 4) {     // if not out of range
    return measure3.RangeMilliMeter;
  } else {
    return -1;
  }
}

int readLeftEncoder();
int readRightEncoder();
void turnLeft();
void moveForward();
void turnRight();

