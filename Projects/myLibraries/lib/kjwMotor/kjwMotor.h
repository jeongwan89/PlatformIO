#ifndef KJWMOTOR_H
#define KJWMOTOR_H

#include <Arduino.h>

#define CCW 0
#define CW 1

class kjwMotor
{
public:
    // constructor
    kjwMotor();
    kjwMotor(int speedPin, int directionPin);

    // set speed pin
    void SetSpeedPin(int speedPin);

    // set direction pin
    void SetDirectionPin(int directionPin);

    // set speed
    void Speed(int speed);

    // set direction
    void Dir(int direction);

    // toggle direction
    void ToggleDirection();

    // soft toggle direction
    void softToggleDirection(int step = 10); // milliseconds
    // (x)TODO : 감속/가속 step 인수를 받아서 가속도 조정이 가능하게
    //    TODO : 현재의 상태를 monitoring 할 수 있는 인수 추가
    
    // get direction
    int GetDirection();

    // get speed
    int GetSpeed();
    
private:
    int _speedPin;
    int _directionPin;
    int _currentDirection;
};

#endif