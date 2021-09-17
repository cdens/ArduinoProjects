/*
BotMotor.cpp - Creates BotMotor class to control a motor
*/

#include "Arduino.h"
#include "BotMotor.h"

BotMotor::BotMotor(byte pinPWM, byte pinIN1, byte pinIN2, int reversed)
{
  pinMode(pinPWM, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  _pinPWM = pinPWM;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _reversed = reversed; //reverse directions (for dual outboard or inboard facing motors so positive speed = move in same direction)
}


void BotMotor::spin(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }
        
    if ((speed > 0 && !_reversed) || (speed < 0 && _reversed)){ //clockwise
        digitalWrite(_pinIN1, HIGH);
        digitalWrite(_pinIN2, LOW);
    } else if ((speed < 0 && !_reversed) || (speed > 0 && _reversed)) { //counterclockwise
        digitalWrite(_pinIN1, LOW);
        digitalWrite(_pinIN2, HIGH);
    } else { //hard stop (speed = 0)
        digitalWrite(_pinIN1, HIGH);
        digitalWrite(_pinIN2, HIGH);
    }
    
    digitalWrite(_pinPWM, abs(speed));
}


void BotMotor::stop() { //hard brake
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, HIGH);
  digitalWrite(_pinPWM, 0);
}


void BotMotor::coast() { //coast motor
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, LOW);
  digitalWrite(_pinPWM, 0);
}
