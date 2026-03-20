#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 026: Chorus Effect (合唱效果器)
 * ==============================================================================
 *
 * [說明]
 * 你剛完成了 Vibrato (顫音)，那是純粹的音高調變 (Pitch Modulation)。
 * Chorus (合唱) 效果器與 Vibrato 的最大差別在於：它保留了「乾訊號 (Dry Signal)」。
 * 當原始聲音與一個「音高略微偏移且有時間差」的聲音混合時，會產生多個人同時演奏的感覺。
 *
 * [公式]
 * output = (1.0f - mix) * dryInput + mix * wetDelayedSignal;
 *
 * [關鍵參數]
 * 1. Mix: 乾濕比 (0.0=全乾, 0.5=一半, 1.0=全濕)。
 * 2. Rate (Hz): LFO 調變的速度 (通常 0.1Hz ~ 3Hz)。
 * 3. Depth (ms): Delay 時間變動的範圍 (通常 2ms ~ 10ms)。
 * 4. Pre-Delay (ms): 延遲的基準點 (通常 20ms 左右)。
 *
 * [任務]
 * 1. 實作一個基礎的 DelayLine (帶線性插值讀取)。
 * 2. 實作一個 Sine LFO。
 * 3. 實作 Chorus 類別：
 *    - 在 processSample 中計算當前的調變後延遲量 (PreDelay_samples + LFO * Depth_samples)。
 *    - 從 DelayLine 讀取插值後的訊號。
 *    - 將 Dry 與 Wet 訊號依照 mix 比例混合輸出。
 *    - 注意：本次測驗的所有參數輸入單位皆為 ms 或 Hz，請在內部自行轉換為 Samples。
 *
 * [提示]
 * samples = ms * 0.001 * sampleRate;
 */

// TODO: 實作 DelayLine 類別
class DelayLine
{
protected:
    std::vector<float> buffer;
    int writeIdx = 0;

public:
    void prepare(int maxDelayInSamples)
    {
        buffer.assign(maxDelayInSamples, 0.0f);
    }

    void pushSample(float input)
    {
        // ...
        buffer[writeIdx] = input;
    }

    float pullSample(float delayInSamples)
    {
        // ... (需含線性插值)
        float readPos = (float)writeIdx - delayInSamples;
        int writeIdx0 = std::floor(readPos);
        int writeIdx1 = writeIdx0 + 1;
        float ratio = readPos - writeIdx0;

        wrapIdx(writeIdx0);
        wrapIdx(writeIdx1);
        // linear interplation
        float interp = buffer[writeIdx0] + (buffer[writeIdx1] - buffer[writeIdx0]) * ratio;

        return interp;
    }

    void advance()
    {
        writeIdx++;
        wrapIdx(writeIdx);
    }

    void wrapIdx(int &index)
    {
        int size = (int)buffer.size();
        index = (index + size) % size;
    }
};

// TODO: 實作 LFO 類別 (輸出 -1.0 ~ 1.0)
class LFO
{
protected:
    float sampleRate = 44100.0f;
    float freq = 440.0f;
    float phase = 0.0f;
    float phaseDelta = 0.0f;

public:
    void prepare(float sampleRate)
    {
        // ...
        this->sampleRate = sampleRate;
    }

    void setFreq(float freqHz)
    {
        // ...
        freq = freqHz;
        phaseDelta = freq / sampleRate;
    }

    float processSample()
    {
        // ...
        float output = std::sin(2 * M_PI * phase);

        // phase wrap
        phase += phaseDelta;
        phase = std::fmod(phase, 1.0f);

        return output;
    }

    void reset()
    {
        phase = 0.0f;
    }
};

// TODO: 實作 Chorus 類別
class Chorus
{
protected:
    DelayLine delayline;
    LFO lfo;
    float sampleRate = 44100.0f;
    float preDelayInSamples;
    float depthInSamples;
    float rateHz = 0.0f;
    float mix = 0.0f;

public:
    void prepare(float sampleRate)
    {
        this->sampleRate = sampleRate;

        // ... 設置 DelayLine 與 LFO
        float delayInSec = 0.1f; // sec 沒給就自己給了
        float delayInSample = delayInSec * sampleRate;
        delayline.prepare(delayInSample);

        lfo.prepare(sampleRate);
    }

    void setParams(float preDelayMs, float depthMs, float rateHz, float mix)
    {
        // 將 ms 轉換為 samples，並存儲參數
        preDelayInSamples = preDelayMs * sampleRate / 1000;
        depthInSamples = depthMs * sampleRate / 1000;
        this->rateHz = rateHz;
        this->mix = mix;

        lfo.setFreq(rateHz);
        lfo.reset();
    }

    float processSample(float input)
    {
        // 1. 取得 LFO 輸出
        float lfoOutput = lfo.processSample();
        // 2. 計算調變後的延遲量 (不要低於 0!)
        float delayInSample = preDelayInSamples + depthInSamples * lfoOutput;
        if (delayInSample <= 0)
        {
            delayInSample = 0.001f; // pre protected
        }
        // 3. 從 DelayLine 讀取訊號 (Wet)
        float bufferOutput = delayline.pullSample(delayInSample);
        // 4. 寫入當前訊號到 DelayLine 並推進指標
        delayline.pushSample(input);
        delayline.advance();
        // 5. 輸出 (1-mix)*input + mix*wet
        return (1 - mix) * input + mix * bufferOutput;
    }

    void reset()
    {
        lfo.reset();
    }
};

// ==========================================
// 測試區塊 (嚴禁修改)
// ==========================================
void runTests()
{
    Chorus chorus;
    float sampleRate = 1000.0f; // 1kHz 方便計算
    chorus.prepare(sampleRate);

    // 設置：
    // Pre-delay: 10ms (10 samples)
    // Depth: 2ms (2 samples) -> 調變範圍 8~12 samples
    // Rate: 250Hz -> 在 1kHz 下每 4 samples 一個週期
    // Mix: 0.5
    chorus.setParams(10.0f, 2.0f, 250.0f, 0.5f);

    std::vector<float> input(20);
    for (int i = 0; i < 20; ++i)
        input[i] = (float)((i + 1) * 10); // 10, 20, 30...

    // 填充 Buffer
    for (int i = 0; i < 15; ++i)
        chorus.processSample(input[i]);
    chorus.reset();
    // 開始測試關鍵點
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.1f; };
    int passed = 0;

    // 第 16 步 (input = 160)
    // LFO Phase = 0 -> output = 0 -> Delay = 10.0 samples
    // Wet = input[16 - 10 - 1] = input[5] = 60.0f
    // Output = 0.5 * 160 + 0.5 * 60 = 110.0f
    float out1 = chorus.processSample(160.0f);
    std::cout << "[Test 1] Mix 0.5, Delay 10.0 samples -> ";
    if (isClose(out1, 110.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (Result: " << out1 << ", Expected: 110.0)\n";

    // 第 17 步 (input = 170)
    // LFO Phase = 0.25 -> output = 1.0 -> Delay = 12.0 samples
    // Wet = input[17 - 12 - 1] = input[4] = 50.0f
    // Output = 0.5 * 170 + 0.5 * 50 = 110.0f
    float out2 = chorus.processSample(170.0f);
    std::cout << "[Test 2] Mix 0.5, Delay 12.0 samples -> ";
    if (isClose(out2, 110.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (Result: " << out2 << ", Expected: 110.0)\n";

    // 第 18 步 (input = 180)
    // LFO Phase = 0.5 -> output = 0 -> Delay = 10.0 samples
    // Wet = input[18 - 10 - 1] = input[7] = 80.0f
    // Output = 0.5 * 180 + 0.5 * 80 = 130.0f
    float out3 = chorus.processSample(180.0f);
    std::cout << "[Test 3] Mix 0.5, Delay 10.0 samples -> ";
    if (isClose(out3, 130.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (Result: " << out3 << ", Expected: 130.0)\n";

    // 第 19 步 (input = 190)
    // LFO Phase = 0.75 -> output = -1.0 -> Delay = 8.0 samples
    // Wet = input[19 - 8 - 1] = input[10] = 110.0f
    // Output = 0.5 * 190 + 0.5 * 110 = 150.0f
    float out4 = chorus.processSample(190.0f);
    std::cout << "[Test 4] Mix 0.5, Delay 8.0 samples -> ";
    if (isClose(out4, 150.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (Result: " << out4 << ", Expected: 150.0)\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 026 合唱效果器測試通過！\n";
    else
        std::cout << "❌ 還有一些邊界條件或單位轉換需要檢查喔！\n";
}

int main()
{
    std::cout << "=== KATA 026 測試開始 ===\n";
    runTests();
    return 0;
}
