#include "kjwMotor.h"
#include <Arduino.h>

// ...existing code...

kjwMotor::kjwMotor()
    : _speedPin(-1), _directionPin(-1), _currentDirection(CW)
{
    // Default constructor body can be empty or initialize pins to default values
}

kjwMotor::kjwMotor(int speedPin, int directionPin)
    : _speedPin(speedPin), _directionPin(directionPin), _currentDirection(CW)
{
    pinMode(_speedPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
}

void kjwMotor::SetSpeedPin(int speedPin)
{
    _speedPin = speedPin;
    pinMode(_speedPin, OUTPUT);
}

void kjwMotor::SetDirectionPin(int directionPin)
{
    _directionPin = directionPin;
    pinMode(_directionPin, OUTPUT);
}

void kjwMotor::Speed(int speed)
{
    if (speed < 0) speed = 0;
    if (speed > 100) speed = 100;
    int mappedSpeed = map(speed, 0, 100, 0, 255);
    analogWrite(_speedPin, mappedSpeed);
}

void kjwMotor::Dir(int direction)
{
    if (direction == CCW)
    {
        digitalWrite(_directionPin, LOW);
    }
    else if (direction == CW)
    {
        digitalWrite(_directionPin, HIGH);
    }
}

void kjwMotor::ToggleDirection()
{
    if (_currentDirection == CCW)
    {
        _currentDirection = CW;
    }
    else
    {
        _currentDirection = CCW;
    }
    Dir(_currentDirection);
}
