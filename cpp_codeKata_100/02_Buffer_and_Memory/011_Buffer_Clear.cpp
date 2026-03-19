#include <algorithm>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 011: Buffer Clear / Mute (清空緩衝區)
 * ==============================================================================
 *
 * [說明]
 * 在音訊處理中，「靜音 (Mute)」或者是「初始化 Buffer」是極度頻繁的操作。
 * 我們不能只靠 `float buffer[1024]` 就假設它是空的，裡面可能有之前的殘留數據。
 * 此外，如果某個效果器被關掉，我們必須把輸出 Buffer 清空，否則會發出恐怖的噪音。
 *
 * [觀念]
 * 有幾種方式可以清空陣列：
 * 1. 迴圈跑一遍 (慢)。
 * 2. std::fill (標準做法，易讀且快)。
 * 3. memset (最底層，但對非純資料類型不安全)。
 *
 * [任務]
 * 實作 clearBuffer 函數，將傳入的 vector 內容全部填為 0.0f。
 */

void clearBuffer(std::vector<float> &buffer)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示：使用 std::fill(開始指標, 結束指標, 填入值)
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> myBuffer = {0.1f, -0.5f, 1.0f, 0.9f, -0.1f};
    int passed = 0;

    std::cout << "[測試 1] 清空前不為零 -> ";
    bool allZeroBefore = true;
    for (float f : myBuffer)
        if (f != 0.0f)
            allZeroBefore = false;
    if (!allZeroBefore)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (Buffer 一開始就是空的？)\n";

    std::cout << "[測試 2] 執行 clearBuffer -> ";
    clearBuffer(myBuffer);
    bool allZeroAfter = true;
    for (float f : myBuffer)
        if (f != 0.0f)
            allZeroAfter = false;
    if (allZeroAfter)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
    {
        std::cout << "FAIL (結果仍有殘留: ";
        for (float f : myBuffer)
            std::cout << f << " ";
        std::cout << ")\n";
    }

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 011 挑戰成功！Sprint 2 正式啟航！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 011 測試開始 ===\n";
    runTests();
    return 0;
}
