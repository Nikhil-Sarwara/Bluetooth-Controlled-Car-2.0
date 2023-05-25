#include <SoftwareSerial.h>
#define MOTOR_1A 2  // Connect motor driver input 1 to pin 11
#define MOTOR_1B 3  // Connect motor driver input 2 to pin 10
#define MOTOR_2A 4  // Connect motor driver input 3 to pin 9
#define MOTOR_2B 5  // Connect motor driver input 4 to pin 6
#define TX 0        // Connect Bluetooth module Tx to pin 2
#define RX 1        // Connect Bluetooth module Rx to pin 3

SoftwareSerial BTmodule(TX, RX);
int speed = 255;
String readString = "";
int time = 0;

void setup() {
  Serial.begin(9600);
  BTmodule.begin(9600);
  BTmodule.setTimeout(10);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  analogWrite(10, 100);
  analogWrite(9, 100);
}

void loop() {


  while (BTmodule.available()) {
    readString = BTmodule.readString();
    Serial.print("Received: ");
    Serial.println(readString);
  }

  // Read Speed
  ReadSpeed();

  CheckForward();
  CheckBackward();
  CheckLeft();
  CheckRight();
  CheckStop();
}

void MoveForward() {
  analogWrite(MOTOR_1A, speed);
  analogWrite(MOTOR_2A, speed);
}

void MoveForward(int time) {
  analogWrite(MOTOR_1A, speed);
  analogWrite(MOTOR_2A, speed);
  delay(time);
  Stop();
  readString = "Stop";
}

void MoveBackward() {
  analogWrite(MOTOR_1B, speed);
  analogWrite(MOTOR_2B, speed);
}

void MoveBackward(int time) {
  analogWrite(MOTOR_1B, speed);
  analogWrite(MOTOR_2B, speed);
  delay(time);
  Stop();
  readString = "Stop";
}

void MoveLeft() {
  analogWrite(MOTOR_1B, speed);
  analogWrite(MOTOR_2A, speed);
}

void MoveLeft(int time) {
  analogWrite(MOTOR_1B, speed);
  analogWrite(MOTOR_2A, speed);
  delay(time);
  Stop();
  readString = "Stop";
}

void MoveRight() {
  analogWrite(MOTOR_1A, speed);
  analogWrite(MOTOR_2B, speed);
}

void MoveRight(int time) {
  analogWrite(MOTOR_1A, speed);
  analogWrite(MOTOR_2B, speed);
  delay(time);
  Stop();
  readString = "Stop";
}

void Stop() {
  analogWrite(MOTOR_1A, 0);
  analogWrite(MOTOR_1B, 0);
  analogWrite(MOTOR_2A, 0);
  analogWrite(MOTOR_2B, 0);
}

void ReadSpeed() {
  //  Speed
  if (readString.substring(0, 6) == "Speed:") {
    String val = readString.substring(readString.length() - 3);
    if (val.substring(0, 1) == "d") {
      speed = val.substring(2).toInt();
    } else if (val.substring(0, 1) == ":") {
      speed = val.substring(1).toInt();
    } else {
      speed = val.toInt();
    }
    Serial.print("Speed: ");
    Serial.println(speed);
    analogWrite(10, speed);
    analogWrite(9, speed);
  }
}

void CheckForward() {
  if (readString.substring(0, 8) == "Forward:") {
    String val = readString.substring(readString.length() - 3);
    if (val.substring(0, 2) == "d") speed = val.substring(2).toInt();
    else if (val.substring(0, 1) == ":") time = val.substring(1).toInt();
    else time = val.toInt();
    MoveForward(time * 1000);
  } else if (readString == "Forward") MoveForward();
}

void CheckBackward() {
  if (readString.substring(0, 9) == "Backward:") {
    String val = readString.substring(readString.length() - 3);
    if (val.substring(0, 2) == "d") speed = val.substring(2).toInt();
    else if (val.substring(0, 1) == ":") time = val.substring(1).toInt();
    else time = val.toInt();

    MoveBackward(time * 1000);
  } else if (readString == "Backward") MoveBackward();
}

void CheckLeft() {
  if (readString.substring(0, 5) == "Left:") {
    String val = readString.substring(readString.length() - 3);
    if (val.substring(0, 2) == "d") speed = val.substring(2).toInt();
    else if (val.substring(0, 1) == ":") time = val.substring(1).toInt();
    else time = val.toInt();

    MoveLeft(time * 1000);
  } else if (readString == "Left") MoveLeft();
}

void CheckRight() {
  if (readString.substring(0, 6) == "Right:") {
    String val = readString.substring(readString.length() - 3);
    if (val.substring(0, 2) == "d") speed = val.substring(2).toInt();
    else if (val.substring(0, 1) == ":") time = val.substring(1).toInt();
    else time = val.toInt();

    MoveRight(time* 1000);
  } else if (readString == "Right") MoveRight();
}

void CheckStop() {
  if (readString == "Stop") Stop();
}