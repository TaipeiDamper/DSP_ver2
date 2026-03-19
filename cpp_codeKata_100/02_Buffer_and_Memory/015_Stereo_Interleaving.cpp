#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 015: Stereo Interleaving (立體聲交錯排列)
 * ==============================================================================
 *
 * [說明]
 * 音訊資料在記憶體中有兩種常見的排列方式：
 * 1. 非交錯 (De-interleaved) / Planar：
 *    Left Channel:  [L1, L2, L3, L4]
 *    Right Channel: [R1, R2, R3, R4]
 *    (這是大部分 DAW 和 DSP 引擎內部處理運算時最喜歡的格式，因為可以連續處理單一聲道)
 *
 * 2. 交錯 (Interleaved)：
 *    [L1, R1, L2, R2, L3, R3, L4, R4]
 *    (這是 WAV 檔案儲存以及聲音介面 (Audio API) 輸出的標準格式)
 *
 * [任務]
 * 把兩個獨立的 Left 和 Right Buffer，合併成一個交錯排列的 Out Buffer。
 * 假設 Left 和 Right 長度相同，而且 Out Buffer 的長度已經是傳入的 Left 的 2 倍大。
 */

void interleave(const std::vector<float> &leftBuffer, const std::vector<float> &rightBuffer,
                std::vector<float> &interleavedOut)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示：利用 out[i * 2] 和 out[i * 2 + 1] 來儲存資料。

        for (int i = 0; i < leftBuffer.size(); i++)
        {
            interleavedOut[i * 2] = leftBuffer[i];
            interleavedOut[i * 2 + 1] = rightBuffer[i];
        }

    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> left = {1.0f, 2.0f, 3.0f};
    std::vector<float> right = {-1.0f, -2.0f, -3.0f};
    std::vector<float> out(6, 0.0f); // 預先分配了 6 個空間

    int passed = 0;

    interleave(left, right, out);

    std::cout << "[測試 1] 第一組樣本順序 (L1, R1) -> ";
    if (out[0] == 1.0f && out[1] == -1.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out[0] << ", " << out[1] << ")\n";

    std::cout << "[測試 2] 第二組樣本順序 (L2, R2) -> ";
    if (out[2] == 2.0f && out[3] == -2.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out[2] << ", " << out[3] << ")\n";

    std::cout << "[測試 3] 第三組樣本順序 (L3, R3) -> ";
    if (out[4] == 3.0f && out[5] == -3.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out[4] << ", " << out[5] << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 015 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 015 測試開始 ===\n";
    runTests();
    return 0;
}
