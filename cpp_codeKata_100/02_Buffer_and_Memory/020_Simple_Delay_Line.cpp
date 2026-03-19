#include <cmath>
#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 020: Simple Delay Line (Sprint 2 Boss: 簡單延遲效果器)
 * ==============================================================================
 *
 * [說明]
 * 將 Circular Buffer 的 Read 和 Write 結合，並加入 Feedback (反饋)。
 * 這就是一顆完整 Delay Plugin 的 DSP 核心！
 *
 * 訊號流：
 * 1. 讀取 Buffer 裡 N 個樣本前的聲音 -> delayedSample
 * 2. 混合輸出 -> out = (input * dry) + (delayedSample * wet)
 * 3. 寫入 Buffer -> bufferInput = input + (delayedSample * feedback)
 * 4. 將 bufferInput 推進 Circular Buffer
 *
 * [任務]
 * 我們已經為你保留了 getSampleLerp 和 pushSample 函數。
 * 請實作 processSample 函數，完成整個 Delay 的引擎運作。
 */

class SimpleDelay
{
  private:
    std::vector<float> buffer;
    int writeIndex;
    int bufferSize;

  public:
    // 效果器參數
    float delaySamples = 0.0f;
    float feedback = 0.0f;
    float dry = 1.0f;
    float wet = 0.5f;

    SimpleDelay(int size)
    {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIndex = 0;
    }

    // 將前面學過的寫在這裡
    // store in buffer
    void pushSample(float input)
    {
        buffer[writeIndex] = input;
        writeIndex = (writeIndex + 1) % bufferSize;
    }

    // take sample from buffer
    float getSampleLerp(float delay)
    {
        float readPos = (float)writeIndex - delay;
        int readPosInt = static_cast<int>(std::floor(readPos));
        float frac = readPos - (float)readPosInt;

        int index0 = (readPosInt % bufferSize + bufferSize) % bufferSize;
        int index1 = (index0 + 1) % bufferSize;

        return buffer[index0] + (buffer[index1] - buffer[index0]) * frac;
    }

    // 🏆 魔王關挑戰：
    float processSample(float input)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 從 buffer 讀出延遲的樣本 (依據 this->delaySamples)
        float delayedSample = getSampleLerp(delaySamples);
        // 2. 計算並保存最終要 output 的聲音
        float output = input * dry + delayedSample * wet;
        // 3. 計算要寫回 buffer 的聲音 (包含 feedback)
        float sampleToBuffer = input + delayedSample * feedback;
        // 4. pushSample 寫回 buffer
        pushSample(sampleToBuffer);
        // 5. 回傳 output

        return output; // 請修正
        // ------------------------------------------------------------------
    }
};

//  * 訊號流：
//  * 1. 讀取 Buffer 裡 N 個樣本前的聲音 -> delayedSample
//  * 2. 混合輸出 -> out = (input * dry) + (delayedSample * wet)
//  * 3. 寫入 Buffer -> bufferInput = input + (delayedSample * feedback)
//  * 4. 將 bufferInput 推進 Circular Buffer

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    SimpleDelay delay(100);
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    // 設定參數
    delay.delaySamples = 5.0f; // 延遲 5 個樣本
    delay.feedback = 0.5f;     // 反饋一半的聲音
    delay.dry = 1.0f;
    delay.wet = 0.5f;

    // 灌入一個 Impulse (脈衝訊號：第一下是 1.0，後面全是 0.0)
    float out0 = delay.processSample(1.0f); // 剛開始 buffer 是空的
    std::cout << "[測試 1] 第一個樣本，Dry 信號直接通過 -> ";
    if (isClose(out0, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out0 << ")\n";

    // 推進到第 5 個樣本 (Delay 發生的瞬間)
    // 期間 1~4 全丟 0.0f
    delay.processSample(0.0f);
    delay.processSample(0.0f);
    delay.processSample(0.0f);
    delay.processSample(0.0f);

    float out5 = delay.processSample(0.0f);
    std::cout << "[測試 2] 第 5 個樣本，聽到第一次 Delay (Wet 0.5) -> ";
    // buffer 裡面讀出 1.0，乘以 wet(0.5) = 0.5
    if (isClose(out5, 0.5f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out5 << ")\n";

    // 再推進 5 個樣本，測試 Feedback
    delay.processSample(0.0f);
    delay.processSample(0.0f);
    delay.processSample(0.0f);
    delay.processSample(0.0f);

    float out10 = delay.processSample(0.0f);
    std::cout << "[測試 3] 第 10 個樣本，聽到 Feedback (Wet 0.5 * FB 0.5) -> ";
    // 上一次 1.0 被 push 回去時剩 0.5 (feedback)。這次讀出來乘以 wet(0.5) = 0.25
    if (isClose(out10, 0.25f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out10 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3)
        std::cout << "🎉 恭喜！KATA 020 挑戰成功！Sprint 2 完美通關！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 020 測試開始 ===\n";
    runTests();
    return 0;
}
