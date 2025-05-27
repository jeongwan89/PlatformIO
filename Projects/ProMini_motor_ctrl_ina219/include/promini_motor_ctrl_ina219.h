#ifndef MY_PROMINI_MOTOR_CTRL_INA219_H
#define MY_PROMINI_MOTOR_CTRL_INA219_H

#include <Arduino.h>

#define SPEEDPIN 9 // PWM 핀
#define DIRECTIONPIN 8 // 디지털 핀
#define ANALOGSPEEDPIN A0 // 볼륨
#define CLK 4 // TM1637 CLK 핀
#define DIO 5 // TM1637 DIO 핀
#define TOGGLESW 7
#define TACTICALSW 6
#define I2C_ADDRESS 0x40


//! @file promini_motor_ctrl_ina219.h
//! @brief Promini Motor Control with INA219 Sensor
//! @details This file contains the definitions and functions for controlling a motor using a Promini board and INA219 sensor
// sensor 초기화
void ina219_init(INA219_WE  &ina219) 
{
    if (!ina219.init()) {
        Serial.println("Failed to find INA219 chip. Check wiring!");
        while (1) {
            delay(10); // 무한 대기
        }
    }
    ina219.setShuntSizeInOhms(0.1); // 션트 저항 값 설정 (0.1옴)
}

#endif // MY_PROMINI_MOTOR_CTRL_INA219
// End of file
