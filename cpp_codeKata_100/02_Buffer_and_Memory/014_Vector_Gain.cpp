#include <cmath>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 014: Vector Application of Gain (針對整個陣列套用音量)
 * ==============================================================================
 *
 * [說明]
 * 當你要調整整條音軌的音量時，你會讓 Buffer 裡的每一個樣本都乘以同一個增益值 (Gain)。
 * 這是 DSP 中處理「音量 (Gain)」最常見的操作。
 *
 * [觀念]
 * 給定一個輸入/輸出 Buffer (inOut) 和一個增益值 gain。
 * 運算：inOut[i] = inOut[i] * gain
 *
 * [任務]
 * 實作 applyGain 函數，直接修改傳入的 vector 內容。
 */

void applyGain(std::vector<float> &buffer, float gain)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 遍歷整個 buffer，將每個元素乘以 gain
    for (int i = 0; i < buffer.size(); i++)
    {
        buffer[i] *= gain;
    }
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> buffer = {1.0f, -0.5f, 0.2f};
    float gain = 0.5f;

    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    applyGain(buffer, gain);

    std::cout << "[測試 1] 第一個樣本 (1.0 * 0.5 = 0.5) -> ";
    if (isClose(buffer[0], 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << buffer[0] << ")\n";

    std::cout << "[測試 2] 第二個樣本 (-0.5 * 0.5 = -0.25) -> ";
    if (isClose(buffer[1], -0.25f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << buffer[1] << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 014 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 014 測試開始 ===\n";
    runTests();
    return 0;
}
