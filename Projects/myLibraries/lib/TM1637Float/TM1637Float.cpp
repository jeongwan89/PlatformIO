/**
 * TM1637Float.cpp - TM1637 디스플레이용 부동 소수점 표시 라이브러리 구현
 */

 #include "TM1637Float.h"

 bool TM1637Float::displayFloat(TM1637Display &display, float value, int decimalPos) {
   // 값이 범위를 벗어나면 에러 표시하고 false 반환
   if (value > 999.9 || value < -99.9) {
     uint8_t errorData[] = {
       display.encodeDigit(14),  // E
       display.encodeDigit(11),  // r
       display.encodeDigit(11),  // r
       display.encodeDigit(0)    // 0
     };
     display.setSegments(errorData);
     return false;
   }
   
   // 값이 음수인지 확인
   bool negative = value < 0;
   if (negative) {
     value = -value;
   }
   
   // 소수점 이하 자릿수에 맞게 값 조정
   int multiplier = 1;
   for (int i = 0; i < decimalPos; i++) {
     multiplier *= 10;
   }
   
   // 정수부와 소수부로 분리
   int intPart = (int)value;
   int decPart = (int)((value - intPart) * multiplier + 0.5);  // 반올림
   
   // 원하는 소수점 위치에 따라 값 조정
   int displayValue = intPart * multiplier + decPart;
   
   // 세그먼트 배열 준비
   uint8_t segments[4] = {0, 0, 0, 0};
   
   // 소수점 위치가 디스플레이 범위 내에 있는지 확인
   if (decimalPos >= 1 && decimalPos <= 3) {
     // 각 자리 숫자 계산
     for (int i = 3; i >= 0; i--) {
       if (i == 0 && negative) {
         segments[i] = 0b01000000;  // 음수 부호
       } else {
         segments[i] = display.encodeDigit(displayValue % 10);
         displayValue /= 10;
       }
     }
     
     // 소수점 추가
     segments[3 - decimalPos] |= DOT;
   }
   
   // 디스플레이에 표시
   display.setSegments(segments);
   return true;
 }
 
 bool TM1637Float::displayTemperature(TM1637Display &display, float temperature) {
   // 온도 값이 범위를 벗어나면 에러 표시
   if (temperature > 99.9 || temperature < -9.9) {
     uint8_t errorData[] = {
       display.encodeDigit(14),  // E
       display.encodeDigit(11),  // r
       display.encodeDigit(11),  // r
       display.encodeDigit(0)    // 0
     };
     display.setSegments(errorData);
     return false;
   }
   
   // 온도는 소수점 1자리로 표시
   return displayFloat(display, temperature, 1);
 }
 
 void TM1637Float::displayTime(TM1637Display &display, int hours, int minutes) {
   // 시간과 분이 유효한 범위 내에 있는지 확인
   hours = constrain(hours, 0, 23);
   minutes = constrain(minutes, 0, 59);
   
   // 세그먼트 배열 준비
   uint8_t segments[4] = {0, 0, 0, 0};
   
   // 시간 표시 (상위 2자리)
   segments[0] = display.encodeDigit(hours / 10);  // 시간 십의 자리
   segments[1] = display.encodeDigit(hours % 10);  // 시간 일의 자리
   
   // 시간과 분 사이에 소수점 추가
   segments[1] |= DOT;
   
   // 분 표시 (하위 2자리)
   segments[2] = display.encodeDigit(minutes / 10);  // 분 십의 자리
   segments[3] = display.encodeDigit(minutes % 10);  // 분 일의 자리
   
   // 디스플레이에 표시
   display.setSegments(segments);
 }