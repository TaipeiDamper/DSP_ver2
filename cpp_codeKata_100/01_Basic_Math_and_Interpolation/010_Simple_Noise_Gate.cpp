#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 010: Simple Noise Gate (簡單雜訊門)
 * ==============================================================================
 *
 * [說明]
 * Noise Gate 是動態處理中最基本的工具。它的作用是：
 * 當聲音太小（低於某個 Threshold）時，把聲音關掉，以消除背景雜訊。
 *
 * [觀念]
 * 這是一個非黑即白（Hard Gate）的版本：
 * - 如果 abs(input) > threshold，則 output = input (門打開)
 * - 如果 abs(input) <= threshold，則 output = 0.0 (門關閉)
 *
 * [任務]
 * 實作 simpleGate 函數。
 * 雖然我們在 KATA 006 學過 fastAbs，但這裡你可以直接使用 std::abs。
 */

float simpleGate(float input, float threshold)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：

    if (std::abs(input) > threshold)
    {
        return input;
    }

    return 0.0f; // 請修正
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 高於閾值 (0.5, thres 0.1) -> ";
    if (isClose(simpleGate(0.5f, 0.1f), 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << simpleGate(0.5f, 0.1f) << ")\n";

    std::cout << "[測試 2] 低於閾值 (0.05, thres 0.1) -> ";
    if (isClose(simpleGate(0.05f, 0.1f), 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << simpleGate(0.05f, 0.1f) << ")\n";

    std::cout << "[測試 3] 負數且高於閾值 (-0.5, thres 0.1) -> ";
    if (isClose(simpleGate(-0.5f, 0.1f), -0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << simpleGate(-0.5f, 0.1f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 010 挑戰成功！Sprint 1 圓滿達成！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 010 測試開始 ===\n";
    runTests();
    return 0;
}
