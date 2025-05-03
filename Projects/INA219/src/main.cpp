#define DEBUG

#include <Arduino.h>

#include <Wire.h>
#include <INA219_WE.h>
#define INA219_ADDRESS 0x40
INA219_WE ina219(INA219_ADDRESS);

#include <TM1637Display.h>
#define CLK 10
#define DIO 11
TM1637Display display(CLK, DIO);
// This is a test program for the TM1637 7-segment display

#include <TM1637Float.h>
// This is a test program for the TM1637 7-segment display
TM1637Float tm1637Float;

void setup() {
  Serial.begin(115200);
  #ifdef DEBUG
  Serial.println("Debug mode enabled");
  #endif
  Wire.begin();
  #ifdef DEBUG
  Serial.println("Wire library initialized");
  #endif
  
  if(ina219.init()) {
    Serial.println("INA219 initialized successfully");
  } else {
    Serial.println("INA219 initialization failed");
    while(1); // Stop execution if INA219 initialization fails
  } 
  Serial.println("INA219 Current Sensor Example Sketch - Continuous Mode");

  ina219.setADCMode(INA219_ADC_MODE::BIT_MODE_12);
  ina219.setMeasureMode(INA219_MEASURE_MODE::CONTINUOUS);
  ina219.setPGain(INA219_PGAIN::PG_320);
  ina219.setBusRange(INA219_BUS_RANGE::BRNG_32);
  ina219.setShuntSizeInOhms(0.1); // Set shunt resistor value
  ina219.startSingleMeasurement();
  
  display.setBrightness(0x0f); // Set brightness to maximum
  delay(2000); // Wait for a while before displaying the next value
}

void loop() {
  // put your main code here, to run repeatedly:
  float current = ina219.getCurrent_mA();
  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" mA");
  tm1637Float.displayFloat(display, current, 1); // Display current on TM1637
  // display.showNumberDec((int)current, false, 4, 0); // Display current on TM1637
  delay(1000); // Update every second
  if (ina219.getOverflow()) {
    Serial.println("INA219 overflow detected!");
    // display.showNumberDec(9999, false, 4, 0); // Display overflow on TM1637
    return; // Exit the loop if overflow is detected
  }
  if (ina219.getConversionReady()) {
    float busVoltage = ina219.getBusVoltage_V();
    Serial.print("Bus Voltage: ");
    Serial.print(busVoltage);
    Serial.println(" V");
  }
  delay(1000); // Update every second 
}
