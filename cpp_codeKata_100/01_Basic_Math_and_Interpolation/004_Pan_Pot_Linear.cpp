#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 004: Pan Pot - Linear (線性左右平移)
 * ==============================================================================
 *
 * [說明]
 * 當我們想要把單聲道 (Mono) 的聲音放置在立體聲 (Stereo) 音場中的某個位置時，
 * 我們需要一個 Panner (平移器 / 聲像控制器)。
 * 這是最基本的「線性分配法」，透過把聲音能量按比例分配給左右聲道，來決定位置。
 *
 * (雖然計算最簡單，但它會有一個小缺陷：當聲音在正中間時聽起來音量會變小，
 * 這個缺陷會在我們下一個 Kata "Constant Power Pan" 解決！)
 *
 * [觀念]
 * 給定一個 panPosition 參數，範圍是 0.0f 到 1.0f。
 * - 0.0f：完全在左邊 (左聲道 Gain = 1.0, 右聲道 Gain = 0.0)
 * - 0.5f：在正中間   (左聲道 Gain = 0.5, 右聲道 Gain = 0.5)
 * - 1.0f：完全在右邊 (左聲道 Gain = 0.0, 右聲道 Gain = 1.0)
 *
 * [任務]
 * 把正確的數值分別寫入 leftGain 和 rightGain 這兩個傳遞址 (Reference) 的變數中。
 */

void calculateLinearPan(float panPosition, float &leftGain, float &rightGain)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // (提示：注意範圍是 0.0 到 1.0，想一下左邊跟右邊增益的加總應該是多少)

    leftGain = 1.0 - panPosition; // 請修正這裡
    rightGain = panPosition;      // 請修正這裡

    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    float L = 0.0f, R = 0.0f;

    std::cout << "[測試 1] 極左 (0.0) -> ";
    calculateLinearPan(0.0f, L, R);
    if (isClose(L, 1.0f) && isClose(R, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 2] 極右 (1.0) -> ";
    calculateLinearPan(1.0f, L, R);
    if (isClose(L, 0.0f) && isClose(R, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 3] 正中 (0.5) -> ";
    calculateLinearPan(0.5f, L, R);
    if (isClose(L, 0.5f) && isClose(R, 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 4] 偏左 (0.25) -> ";
    calculateLinearPan(0.25f, L, R);
    if (isClose(L, 0.75f) && isClose(R, 0.25f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 004 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 004 測試開始 ===\n";
    runTests();
    return 0;
}
