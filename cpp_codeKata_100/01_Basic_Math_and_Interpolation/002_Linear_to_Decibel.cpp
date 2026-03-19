#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 002: Linear to Decibel Conversion (線性增益轉分貝)
 * ==============================================================================
 *
 * [說明]
 * 當我們要把訊號強度顯示在 UI 的長條圖 (Meter) 上，或是計算壓縮器 (Compressor)
 * 的 Gain Reduction 時，需要將聲音的線性振幅轉換回分貝。
 *
 * [公式]
 * dB = 20 * log10(linear)
 *
 * [警告！程式崩潰陷阱]
 * 如果聲音是絕對靜音 (linear = 0.0f)，log10(0) 在數學上無意義，
 * 程式會產生 -Infinity (負無限大)。一但在這之後乘以任何數字，整個聲音引擎會當機 (NaN)。
 *
 * [任務]
 * 實作 linearToDb 函數。
 * [防呆機制] 如果輸入的 linear 小於特定的閾值 (例如 0.00001f)，直接回傳 -100.0f。
 */

float linearToDb(float linear)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // (提示：C++ 的 log10 函數是 std::log10)

    if (linear < 0.00001f)
    {
        return -100.0f;
    }

    float dB = 20.0f * std::log10(linear);
    return dB;
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 1.0 應該是 0 dB -> ";
    if (isClose(linearToDb(1.0f), 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << linearToDb(1.0f) << ")\n";

    std::cout << "[測試 2] 0.5 應該約等於 -6.02 dB -> ";
    if (isClose(linearToDb(0.5f), -6.020f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << linearToDb(0.5f) << ")\n";

    std::cout << "[測試 3] 極小值防呆 (0.0 應該回傳 -100.0) -> ";
    if (isClose(linearToDb(0.0f), -100.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (處理 0.0 時沒有防護，結果為: " << linearToDb(0.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 002 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 002 測試開始 ===\n";
    runTests();
    return 0;
}
