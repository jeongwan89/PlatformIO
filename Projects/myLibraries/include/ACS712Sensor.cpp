#include "ACS712Sensor.h"

ACS712Sensor::ACS712Sensor(int analogPin, float sensitivity)
    : _analogPin(analogPin), _sensitivity(sensitivity)
{
    pinMode(_analogPin, INPUT);
}

float ACS712Sensor::readCurrent()
{
    int rawValue = analogRead(_analogPin); // 아날로그 값 읽기
    float voltage = (rawValue * _vRef) / _adcResolution; // 전압으로 변환
    float current = (voltage - (_vRef / 2)) / (_sensitivity / 1000.0); // 전류 계산
    return current;
}