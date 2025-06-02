#include <Arduino.h>
#include <TM1637Display.h>
#include <TM1637Float.h>
#include <kjwMotor.h>
#include <Wire.h>
#include <INA219_WE.h>
#include "promini_motor_ctrl_ina219.h"

kjwMotor motor(SPEEDPIN, DIRECTIONPIN);
TM1637Float display(CLK, DIO);
INA219_WE ina219(I2C_ADDRESS);

void setup() {
    
    display.setBrightness(7, true);
    pinMode(ANALOGSPEEDPIN, INPUT);
    pinMode(TOGGLESW, INPUT_PULLUP);
    pinMode(TACTICALSW, INPUT_PULLUP);
    analogWrite(SPEEDPIN, 0);
    
    ina219_init(ina219); // sensor 초기화
    Serial.begin(57600);
}

void loop() {
    // 모터 긴급 정지 스위치가 눌림?
    int motorState = digitalRead(TOGGLESW);
    if (motorState == HIGH) {
        motor.Speed(0);
        Serial.println("Stop switch is pressed. Motor stopped.");
        return;
    }
    // 방향 push button이 눌림?
    int tacticalState = digitalRead(TACTICALSW);
    if (tacticalState == LOW) {
        motor.softToggleDirection();
        Serial.println("Tactical switch pressed. Motor direction toggled.");
        delay(500); // Debounce delay
        return;
    }
    // 긴급 처리가 없으면 모터 동작
    motor.Speed(map(analogRead(ANALOGSPEEDPIN), 0, 1023, 0, 100));
    static float current_mA = 0.0;
    current_mA = ina219.getCurrent_mA();
    Serial.print("Current: "); Serial.print(current_mA); Serial.println("mA");
    display.displayFloat(current_mA, 0);    
}

