#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 003: Linear Interpolation (Lerp / 線性內插)
 * ==============================================================================
 *
 * [說明]
 * Lerp 是整個 DSP 最重要且無處不在的數學公式！
 * 應用場景：
 * 1. 旋鈕在 100ms 和 200ms 間轉動，算出中間過渡緩慢移動的值 (Parameter Smoothing)。
 * 2. Delay Buffer 在取樣點是 1.5 的位置讀取聲音，必須取 array[1] 和 array[2] 計算出 1.5 該有的漸層值。
 *
 * [觀念]
 * 給定起點 start，終點 end，和一個 0.0 到 1.0 的比例 fraction。
 * fraction = 0.0 時，完全等於 start。
 * fraction = 1.0 時，完全等於 end。
 * fraction = 0.5 時，剛好在兩者正中央。
 *
 * [公式]
 * result = start + fraction * (end - start)
 * 或者 (1 - fraction) * start + fraction * end
 */

float lerp(float start, float end, float fraction)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：

    float result = start + fraction * (end - start);
    return result; // 請替換掉這行
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 從 10 到 20, 比例 0.0 -> ";
    if (isClose(lerp(10.0f, 20.0f, 0.0f), 10.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << lerp(10.0f, 20.0f, 0.0f) << ")\n";

    std::cout << "[測試 2] 從 10 到 20, 比例 1.0 -> ";
    if (isClose(lerp(10.0f, 20.0f, 1.0f), 20.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << lerp(10.0f, 20.0f, 1.0f) << ")\n";

    std::cout << "[測試 3] 從 10 到 20, 比例 0.5 -> ";
    if (isClose(lerp(10.0f, 20.0f, 0.5f), 15.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << lerp(10.0f, 20.0f, 0.5f) << ")\n";

    std::cout << "[測試 4] 從 -1.0 到 1.0 (音訊波形常態), 比例 0.75 -> ";
    if (isClose(lerp(-1.0f, 1.0f, 0.75f), 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (你的結果: " << lerp(-1.0f, 1.0f, 0.75f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 003 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 003 測試開始 ===\n";
    runTests();
    return 0;
}
