#include <cmath>
#include <iostream>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 025: Boss Fight - Vibrato Effect (顫音效果器綜合測驗)
 * ==============================================================================
 *
 * [說明]
 * 你說你忘記了？這是檢測肌肉記憶與尋找盲點最好的時刻！
 * Vibrato (顫音) 效果器，本質上就是把我們這幾天學的所有東西全部疊加在一起：
 *
 * 1. 它需要一個 LFO (低頻振盪器)，不斷產生一個介於 -1.0 到 1.0 的 Sine 波。
 * 2. 它需要一條 Delay Line (環形緩衝區)。
 * 3. 每一格 Sample 計算時，Delay 的時間長度會被 LFO 調變 (Modulation)。
 *    公式通常是：currentDelay = baseDelay + (lfoOutput * modulationDepth)
 * 4. 因為 currentDelay 一定是小數，所以你必須用到線性插值讀取 (Lerp Read)。
 *
 * [任務]
 * 這是 Sprint 3 的期中考，我不會給你任何變數與函式的步驟提示。
 * 請自行設計 Vibrato class：
 * - 內部需要管理 Buffer 的寫入指標。
 * - 內部需要管理 LFO 的相位指標 (Phase)。
 * - 請實作 processSample(float input) 並且通過嚴格的測試。
 *
 * 💡 忘記了是超級正常的！工程師的日常就是「去翻自己昨天寫的 Code」。
 * 去看看你 KATA 019 (Lerp) 和 KATA 024 (LFO) 的檔案吧！
 */

class DelayLine
{
protected:
    std::vector<float> buffer;
    float delayInSample = 0.0f;
    int writeIdx = 0;
    int bufferSize = 0;

public:
    DelayLine() {};
    void prepare()
    {
        bufferSize = 50;
        buffer.assign(bufferSize, 0.0f);
    };
    void setBuffer(int size)
    {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIdx = 0;
    }

    // storeInSample
    void pushSample(float inputSample_)
    {
        buffer[writeIdx] = inputSample_;
    }

    // readSample
    float pullSample(float delayInSample)
    {
        float readPos = (float)writeIdx - delayInSample;
        int readIdx0 = std::floor(readPos);
        int readIdx1 = readIdx0 + 1;
        float ratio = readPos - (float)readIdx0;
        wrapIdx(readIdx0);
        wrapIdx(readIdx1);
        // linear interpolation
        float output = buffer[readIdx0] + (buffer[readIdx1] - buffer[readIdx0]) * ratio;
        return output;
    }

    void movePtr()
    {
        writeIdx++;
        wrapIdx(writeIdx);
    }

    void reset()
    {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
    }

private:
    void wrapIdx(int &index)
    {
        index = (index + bufferSize) % bufferSize;
    }
};

/*
generate signal from -1 to 1
*/
class LFO
{
protected:
    float sampleRate = 44100.0f;
    float phase = 0.0f;
    float phaseDelta = 0.0f;

public:
    LFO() {};
    void prepare(float sampleRate_)
    {
        sampleRate = sampleRate_;
    }
    void setFreq(float freq_)
    {
        phaseDelta = freq_ / sampleRate;
    }
    float processSample()
    {
        float output = std::sin(2 * M_PI * phase);
        phase = std::fmod(phase + phaseDelta, 1.0f); // wrap
        return output;
    }
    void reset()
    {
        phase = 0.0f;
    }
};

class Vibrato
{
    // 拔除所有輔助輪。自由發揮！
protected:
    DelayLine delayline;
    LFO lfo;
    float baseDelaySamples = 0.0f;
    float modulationDepthSamples = 0.0f;

public:
    Vibrato() {};
    void prepare(float sampleRate_)
    {
        delayline.prepare();
        lfo.prepare(sampleRate_);
    }
    void setLFO(float freq_)
    {
        lfo.setFreq(freq_);
    }
    void setDelayParams(float baseDelaySamples_, float modulationDepthSamples_)
    {
        baseDelaySamples = baseDelaySamples_;
        modulationDepthSamples = modulationDepthSamples_;
    }

    float processSample(float input_)
    {
        float modLFO = lfo.processSample();
        float bufferOutput = delayline.pullSample(baseDelaySamples + modLFO * modulationDepthSamples);
        delayline.pushSample(input_);

        delayline.movePtr();
        return bufferOutput;
    }

    void resetLFO()
    {
        lfo.reset();
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    Vibrato vib;
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    // 建立嚴格的測試環境
    // 取樣率 100Hz, LFO 頻率 25Hz (每步 phase 前進 0.25)
    // Buffer Size 設定大一點防呆即可 (例如 50)
    // baseDelay = 5.0, depth = 2.0
    // LFO 輸出會在 0.0, 1.0, 0.0, -1.0 之間跳動 (-1.0 的情況測試如果忘了會變回去)
    // 所以 delayTime 會是：5.0, 7.0, 5.0, 3.0

    vib.prepare(100.0f);            // 請自己設計 prepare 或 setSampleRate 函數
    vib.setLFO(25.0f);              // 設定 LFO 頻率
    vib.setDelayParams(5.0f, 2.0f); // baseDelaySamples, modulationDepthSamples

    // 我們先灌入一連串的數字 (例如 10, 20, 30, 40, 50, 60, 70, 80 ...)
    // 前幾步因為 buffer 還是空的，我們只 push，不強求 output 正確，先讓 buffer 有資料
    for (int i = 1; i <= 20; ++i)
    {
        vib.processSample((float)(i * 10)); // 灌入 10, 20, 30...
    }

    // 現在 writeIndex 應該來到 20，也就是準備寫入 21。
    // 假設我們在 i=20 的時候 (代表已經 push 了 20 個樣本)，我們強制把 LFO Phase 歸零
    vib.resetLFO();

    // 第 21 步 (input = 210)
    // LFO Phase = 0.0 -> LFO output = 0.0 -> delayTime = 5.0
    // Buffer 寫入 210 後，writePos 推進。
    // 回頭讀取 delay 5.0 的資料：也就是第 16 步灌入的 160。
    float out1 = vib.processSample(210.0f);
    std::cout << "[測試 1] LFO = 0.0, Delay = 5.0 -> ";
    if (isClose(out1, 160.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out1 << ")\n";

    // 第 22 步 (input = 220)
    // LFO Phase = 0.25 -> LFO output = 1.0 -> delayTime = 7.0
    // Buffer 寫入 220 後推指標。回頭讀 7.0 的資料：也就是第 15 步灌入的 150。
    float out2 = vib.processSample(220.0f);
    std::cout << "[測試 2] LFO = 1.0, Delay = 7.0 -> ";
    if (isClose(out2, 150.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out2 << ")\n";

    // 第 23 步 (input = 230)
    // LFO Phase = 0.5 -> LFO output = 0.0 -> delayTime = 5.0
    // 回頭讀 5.0 的資料：第 18 步灌入的 180。
    float out3 = vib.processSample(230.0f);
    std::cout << "[測試 3] LFO = 0.0, Delay = 5.0 -> ";
    if (isClose(out3, 180.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out3 << ")\n";

    // 第 24 步 (input = 240)
    // LFO Phase = 0.75 -> LFO output = -1.0 -> delayTime = 3.0
    // 回頭讀 3.0 的資料：第 21 步灌入的 210。
    float out4 = vib.processSample(240.0f);
    std::cout << "[測試 4] LFO = -1.0, Delay = 3.0 -> ";
    if (isClose(out4, 210.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out4 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 025 期中考通關！你把 LFO 跟 Delay 完美結合了！\n";
    else
        std::cout << "❌ 還有錯誤，去翻翻前面的 Code 吧。\n";
}

int main()
{
    std::cout << "=== KATA 025 測試開始 ===\n";
    runTests();
    return 0;
}
