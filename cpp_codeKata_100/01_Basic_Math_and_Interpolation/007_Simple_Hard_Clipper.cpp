#include <algorithm> // 為了 std::clamp
#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 007: Simple Hard Clipper (硬剪裁 / 破音基礎)
 * ==============================================================================
 *
 * [說明]
 * 當音訊訊號超過範圍 (通常是 -1.0 到 1.0) 時，硬體或數位系統會發生「削波」。
 * 這是數位失真 (Digital Distortion) 的來源，也是製作 Distortion 效果器的第一步。
 *
 * [觀念]
 * 給定一個輸入值 input，以及上限 threshold。
 * 如果 input 大於 threshold，輸出 threshold。
 * 如果 input 小於 -threshold，輸出 -threshold。
 * 其他情況輸出原本的 input。
 *
 * [任務]
 * 使用 C++17 或以後最優雅的方式實作 hardClip 函數。
 */

float hardClip(float input, float threshold)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示：C++17 提供了一個非常有用的函數叫 std::clamp(value, min, max)
    input = std::clamp(input, -threshold, threshold);
    return input; // 請修正
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.001f; };
    int passed = 0;

    std::cout << "[測試 1] 未超過範圍 (0.5, thres 1.0) -> ";
    if (isClose(hardClip(0.5f, 1.0f), 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << hardClip(0.5f, 1.0f) << ")\n";

    std::cout << "[測試 2] 正向削波 (1.2, thres 1.0) -> ";
    if (isClose(hardClip(1.2f, 1.0f), 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << hardClip(1.2f, 1.0f) << ")\n";

    std::cout << "[測試 3] 負向削波 (-1.5, thres 1.0) -> ";
    if (isClose(hardClip(-1.5f, 1.0f), -1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << hardClip(-1.5f, 1.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 007 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 007 測試開始 ===\n";
    runTests();
    return 0;
}
