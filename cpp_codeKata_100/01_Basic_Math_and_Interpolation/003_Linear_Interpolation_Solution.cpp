#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * [解答] KATA 003: Linear Interpolation (Lerp)
 * ==============================================================================
 *
 * 【教學筆記】
 * 常見有兩種寫法：
 * 寫法一： start + fraction * (end - start)
 * 這個寫法在絕大多數情況下沒問題，但有時會導致「即使 fraction=1.0，因為浮點誤差，結果不完全等於 end」。
 *
 * 寫法二： start * (1 - fraction) + end * fraction
 * 這種寫法更加對稱，但多了一次乘法運算。C++ std::lerp (C++20 新增) 內部會處理各種邊界極端狀況。
 *
 * 在即時音訊運算上，通常我們用「寫法一」，因為快。這也是傳統 DSP 書上的教法。
 */

float lerp(float start, float end, float fraction)
{
    // DSP 極速版 (少一次乘法)
    return start + fraction * (end - start);
}

void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    if (isClose(lerp(10.0f, 20.0f, 0.0f), 10.0f) && isClose(lerp(10.0f, 20.0f, 1.0f), 20.0f) &&
        isClose(lerp(10.0f, 20.0f, 0.5f), 15.0f) && isClose(lerp(-1.0f, 1.0f, 0.75f), 0.5f))
    {
        std::cout << "✅ 解答版測試通過！\n";
    }
}

int main()
{
    runTests();
    return 0;
}
