/**
 * TM1637Float.h - TM1637 디스플레이용 부동 소수점 표시 라이브러리
 * TM1637 4자리 7세그먼트 디스플레이에서 소수점이 있는 실수를 표시할 수 있게 해주는 라이브러리입니다.
 */

 #ifndef TM1637FLOAT_H
 #define TM1637FLOAT_H
 
 #include <Arduino.h>
 #include <TM1637Display.h>
 
 class TM1637Float {
   private:
     static const uint8_t DOT = 0b10000000;  // 소수점 비트 (세그먼트 비트맵에서 소수점은 비트 7)
     
   public:
     /**
      * 부동 소수점 값을 TM1637 디스플레이에 표시
      * 
      * @param display TM1637Display 객체 레퍼런스
      * @param value 표시할 실수 값 (-99.9 ~ 999.9 범위 내)
      * @param decimalPos 소수점 위치 (1=소수점 1자리, 2=소수점 2자리, 3=소수점 3자리)
      * @return 표시 성공 여부 (true=성공, false=범위 초과)
      */
     static bool displayFloat(TM1637Display &display, float value, int decimalPos);
     
     /**
      * 온도 값을 TM1637 디스플레이에 특화된 형태로 표시
      * 25.5도는 25.5, -9.5도는 -9.5 형태로 표시
      * 
      * @param display TM1637Display 객체 레퍼런스
      * @param temperature 표시할 온도 값 (-9.9 ~ 99.9 범위 내)
      * @return 표시 성공 여부 (true=성공, false=범위 초과)
      */
     static bool displayTemperature(TM1637Display &display, float temperature);
     
     /**
      * 시간을 TM1637 디스플레이에 표시 (HH.MM 형식)
      * 콜론 대신 소수점을 사용하여 시간과 분 사이를 구분
      * 
      * @param display TM1637Display 객체 레퍼런스
      * @param hours 시간 (0-23)
      * @param minutes 분 (0-59)
      */
     static void displayTime(TM1637Display &display, int hours, int minutes);
 };
 
 #endif
 