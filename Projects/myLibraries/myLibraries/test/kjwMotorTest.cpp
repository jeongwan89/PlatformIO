#include <Arduino.h>

#include "kjwMotor.h"

const int speedPin = 9; // PWM 핀
const int directionPin = 8; // 디지털 핀

kjwMotor motor(speedPin, directionPin);

void setup()
{
    Serial.begin(9600);
    Serial.println("Motor Test Start");

    // 초기 속도와 방향 설정
    motor.Speed(50); // 속도 50%
    motor.Dir(CW); // 시계 방향
}

void loop()
{
    // 속도 테스트
    for (int speed = 0; speed <= 100; speed += 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");
    delay(2000);

    // 다시 속도 테스트
    for (int speed = 100; speed >= 0; speed -= 10)
    {
        motor.Speed(speed);
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(1000);
    }

    // 방향 전환 테스트
    motor.ToggleDirection();
    Serial.println("Direction Toggled");
    delay(2000);
}
