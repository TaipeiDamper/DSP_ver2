#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 021: One-Pole Smoother / Lowpass Filter (單極點平滑器)
 * ==============================================================================
 *
 * [說明]
 * 當你轉動 UI 上的旋鈕時，如果數值瞬間改變，聲音會出現「喀喀」的爆音 (Zipper Noise)。
 *為了解決這個問題，我們需要一個「平滑器 (Smoother)」，讓數值像彈簧一樣慢慢追上目標。
 *
 * 在 DSP 裡，最常用的平滑器就是「單極點低通濾波器 (One-Pole Lowpass Filter)」。
 *
 * [方塊圖 / 訊號流]
 *
 *         (input - z1)           * coeff
 * input ───────> ( + ) ────────────> ( * ) ───────> ( + ) ────> output
 *                  ^                                  ^
 *                  │                                  │
 *                 (-)                                 │
 *                  │                                  │
 *                  └───────── [ z1 (delay) ] <────────┘
 *
 * 數學式 (Incremental Form，你之前實作 Compressor Envelope 時用過這招！)：
 * output = z1 + (input - z1) * coeff
 * 然後記得要更新狀態：z1 = output
 *
 * [任務]
 * 實作 OnePoleSmoother 的 processSample。
 */

class OnePoleSmoother
{
private:
    float z1 = 0.0f; // 記憶上一個輸出的狀態 (Delay 1 sample)

public:
    float coeff = 0.1f; // 平滑係數 (接近 0 表示動作很慢，接近 1 表示瞬間到達)

    void reset()
    {
        z1 = 0.0f;
    }

    float processSample(float input)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 計算新的輸出
        float output = z1 + (input - z1) * coeff;
        // 2. 更新狀態 z1
        z1 = output;
        // 3. 回傳輸出

        return output; // 請修正
        // ------------------------------------------------------------------
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    OnePoleSmoother smoother;
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    smoother.coeff = 0.5f; // 每次前進剩餘距離的一半

    // 目標值瞬間變成 1.0
    float out1 = smoother.processSample(1.0f);
    std::cout << "[測試 1] 第一步追蹤 -> ";
    if (isClose(out1, 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out1 << ")\n";

    float out2 = smoother.processSample(1.0f);
    std::cout << "[測試 2] 第二步追蹤 -> ";
    // 剩下 0.5 的距離，走一半是 0.25 -> 總共 0.75
    if (isClose(out2, 0.75f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out2 << ")\n";

    float out3 = smoother.processSample(1.0f);
    std::cout << "[測試 3] 第三步追蹤 -> ";
    // 0.75 到 1.0 的一半是 0.125 -> 總共 0.875
    if (isClose(out3, 0.875f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out3 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 021 挑戰成功！Sprint 3 的好開始！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 021 測試開始 ===\n";
    runTests();
    return 0;
}
