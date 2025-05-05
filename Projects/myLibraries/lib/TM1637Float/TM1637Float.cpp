/**
 * TM1637Float.cpp - TM1637 디스플레이용 부동 소수점 표시 라이브러리 구현
 */

#include "TM1637Float.h"

bool TM1637Float::displayFloat(float value, int decimalPos) {
    if (value < -99.9 || value > 999.9 || decimalPos < 0 || decimalPos > 3) {
        return false; // 범위를 초과하면 false 반환
    }

    int scaledValue = static_cast<int>(value * pow(10, decimalPos)); // 소수점 위치에 따라 값 스케일링
    uint8_t digits[4] = {0};

    for (int i = 3; i >= 0; --i) {
        digits[i] = encodeDigit(scaledValue % 10);
        scaledValue /= 10;
    }

    if (value < 0) {
        digits[0] = SEG_G; // 음수 기호
    }

    // 소수점 추가
    digits[3 - decimalPos] |= DOT;

    setSegments(digits); // TM1637Display의 setSegments 호출
    return true;
}

bool TM1637Float::displayTemperature(float temperature) {
    if (temperature < -9.9 || temperature > 99.9) {
        return false; // 범위를 초과하면 false 반환
    }

    int scaledTemp = static_cast<int>(temperature * 10); // 소수점 1자리 스케일링
    uint8_t digits[4] = {0};

    for (int i = 3; i >= 0; --i) {
        digits[i] = scaledTemp % 10;
        scaledTemp /= 10;
    }

    if (temperature < 0) {
        digits[0] = SEG_G; // 음수 기호
    }

    // 소수점 추가
    digits[2] |= DOT;

    setSegments(digits); // TM1637Display의 setSegments 호출
    return true;
}

void TM1637Float::displayTime(int hours, int minutes) {
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        return; // 유효하지 않은 시간은 표시하지 않음
    }

    uint8_t digits[4] = {
        static_cast<uint8_t>(hours / 10),
        static_cast<uint8_t>(hours % 10),
        static_cast<uint8_t>(minutes / 10),
        static_cast<uint8_t>(minutes % 10)
    };

    // 시간과 분 사이에 소수점 추가
    digits[1] |= DOT;

    setSegments(digits); // TM1637Display의 setSegments 호출
}