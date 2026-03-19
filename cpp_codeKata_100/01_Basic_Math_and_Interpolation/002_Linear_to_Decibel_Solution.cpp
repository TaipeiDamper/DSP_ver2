#include <iostream>
#include <cmath>

/*
 * ==============================================================================
 * [解答] KATA 002: Linear to Decibel Conversion
 * ==============================================================================
 * 
 * 【教學筆記】
 * 我們在做 DSP 時，除以 0 或 log(0) 是「不可容忍的天條」，因為它會產生
 * 擴散性的 NaN (Not a Number) 病毒，瞬間把整個迴圈裡的 Buffer 全毀，
 * 喇叭會發出可怕爆音然後徹底無聲。所以「邊界檢查」是每次呼叫危險函數前必做的動作。
 */

float linearToDb(float linear) {
    // 1. 防呆保護：若數值小於極小值 (10^-5 剛好對應 -100dB)
    if (linear <= 0.00001f) {
        return -100.0f;
    }

    // 2. 正常轉換
    return 20.0f * std::log10(linear);
}

void runTests() {
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    if (isClose(linearToDb(1.0f), 0.0f) && 
        isClose(linearToDb(0.5f), -6.020f) && 
        isClose(linearToDb(0.0f), -100.0f)) {
        std::cout << "✅ 解答版測試通過！\n";
    }
}

int main() {
    runTests();
    return 0;
}
