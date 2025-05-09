#include <Arduino.h>
#include <TM1637Display.h>
#include <TM1637Float.h>
#include <kjwMotor.h>
#include <Wire.h>
#include <INA219_WE.h>
#include "promini_motor_ctrl_ina219.h"

// function prototypes
void ina219_init(void);

kjwMotor motor(SPEEDPIN, DIRECTIONPIN);
TM1637Float display(CLK, DIO);
INA219_WE ina219(I2C_ADDRESS);

void setup() {
    
    display.setBrightness(7, true);
    pinMode(ANALOGSPEEDPIN, INPUT);
    pinMode(TOGGLESW, INPUT_PULLUP);
    pinMode(TACTICALSW, INPUT_PULLUP);
    analogWrite(SPEEDPIN, 0);
    
    ina219_init(); // sensor 초기화
    Serial.begin(115200);
}

void loop() {
    int motorState = digitalRead(TOGGLESW);
    if (motorState == HIGH) {
        motor.Speed(0);
        Serial.println("Stop switch is pressed. Motor stopped.");
        return;
    }
    motor.Speed(map(analogRead(ANALOGSPEEDPIN), 0, 1023, 0, 100));
    static float current_mA = 0.0;
    current_mA = ina219.getCurrent_mA();
    Serial.print("Current: "); Serial.print(current_mA); Serial.println("mA");
    display.displayFloat(current_mA, 0);    
}

void ina219_init() {
    // INA219 초기화
    if (!ina219.init()) {
        Serial.println("Failed to find INA219 chip. Check wiring!");
        while (1) {
            delay(10); // 무한 대기
        }
    }
    ina219.setShuntSizeInOhms(0.1); // 션트 저항 값 설정 (0.1옴)
}