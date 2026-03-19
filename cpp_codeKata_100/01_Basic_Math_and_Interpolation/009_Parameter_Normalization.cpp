#include <algorithm> // 為了 std::clamp
#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 009: Parameter Normalization (參數映射 / 歸一化)
 * ==============================================================================
 *
 * [說明]
 * 在音訊軟體中，UI 的旋鈕通常給出的數值範圍是 0.0 到 1.0 (歸一化數值)。
 * 但實際的 DSP 參數可能完全不同，例如：
 * - 頻率 (Frequency)：20Hz 到 20000Hz。
 * - 增益 (Gain)：-60dB 到 12dB。
 *
 * [觀念]
 * 我們需要一個公式把 normalizedValue (0~1) 映射到 [min, max] 範圍。
 * 這其實就是 KATA 003: Lerp 的直覺應用。
 *
 * 公式：
 * targetValue = min + normalizedValue * (max - min)
 *
 * [任務]
 * 實作 mapLinear 函數，並處理基本的超出範圍保護 (使用 std::clamp 確保傳入值在 0~1 之間)。
 */

float mapLinear(float normalizedValue, float min, float max)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 1. 先把 normalizedValue 限制在 0.0 ~ 1.0
    // 2. 套用映射公式並回傳
    normalizedValue = std::clamp(normalizedValue, 0.0f, 1.0f);

    return min + normalizedValue * (max - min); // 請修正
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 中點映射 (0.5 映射到 100~200) -> ";
    if (isClose(mapLinear(0.5f, 100.0f, 200.0f), 150.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << mapLinear(0.5f, 100.0f, 200.0f) << ")\n";

    std::cout << "[測試 2] 邊界點映射 (0.0 映射到 20~20000) -> ";
    if (isClose(mapLinear(0.0f, 20.0f, 20000.0f), 20.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << mapLinear(0.0f, 20.0f, 20000.0f) << ")\n";

    std::cout << "[測試 3] 超出範圍保護 (1.5 應該被當作 1.0) -> ";
    if (isClose(mapLinear(1.5f, 0.0f, 100.0f), 100.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << mapLinear(1.5f, 0.0f, 100.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 009 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 009 測試開始 ===\n";
    runTests();
    return 0;
}
