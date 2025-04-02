#ifndef ACS712SENSOR_H
#define ACS712SENSOR_H

#include <Arduino.h>

/*
analogPin: 센서가 연결된 아날로그 핀 번호를 지정합니다.
sensitivity: 센서의 감도(mV/A)를 설정합니다. 예를 들어, 
            ACS712-05B는 185mV/A, 
            ACS712-20A는 100mV/A, 
            ACS712-30A는 66mV/A입니다.
readCurrent: 아날로그 값을 읽고 전류를 계산하여 반환합니다.
*/
class ACS712Sensor
{
public:
    // 생성자: 아날로그 핀 번호와 센서의 감도(mV/A)를 설정
    ACS712Sensor(int analogPin, float sensitivity);

    // 전류 값을 읽어오는 함수 (단위: 암페어)
    float readCurrent();

private:
    int _analogPin;       // 아날로그 핀 번호
    float _sensitivity;   // 센서 감도 (mV/A)
    const float _vRef = 5.0; // Arduino의 참조 전압 (5V)
    const int _adcResolution = 1024; // ADC 해상도 (10비트)
};

#endif // ACS712SENSOR_H