#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <Arduino.h>

#define speedPin  9 // PWM 핀
#define directionPin  8 // 디지털 핀
#define analogSpeedPin  A0 // 볼륨
#define imACSPin  A2 // 아날로그 핀 A2
#define moduleACSPin  A1 // 아날로그 핀 A1
#define sensorSensitivity5A  185 // 5A 센서의 감도 (mV/A)
#define sensorSensitivity20A  100 // 20A 센서의 감도 (mV/A)
#define CLK  4 // TM1637 CLK 핀
#define DIO  5 // TM1637 DIO 핀
#define ToggleSW 7
#define TacticalSW 6

#endif // MY_HEADER_H
// End of file