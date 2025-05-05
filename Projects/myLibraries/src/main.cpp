#include <Arduino.h>
#include <TM1637Float.h>
#include <TM1637Display.h>

#include <kjwMotor.h>
#include <ACS712Sensor.h>

#include "header.h"
#define TEST_DELAY 1000

kjwMotor motor(speedPin, directionPin);
ACS712Sensor currentSensor(imACSPin, sensorSensitivity5A);
// ACS712Sensor curentSensorModule(moduleACSPin, sensorSensitivity20A);
TM1637Float tm1637Float(CLK, DIO);
float readCurrent(ACS712Sensor &sensor);
void test1(void);
// void test2(void);
void ToggleDirection(kjwMotor &motor, TM1637Float &tm1637Float);

void setup()
{
    pinMode(ToggleSW, INPUT_PULLUP); // 토글 스위치 핀 설정
    pinMode(TacticalSW, INPUT_PULLUP); // 전술 스위치 핀 설정
    pinMode(analogSpeedPin, INPUT); // 아날로그 핀 설정

    Serial.begin(115200); // 시리얼 통신 시작
    Serial.println("Motor Test Start");

    // 초기 속도와 방향 설정
    motor.Speed(0); // 속도 50%
    motor.Dir(CW); // 시계 방향

    tm1637Float.setBrightness(7); // 디스플레이 밝기 설정 (0~7)
    tm1637Float.clear(); // 디스플레이 초기화
}

void loop()
{
    int motorSpd = analogRead(analogSpeedPin); // 아날로그 핀에서 속도 읽기
    if (digitalRead(ToggleSW) == HIGH) // 토글 스위치가 눌리면
    {
        Serial.println("Toggle Switch down");
        motor.Speed(0); // 모터정지
        delay(TEST_DELAY); // 1초 대기
        while(digitalRead(ToggleSW) == HIGH) // 스위치가 눌려있는 동안 정지
        { };
    }
    else {
        Serial.println("Toggle Switch up");
        Serial.print("Analog Speed Value (motorSpd): ");
        Serial.println(motorSpd);
        motor.Speed(map(motorSpd, 0, 1023, 0, 100)); // 모터 속도 설정
        if (digitalRead(TacticalSW) == LOW) // 전술 스위치가 눌리면
        {
            Serial.println("Tactical Switch down");
            ToggleDirection(motor, tm1637Float); // 방향 전환
        }
        else {
            Serial.println("Tactical Switch up");
        }
    }
    tm1637Float.showNumberDec(motorSpd);
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
        tm1637Float.displayFloat(readCurrent(currentSensor), 2); // 소수점 1자리로 표시
        // display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        tm1637Float.displayFloat(readCurrent(currentSensor), 2); // 소수점 1자리로 표시
        // display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
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
        tm1637Float.displayFloat(readCurrent(currentSensor), 2); // 소수점 1자리로 표시
        // display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
    }

    // 속도 감소 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
        tm1637Float.displayFloat(readCurrent(currentSensor), 2); // 소수점 1자리로 표시
        // display.showNumberDecEx( (int) (readCurrent(currentSensor) * 100), 0x40, true, 4, 0); // 4자리로 표시
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
void ToggleDirection(kjwMotor &motor, TM1637Float &display)
{
    int motorSpd = analogRead(analogSpeedPin); // 아날로그 핀에서 속도 읽기
    // 모터 속도 감소
    for(int i = motor.GetSpeed() - 1 ; i >= 1; i -= 10)
    {
        motor.Speed(map(i, 0, 1023, 0, 100));
        delay(6);
        display.showNumberDec(i); // 소수점 1자리로 표시
    }
    // 방향 전환
    motor.ToggleDirection();
    Serial.println("Direction Toggled");
    // 모터 속도 감소
    for(int i = 0; i <= motorSpd; i += 10)
    {
        motor.Speed(map(i, 0, 1023, 0, 100));
        delay(6);
        display.showNumberDec(i); // 소수점 1자리로 표시
    }
}