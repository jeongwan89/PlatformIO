#include <Arduino.h>

#include <ACS712Sensor.h>
#include <TM1637Display.h>
#include <TM1637Float.h>

#define CLK 10
#define DIO 11
#define ACS712_PIN A2


ACS712Sensor ACS(ACS712_PIN, "20A"); // 100mV/A (ACS712-20A)

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

TM1637Display display(CLK, DIO);
TM1637Float tm1637Float;
void setup() {
    Serial.begin(115200);
    display.setBrightness(0x0f);
}

void loop() {
    float mA = ACS.readCurrent();
    // float A = mA / 1000;
    Serial.print("current: "); Serial.print(mA); Serial.println(" mA");
    tm1637Float.displayFloat(display, mA, 1);
    delay(100);
}
