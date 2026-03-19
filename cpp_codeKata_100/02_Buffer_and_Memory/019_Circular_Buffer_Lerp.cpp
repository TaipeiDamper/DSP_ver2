#include <cmath>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 019: Circular Buffer - Linear Interpolation (線性插值讀取)
 * ==============================================================================
 *
 * [說明]
 * 當我們要做 Delay 時間動態變化 (例如 Vibrato 或 Chorus) 時，
 * 延遲長度 (delaySamples) 通常不可能是整數。
 *
 * 例如：如果 delay 是 2.5 樣本，我們必須取出第 2 個跟第 3 個樣本進行線性插值 (Lerp)。
 *
 * [任務]
 * 實作 getSampleLerp 函數。
 * 提示 (無分支高效寫法)：
 * 1. float readPos = (float)writeIndex - delaySamples;
 * 2. int readPosInt = static_cast<int>(std::floor(readPos)); // 取出絕對整數部分
 * 3. float frac = readPos - (float)readPosInt;               // 取出絕對小數部分
 * 4. 透過 (readPosInt % bufferSize + bufferSize) % bufferSize 求出 index0 處理繞回
 * 5. 求出 index1 也處理繞回
 * 6. 套用線性插值：buffer[index0] + (buffer[index1] - buffer[index0]) * frac;
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

    float getSampleLerp(float delaySamples)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 計算浮點數讀取位置
        float readPos = wrap((float)writeIndex - delaySamples);
        // 2. 取得 index0, index1 與小數 frac
        int index0 = static_cast<int>(std::floor(readPos));
        int index1 = wrap(index0 + 1);
        float frac = wrap(readPos - (float)index0);
        // 3. 執行線性插值 (Lerp)
        float lerp = buffer[index0] + (buffer[index1] - buffer[index0]) * frac;

        return lerp; // 請修正
        // ------------------------------------------------------------------
    }

    int wrap(int index)
    {
        index = (index + bufferSize) % bufferSize;
        return index;
    }

    float wrap(float index)
    {
        index = std::fmod((index + (float)bufferSize), (float)bufferSize);
        return index;
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    CircularBuffer cb(5);
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    // 依序寫入 1, 2, 3, 4, 5
    cb.pushSample(10.0f); // index 0
    cb.pushSample(20.0f); // index 1
    cb.pushSample(30.0f); // index 2
    cb.pushSample(40.0f); // index 3
    cb.pushSample(50.0f); // index 4 -> writeIndex = 0

    std::cout << "[測試 1] 整數延遲讀取 (delay 1.0) -> ";
    if (isClose(cb.getSampleLerp(1.0f), 50.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSampleLerp(1.0f) << ")\n";

    std::cout << "[測試 2] 半位樣本延遲 (delay 1.5) -> ";
    // 應介於 index 4 (50.0) 與 index 3 (40.0) 之間 -> 45.0
    if (isClose(cb.getSampleLerp(1.5f), 45.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSampleLerp(1.5f) << ")\n";

    std::cout << "[測試 3] 跨界樣本延遲 (delay 4.5) -> ";
    // 計算：readPos = 0 - 4.5 = -4.5 -> 繞回後落於 index 0.5
    // index0 = 0 (10.0), index1 = 1 (20.0), frac = 0.5 -> 應該是 15.0
    if (isClose(cb.getSampleLerp(4.5f), 15.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << cb.getSampleLerp(4.5f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 019 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 019 測試開始 ===\n";
    runTests();
    return 0;
}
