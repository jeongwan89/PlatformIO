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

#endif // MY_PROMINI_MOTOR_CTRL_INA219
// End of file