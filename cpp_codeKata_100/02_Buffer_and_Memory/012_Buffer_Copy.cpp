#include <algorithm>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 012: Buffer Copy (拷貝音訊數據)
 * ==============================================================================
 *
 * [說明]
 * 將一個 Buffer 的內容複製到另一個 Buffer 是 DSP 鏈 (Processing Chain) 中的家常便飯。
 * 例如：將輸入 Buffer 備份一份，以便之後做 Dry/Wet 混音。
 * 或者是將數據從一個 Effect 傳遞到下一個 Effect。
 *
 * [觀念]
 * 複製資料有幾種常見方法：
 * 1. 迴圈 `for (int i=0; i<size; ++i) dst[i] = src[i];` (基礎但手動)。
 * 2. `std::copy(src_beg, src_end, dst_beg)` (標準做法，易讀且有優化)。
 * 3. `vector1 = vector2` (整門拷貝，但會觸發記憶體重新分配，在 Real-time Thread 中要小心)。
 *
 * [任務]
 * 實作 copyBuffer 函數，將 source 拷貝到 destination 中。
 * 假設 destination 已經有足夠的大小。
 */

void copyBuffer(const std::vector<float> &source, std::vector<float> &destination)
{
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示：使用 std::copy(source開始, source結束, destination開始)
    std::copy(source.begin(), source.end(), destination.begin());
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    std::vector<float> src = {1.1f, 2.2f, 3.3f, 4.4f};
    std::vector<float> dst(4, 0.0f); // 初始化為 0
    int passed = 0;

    copyBuffer(src, dst);

    bool match = true;
    for (size_t i = 0; i < src.size(); ++i)
    {
        if (src[i] != dst[i])
            match = false;
    }

    std::cout << "[測試 1] 資料內容完全一致 -> ";
    if (match)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (內容不匹配)\n";

    std::cout << "--------------------------------------\n";
    if (passed == 1)
        std::cout << "🎉 恭喜！KATA 012 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 012 測試開始 ===\n";
    runTests();
    return 0;
}
