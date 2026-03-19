#include <iostream>
#include <cmath>
#include <cassert>

/*
 * ==============================================================================
 * [解答] KATA 001: Decibel to Linear Conversion
 * ==============================================================================
 * 
 * 【教學筆記】
 * 1. 為什麼要防呆 (`db <= -100.0f`)？
 *    因為 10^(-100/20) 是一個非常小但大於 0 的浮點數 (Denormalized number)。
 *    在某些舊款 CPU 處理極小浮點數時，效能會暴跌百倍！這叫做 "Denormal issue"。
 *    直接歸零是最安全且符合人耳聽覺的作法。
 * 
 * 2. 為什麼用 `std::pow(10.0f, ...)` 而不是 `pow`？
 *    C++11 之後，寫明 `.0f` 可以強制讓編譯器使用單精度 (float) 版本的 powf_，
 *    這在一次處理幾萬個採樣點時，速度會比雙精度 (double) 快很多。
 */

float dbToLinear(float db) {
    // 1. 極小值防護 (Denormal 防護與絕對靜音)
    if (db <= -100.0f) {
        return 0.0f;
    }

    // 2. 數學公式: 10^(dB/20)
    // 備註：使用 10.0f 確保是單精度運算
    return std::pow(10.0f, db / 20.0f);
}

// 測試區塊 (與題目相同)
void runTests() {
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    if (isClose(dbToLinear(0.0f), 1.0f) && 
        isClose(dbToLinear(6.0f), 1.995f) && 
        isClose(dbToLinear(-6.0f), 0.501f) && 
        dbToLinear(-101.0f) == 0.0f) {
        std::cout << "✅ 解答版測試通過！\n";
    }
}

int main() {
    runTests();
    return 0;
}
