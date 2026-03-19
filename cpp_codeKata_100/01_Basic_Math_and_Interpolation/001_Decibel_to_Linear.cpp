#include <cassert>
#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 001: Decibel to Linear Conversion (分貝轉線性增益)
 * ==============================================================================
 *
 * [說明]
 * 在音訊軟體中，UI 上的音量推桿通常顯示分貝 (dB)，例如 -18dB, 0dB, +6dB。
 * 但傳給電腦底層做乘法運算時，必須是「線性值」 (Linear Gain)。
 * 0 dB = 1.0
 * -6 dB ≒ 0.501   (音量減半)
 * -12 dB ≒ 0.25
 *
 * [公式]
 * linear = 10 ^ (dB / 20)
 *
 * [任務]
 * 實作 dbToLinear 函數。
 * [防呆機制] 當 dB 小於等於 -100.0f 時，直接回傳 0.0f (避免極小浮點數運算，並確保絕對靜音)。
 */

float dbToLinear(float db)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // (提示：C++ 的 10 次方函數是 std::pow(base, exp))
    if (db < -100.0)
    {
        return 0.0f;
    }

    float linear = std::pow(10.0f, db / 20.0f);

    return linear; // 請替換掉這行
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊 (請勿修改，用來驗證你的答案)
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 0 dB 應該是 1.0 -> ";
    if (isClose(dbToLinear(0.0f), 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << dbToLinear(0.0f) << ")\n";

    std::cout << "[測試 2] +6 dB 應該約等於 1.995 -> ";
    if (isClose(dbToLinear(6.0f), 1.995f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << dbToLinear(6.0f) << ")\n";

    std::cout << "[測試 3] -6 dB 應該約等於 0.501 -> ";
    if (isClose(dbToLinear(-6.0f), 0.501f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << dbToLinear(-6.0f) << ")\n";

    std::cout << "[測試 4] 極小值防呆 (-101 dB 應該回傳 0.0) -> ";
    if (dbToLinear(-101.0f) == 0.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << dbToLinear(-101.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 001 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 001 測試開始 ===\n";
    runTests();
    return 0;
}
