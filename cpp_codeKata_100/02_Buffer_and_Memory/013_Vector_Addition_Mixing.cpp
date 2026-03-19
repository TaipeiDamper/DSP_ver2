#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 013: Vector Addition / Mixing (向量相加與混音)
 * ==============================================================================
 *
 * [說明]
 * 在音訊處理中，「混音 (Mixing)」最基本的行為就是將兩個訊號相加。
 * 想像一下，如果你有兩個樂器的聲音 Buffer，你要把它們合併成一個輸出的聲音，
 * 本質上就是將對應位置的數字相加。
 *
 * [觀念]
 * 給定兩個輸入 Buffer (inA, inB) 和一個輸出 Buffer (out)。
 * out[i] = inA[i] + inB[i]
 *
 * [任務]
 * 實作 mixBuffers 函數。
 * 請注意，通常也要考慮 Buffer 大小是否一致，但在這個練習中我們假設它們都一樣長。
 */

void mixBuffers(const std::vector<float> &inA, const std::vector<float> &inB, std::vector<float> &out)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 使用 for 迴圈遍歷所有元素進行相加
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = inA[i] + inB[i];
    }

    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> a = {0.5f, -0.2f, 0.1f};
    std::vector<float> b = {0.1f, 0.4f, 0.5f};
    std::vector<float> result(3, 0.0f);

    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    mixBuffers(a, b, result);

    std::cout << "[測試 1] 第一個樣本 (0.5 + 0.1 = 0.6) -> ";
    if (isClose(result[0], 0.6f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << result[0] << ")\n";

    std::cout << "[測試 2] 第二個樣本 (-0.2 + 0.4 = 0.2) -> ";
    if (isClose(result[1], 0.2f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << result[1] << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 013 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 013 測試開始 ===\n";
    runTests();
    return 0;
}
