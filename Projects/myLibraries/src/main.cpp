#include <Arduino.h>
#include <TM1637Display.h>

#include "kjwMotor.h"
#include "ACS712Sensor.h"

const int speedPin = 9; // PWM 핀
const int directionPin = 8; // 디지털 핀
const int analogPin = A1; // 아날로그 핀 A1
const int sensorSensitivity = 185; // 5A 센서의 감도 (mV/A)
const int analogSpeedPin = A0; // 추가된 아날로그 핀 A0
const int CLK = 4; // TM1637 CLK 핀
const int DIO = 5; // TM1637 DIO 핀

kjwMotor motor(speedPin, directionPin);
ACS712Sensor currentSensor(analogPin, sensorSensitivity);
TM1637Display display(CLK, DIO);
float readCurrent(void);
void setup()
{
    Serial.begin(115200); // 시리얼 통신 시작
    Serial.println("Motor Test Start");

    // 초기 속도와 방향 설정
    motor.Speed(50); // 속도 50%
    motor.Dir(CW); // 시계 방향

    display.setBrightness(7); // 디스플레이 밝기 설정 (0~7)
}

void loop()
{
    delay(500); // 500ms 대기
    // 전류 센서에서 전류 값 읽기
    // 아날로그 핀 A0에서 값을 읽고 motorSpd에 저장
    int motorSpd = analogRead(analogSpeedPin);
    Serial.print("Analog Speed Value (motorSpd): ");
    Serial.println(motorSpd);
    display.clear(); // 디스플레이 초기화

    // 속도 증가 테스트
    for (int speed = 0; speed <= 100; speed += 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) readCurrent() * 100, 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) readCurrent() * 100, 0x40, true, 4, 0); // 4자리로 표시
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");

    // 속도 증가 테스트
    for (int speed = 0; speed <= 100; speed += 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) readCurrent() * 100, 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) readCurrent() * 100, 0x40, true, 4, 0); // 4자리로 표시
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");

    // // TM1637 디스플레이에 전류 값 표시
    // int displayValue = static_cast<int>(current * 100); // 전류 값을 소수점 두 자리까지 정수로 변환
    // display.showNumberDec(displayValue, true, 4, 0); // 4자리로 표시
}

float readCurrent(void)
{
    // 아날로그 핀에서 전압 읽기
    int sensorValue = analogRead(analogPin);
    // 전압을 전류로 변환 (센서 감도에 따라 조정)
    float voltage = sensorValue * (5.0 / 1023.0); // 5V 기준
    float current = (voltage - 2.5) / (sensorSensitivity / 1000.0); // mV/A로 변환
    Serial.print("Current sensor value: ");
    Serial.println(sensorValue);
    // 디스플레이에 전류 값 표시
    return current;
}   