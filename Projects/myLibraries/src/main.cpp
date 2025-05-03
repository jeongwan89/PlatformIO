#include <Arduino.h>
#include <TM1637Display.h>

#include "kjwMotor.h"
#include "ACS712Sensor.h"

const int speedPin = 9; // PWM 핀
const int directionPin = 8; // 디지털 핀
const int analogSpeedPin = A0; // 추가된 아날로그 핀 A0
const int imACSPin = A2; // 아날로그 핀 A1
const int moduleACSPin = A1; // 아날로그 핀 A0
const int sensorSensitivity5A = 185; // 5A 센서의 감도 (mV/A)
const int sensorSensitivity20A = 100; // 20A 센서의 감도 (mV/A)
const int CLK = 4; // TM1637 CLK 핀
const int DIO = 5; // TM1637 DIO 핀

kjwMotor motor(speedPin, directionPin);
ACS712Sensor currentSensor(imACSPin, sensorSensitivity5A);
// ACS712Sensor curentSensorModule(moduleACSPin, sensorSensitivity20A);
TM1637Display display(CLK, DIO);
float readCurrent(ACS712Sensor &sensor);
void test1(void);
void test2(void);

void setup()
{
    Serial.begin(115200); // 시리얼 통신 시작
    Serial.println("Motor Test Start");

    // 초기 속도와 방향 설정
    motor.Speed(0); // 속도 50%
    motor.Dir(CW); // 시계 방향

    display.setBrightness(7); // 디스플레이 밝기 설정 (0~7)
    display.clear(); // 디스플레이 초기화
}

void loop()
{
    test1();
}

float readCurrent(ACS712Sensor &sensor)
{
    float current = sensor.readCurrent();
    Serial.print("Current sensor value: ");
    Serial.println(current);
    // 디스플레이에 전류 값 표시
    // Serial.print("Analog reading: ");
    // Serial.println(analogRead(sensor.readRawValue()));
    return current;
}


void test1(void)
{
    delay(500); // 500ms 대기
    // 전류 센서에서 전류 값 읽기
    // 아날로그 핀 A0에서 값을 읽고 motorSpd에 저장
    int motorSpd = analogRead(analogSpeedPin);
    // Serial.print("Analog Speed Value (motorSpd): ");
    // Serial.println(motorSpd);
    // display.clear(); // 디스플레이 초기화

    // 속도 증가 테스트
    for (int speed = 0; speed <= 100; speed += 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
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
        display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");

    // // TM1637 디스플레이에 전류 값 표시
    // int displayValue = static_cast<int>(current * 100); // 전류 값을 소수점 두 자리까지 정수로 변환
    // display.showNumberDec(displayValue, true, 4, 0); // 4자리로 표시
}
/* 
void test2(void)
{
    delay(500); // 500ms 대기
    // 전류 센서에서 전류 값 읽기
    // 아날로그 핀 A0에서 값을 읽고 motorSpd에 저장
    // int motorSpd = analogRead(analogSpeedPin);
    // Serial.print("Analog Speed Value (motorSpd): ");
    // Serial.println(motorSpd);
    // 디스플레이 초기화
    // display.clear(); 

    // 속도 증가 테스트
    for (int speed = 0; speed <= 100; speed += 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensorModule) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensorModule) * 100), 0x40, true, 4, 0); // 4자리로 표시
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
        display.showNumberDecEx( (int) (readCurrent(currentSensorModule) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        display.showNumberDecEx( (int) (readCurrent(currentSensorModule) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");
} */