#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 005: Pan Pot - Constant Power (等功率平移)
 * ==============================================================================
 *
 * [說明]
 * 在 KATA 004 中，我們使用了線性平移。但線性平移有一個物理缺陷：
 * 當聲音在正中間 (0.5) 時，L 和 R 的 Gain 都是 0.5。
 * 由於能量（功率）是振幅的平方，0.5^2 + 0.5^2 = 0.25 + 0.25 = 0.5。
 * 這意味著中間的總能量只有極左或極右 (1.0^2 = 1.0) 的一半！
 * 聽感上，聲音從左邊移到中間時會覺得「變小聲了」，這稱為 Center Dip。
 *
 * [解決方案]
 * 我們使用正弦 (Sine) 和餘弦 (Cosine) 函數來分配 Gain，使得：
 * (LeftGain)^2 + (RightGain)^2 永遠等於 1.0 (等功率)。
 *
 * [公式]
 * angle = panPosition * (PI / 2)  // 將 0~1 映射到 0~90 度
 * leftGain = cos(angle)
 * rightGain = sin(angle)
 *
 * [任務]
 * 實作 calculateConstantPowerPan 函數。
 * 提示：M_PI 通常定義在 <cmath> 中，如果沒有，可以使用 3.1415926535f。
 */

void calculateConstantPowerPan(float panPosition, float &leftGain, float &rightGain)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    const float PI = 3.1415926535f;

    // 我猜應該是把相位->sin function相關的吧

    leftGain = cos(panPosition * (PI * 0.5f));  // 請修正
    rightGain = sin(panPosition * (PI * 0.5f)); // 請修正

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
    calculateConstantPowerPan(0.0f, L, R);
    if (isClose(L, 1.0f) && isClose(R, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 2] 極右 (1.0) -> ";
    calculateConstantPowerPan(1.0f, L, R);
    if (isClose(L, 0.0f) && isClose(R, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 3] 正中 (0.5) -> ";
    calculateConstantPowerPan(0.5f, L, R);
    // 在 0.5 時，angle = 45度, cos(45) = sin(45) = 1/sqrt(2) ≈ 0.707
    if (isClose(L, 0.7071f) && isClose(R, 0.7071f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: L=" << L << ", R=" << R << ")\n";

    std::cout << "[測試 4] 功率檢查 (0.5) -> ";
    calculateConstantPowerPan(0.5f, L, R);
    float power = (L * L) + (R * R);
    if (isClose(power, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (總功率應該是 1.0, 你的結果: " << power << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 005 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 005 測試開始 ===\n";
    runTests();
    return 0;
}
