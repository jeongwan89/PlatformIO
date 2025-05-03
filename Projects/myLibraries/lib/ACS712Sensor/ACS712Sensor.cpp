#include "ACS712Sensor.h"

#define DEBUG 

ACS712Sensor::ACS712Sensor(int analogPin, float sensitivity)
    : _analogPin(analogPin), _sensitivity(sensitivity)
{
    pinMode(_analogPin, INPUT);
}

ACS712Sensor::ACS712Sensor(int analogPin, const String &sensorType)
{
    _analogPin = analogPin;
    if (sensorType == "05A")
        _sensitivity = 185.0; // 5A 센서의 감도 (mV/A)
    else if (sensorType == "20A")
        _sensitivity = 100.0; // 20A 센서의 감도 (mV/A)
    else if (sensorType == "30A")
        _sensitivity = 66.0; // 30A 센서의 감도 (mV/A)
    else
        _sensitivity = 185.0; // 기본값: 5A 센서
    pinMode(_analogPin, INPUT);
}

float ACS712Sensor::readCurrent()
{
    int rawValue = analogRead(_analogPin); // 아날로그 값 읽기
    float voltage = (rawValue * _vRef) / _adcResolution; // 전압으로 변환
    float current = (voltage - (_vRef / 2)) / (_sensitivity / 1000.0); // 전류 계산
#ifdef DEBUG
    Serial.print("Raw Value: "); Serial.print(rawValue); Serial.print(" Voltage: "); Serial.print(voltage); Serial.print(" Current: "); Serial.println(current);
#endif
    return current;
}