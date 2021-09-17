#include <BotMotor.h>

//configuring motor connections
const byte LeftIN1 = 13;
const byte LeftIN2 = 12;
const byte LeftPWM = 11;
const byte RightIN1 = 8;
const byte RightIN2 = 9;
const byte RightPWM = 10;
BotMotor LeftMotor(LeftPWM, LeftIN1, LeftIN2, 0); // LeftMotor is not reversed
BotMotor RightMotor(RightPWM, RightIN1, RightIN2, 1); // RightMotor is reversed

const byte BUTTON = 7; //pin to read voltage from button
const byte Ain = A0; 

// stops the bot (brake = 1 to hard brake, brake = 0 to coast)
void stopBot(int brake) {
  if (brake) {
    LeftMotor.stop();
    RightMotor.stop();
  } else {
    LeftMotor.coast();
    RightMotor.coast();
  }
}

// drives the bot forward (botSpeed > 0) or backwards (botSpeed < 0) at given speed for time specified in milliseconds (or forever if timeMS < 0)
void driveBot(int botSpeed, int timeMS, int brake) {
  LeftMotor.spin(botSpeed);
  RightMotor.spin(botSpeed);
  if (timeMS >= 0) {
    delay(timeMS);
    stopBot(brake);
  }
  delay(5);
}

// turns the bot right (botSpeed > 0) or left (botSpeed < 0) at given speed for time specified in milliseconds (or forever if timeMS < 0)
void turnBot(int botSpeed, int timeMS, int brake) {
  LeftMotor.spin(botSpeed);
  RightMotor.spin(-botSpeed);
  if (timeMS >= 0) {
    delay(timeMS);
    stopBot(brake);
  }
  delay(5);
}

//tests each motor individually
void testSequence() {
  LeftMotor.spin(-50);
  delay(1000);
  LeftMotor.stop();
  delay(1000);
  LeftMotor.spin(200);
  delay(1000);
  LeftMotor.coast();
  delay(1000);
  LeftMotor.stop();
  delay(1000);
  
  RightMotor.spin(-50);
  delay(1000);
  RightMotor.stop();
  delay(1000);
  RightMotor.spin(200);
  delay(1000);
  RightMotor.coast();
  delay(1000);
  RightMotor.stop();
  delay(1000);
}


void setup() {
  //button control
  pinMode(Ain, INPUT);
}

void loop() {  
  //testSequence();
  while (analogRead(Ain) <= 900) { delay(100); } //waits for button pressed
  driveBot(100, 1000, 1); //drive forwards
  delay(1000);
  driveBot(-100, 1000, 1); //drive backwards
  delay(1000);
  turnBot(50, 1000, 1); //turn right
  delay(1000);
  turnBot(-50, 1000, 1); //turn left
  delay(1000);
  driveBot(200, 1000, 0); //drive forward, end by coasting to stop
}
