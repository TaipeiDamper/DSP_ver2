#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 016: Stereo De-interleaving (立體聲解交錯)
 * ==============================================================================
 *
 * [說明]
 * 這是 KATA 015 的反向操作。當你從硬碟讀取一個 WAV 檔案，或是從音效卡接收到麥克風的錄音時，
 * 預設的格式通常是「交錯排列 (Interleaved)」的： [L1, R1, L2, R2, L3, R3...]
 *
 * 為了方便後續在 DSP 引擎裡對各別聲道做處理（比如只對左聲道放 Delay），
 * 我們必須把它「解開 (De-interleave)」成獨立的兩個 Array。
 *
 * [任務]
 * 實作 deinterleave 函數，將傳入的交錯陣列拆解。
 * 假設 leftBuffer 和 rightBuffer 都已經預先分配好了一半的空間。
 */

void deinterleave(const std::vector<float> &interleavedIn, std::vector<float> &leftBuffer,
                  std::vector<float> &rightBuffer)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    for (int i = 0; i < interleavedIn.size(); i = i + 2)
    {
        leftBuffer[i / 2] = interleavedIn[i];
        rightBuffer[i / 2] = interleavedIn[i + 1];
    }
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> in = {1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};
    std::vector<float> left(3, 0.0f);
    std::vector<float> right(3, 0.0f);

    int passed = 0;

    deinterleave(in, left, right);

    std::cout << "[測試 1] 左聲道提取 -> ";
    if (left[0] == 1.0f && left[1] == 2.0f && left[2] == 3.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果有誤)\n";

    std::cout << "[測試 2] 右聲道提取 -> ";
    if (right[0] == -1.0f && right[1] == -2.0f && right[2] == -3.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果有誤)\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 016 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 016 測試開始 ===\n";
    runTests();
    return 0;
}
