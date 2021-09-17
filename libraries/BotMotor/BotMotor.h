/*
BotMotor.h - Library for controlling motors to drive a simple bot
*/
#ifndef BotMotor_h
#define BotMotor_h

#include "Arduino.h"

class BotMotor
{
  public:
    BotMotor(byte pinPWM, byte pinIN1, byte pinIN2, int reversed);
    void spin(int speed);
    void stop();
    void coast();
  private:
    byte _pinPWM;
    byte _pinIN1;
    byte _pinIN2;
    int _reversed;
};

#endif