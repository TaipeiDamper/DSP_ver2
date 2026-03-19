#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 018: Circular Buffer - Read (環形緩衝區讀取)
 * ==============================================================================
 *
 * [說明]
 * 延續 KATA 017，有了寫入功能後，我們需要能夠「回頭讀取」過去的資料。
 * 這是實現 Delay 效果的關鍵。
 *
 * [觀念]
 * 假設現在寫入指標在 writeIndex。
 * 如果我們想要讀取「N 個樣本前」的資料 (delaySamples)：
 * readIndex = writeIndex - delaySamples
 *
 * 但因為這是一個環形緩衝區，如果相減變成負數，我們必須把它繞回到陣列的尾端。
 * 公式：(writeIndex - delaySamples + bufferSize) % bufferSize
 *
 * [任務]
 * 實作 getSample 函數，根據指定的延遲長度回傳樣本。
 */

struct CircularBuffer
{
    std::vector<float> buffer;
    int writeIndex;
    int bufferSize;

    CircularBuffer(int size)
    {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIndex = 0;
    }

    void pushSample(float input)
    {
        buffer[writeIndex] = input;
        writeIndex = (writeIndex + 1) % bufferSize;
    }

    float getSample(int delaySamples)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 計算讀取位置 (考慮繞回 wrap around)
        int readIndex = (writeIndex - delaySamples + bufferSize) % bufferSize;
        // 2. 回傳該位置的數值

        return buffer[readIndex]; // 請修正
        // ------------------------------------------------------------------
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    CircularBuffer cb(5);
    int passed = 0;

    // 依序寫入 1, 2, 3, 4, 5
    cb.pushSample(1.0f); // index 0
    cb.pushSample(2.0f); // index 1
    cb.pushSample(3.0f); // index 2
    cb.pushSample(4.0f); // index 3
    cb.pushSample(5.0f); // index 4 -> 下一個 writeIndex 會變成 0

    std::cout << "[測試 1] 讀取最近寫入的樣本 (delay 1) -> ";
    // 目前 writeIndex 是 0，delay 1 應該是 index 4 的內容 (5.0)
    if (cb.getSample(1) == 5.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSample(1) << ")\n";

    std::cout << "[測試 2] 讀取更早的樣本 (delay 3) -> ";
    // delay 3 應該是 index 2 的內容 (3.0)
    if (cb.getSample(3) == 3.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSample(3) << ")\n";

    // 再寫入一個，覆蓋掉 index 0
    cb.pushSample(6.0f); // index 0, 下一個 writeIndex 是 1

    std::cout << "[測試 3] 繞回後的讀取 (delay 1) -> ";
    // 目前 writeIndex 是 1，delay 1 應該是 index 0 的內容 (6.0)
    if (cb.getSample(1) == 6.0f)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSample(1) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 018 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 018 測試開始 ===\n";
    runTests();
    return 0;
}
