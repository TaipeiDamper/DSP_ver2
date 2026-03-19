#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 008: Soft Clipper (軟剪裁 / 飽和器)
 * ==============================================================================
 *
 * [說明]
 * Hard Clipper (KATA 007) 雖然簡單，但它的轉折點非常生硬，會產生很多刺耳的高頻諧波。
 * 在模擬類比電路（如真空管、錄音帶）時，我們會使用「軟剪裁」。
 * 它的特點是：當訊號接近上限時，會逐漸彎曲，而不是直接切斷。
 *
 * [觀念]
 * 最經典的軟剪裁數學函數是雙曲正切函數：std::tanh(x)。
 * - 當 x 很小時，tanh(x) 幾乎等於 x (線性)。
 * - 當 x 變大時，tanh(x) 會平滑地趨近於 1.0 或 -1.0。
 *
 * [任務]
 * 實作 softClip 函數。
 */

float softClip(float input)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示：直接回傳 std::tanh 的結果即可。

    return std::tanh(input); // 請修正
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.01f; };
    int passed = 0;

    std::cout << "[測試 1] 小訊號保持線性 (0.1) -> ";
    // tanh(0.1) 應該約等於 0.0996
    if (isClose(softClip(0.1f), 0.0996f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << softClip(0.1f) << ")\n";

    std::cout << "[測試 2] 大訊號被壓縮 (2.0) -> ";
    // tanh(2.0) 應該約等於 0.964
    if (isClose(softClip(2.0f), 0.964f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << softClip(2.0f) << ")\n";

    std::cout << "[測試 3] 極大訊號趨近 1.0 (10.0) -> ";
    if (softClip(10.0f) > 0.99f && softClip(10.0f) <= 1.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << softClip(10.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 008 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 008 測試開始 ===\n";
    runTests();
    return 0;
}
