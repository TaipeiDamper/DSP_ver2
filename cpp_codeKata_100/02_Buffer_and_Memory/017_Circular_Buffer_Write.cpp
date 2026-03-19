#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 017: Circular Buffer - Write (環形緩衝區寫入)
 * ==============================================================================
 *
 * [說明]
 * 環形緩衝區 (Circular Buffer / Ring Buffer) 是 Delay、Reverb、Chorus 等效果器的核心。
 * 它的概念是：我們有一個固定大小的陣列，以及一個不斷往右推進的寫入指標 (writeIndex)。
 * 當寫入指標達到陣列的最尾端時，它會「繞回 (wrap around)」到頭部繼續寫入，覆蓋掉最舊的資料。
 * 就像時鐘的指針一樣，永遠在繞圈圈。
 *
 * [任務]
 * 我們已經建立了一個簡單的 CircularBuffer 結構體。
 * 請實作它的 pushSample 函數。
 * 流程：
 * 1. 把 input 寫入 buffer 中 writeIndex 所指的位置。
 * 2. 把 writeIndex 往下推進 1 格。
 * 3. 確保 writeIndex 不會超過 buffer 的大小 (利用 % 運算子或者 if 判斷繞回)。
 */

struct CircularBuffer
{
    std::vector<float> buffer;
    int writeIndex;
    int bufferSize = 0;

    CircularBuffer(int size)
    {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIndex = 0;
    }

    void pushSample(float input)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 寫入資料
        buffer[writeIndex] = input;
        // 2. 推進指標並繞回 (wrap around)
        writeIndex = (writeIndex + 1) % bufferSize;
        // ------------------------------------------------------------------
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    CircularBuffer cb(3); // 大小為 3 的環形緩衝區
    int passed = 0;

    cb.pushSample(10.0f);
    cb.pushSample(20.0f);

    std::cout << "[測試 1] 一般寫入與指標推進 -> ";
    if (cb.buffer[0] == 10.0f && cb.buffer[1] == 20.0f && cb.writeIndex == 2)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (狀態: index=" << cb.writeIndex << ")\n";

    cb.pushSample(30.0f);

    std::cout << "[測試 2] 指標到達邊界是否正確繞回 -> ";
    if (cb.buffer[2] == 30.0f && cb.writeIndex == 0)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (狀態: index=" << cb.writeIndex << ", 應該要變成 0)\n";

    cb.pushSample(40.0f);

    std::cout << "[測試 3] 繞回後覆蓋舊資料 -> ";
    if (cb.buffer[0] == 40.0f && cb.writeIndex == 1)
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (狀態: index=" << cb.writeIndex << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 017 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 017 測試開始 ===\n";
    runTests();
    return 0;
}
