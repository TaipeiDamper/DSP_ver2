#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DelayLine {
public:
    void prepare(int maxDelayInSamples) {
        buffer.assign(maxDelayInSamples + 10, 0.0f);
        bufferSize = buffer.size();
        writeIdx = 0;
    }
    
    void pushSample(float input) {
        buffer[writeIdx] = input;
    }
    
    float pullSample(float delayInSamples) {
        float readPos = (float)writeIdx - delayInSamples;
        while(readPos < 0) readPos += (float)bufferSize;
        
        int idx0 = (int)readPos;
        int idx1 = (idx0 + 1) % bufferSize;
        float frac = readPos - (float)idx0;
        
        return buffer[idx0] + frac * (buffer[idx1] - buffer[idx0]);
    }
    
    void advance() {
        writeIdx = (writeIdx + 1) % bufferSize;
    }

private:
    std::vector<float> buffer;
    int writeIdx = 0;
    int bufferSize = 0;
};

class LFO {
public:
    void prepare(float sampleRate) {
        this->sampleRate = sampleRate;
        phase = 0.0f;
        phaseDelta = 0.0f;
    }
    
    void setFreq(float freqHz) {
        phaseDelta = freqHz / sampleRate;
        // 注意：測試中的 250Hz 在 1kHz 下，phaseDelta = 0.25
    }
    
    float processSample() {
        float output = std::sin(2.0f * (float)M_PI * phase);
        phase += phaseDelta;
        if(phase >= 1.0f) phase -= 1.0f;
        return output;
    }
    
    void reset() { phase = 0.0f; }

private:
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float sampleRate = 44100.0f;
};

class Chorus {
public:
    void prepare(float sampleRate) {
        this->sampleRate = sampleRate;
        // 假設最大延遲不超過 100ms
        delayLine.prepare((int)(0.1f * sampleRate));
        lfo.prepare(sampleRate);
    }
    
    void setParams(float preDelayMs, float depthMs, float rateHz, float mix) {
        this->preDelaySamples = preDelayMs * 0.001f * sampleRate;
        this->depthSamples = depthMs * 0.001f * sampleRate;
        this->mix = mix;
        lfo.setFreq(rateHz);
        lfo.reset();
    }
    
    float processSample(float input) {
        float lfoOut = lfo.processSample();
        float currentDelay = preDelaySamples + lfoOut * depthSamples;
        
        // 確保延遲不小於 0 (雖然 preDelay > depth 時不會，但好習慣)
        if(currentDelay < 0.0f) currentDelay = 0.0f;
        
        float wet = delayLine.pullSample(currentDelay);
        delayLine.pushSample(input);
        delayLine.advance();
        
        return (1.0f - mix) * input + mix * wet;
    }

private:
    DelayLine delayLine;
    LFO lfo;
    float sampleRate = 44100.0f;
    float preDelaySamples = 0.0f;
    float depthSamples = 0.0f;
    float mix = 0.5f;
};

// ==========================================
// 測試區塊 (嚴禁修改)
// ==========================================
void runTests() {
    Chorus chorus;
    float sampleRate = 1000.0f; // 1kHz 方便計算
    chorus.prepare(sampleRate);
    
    chorus.setParams(10.0f, 2.0f, 250.0f, 0.5f);
    
    std::vector<float> input(30);
    for(int i=0; i<30; ++i) input[i] = (float)((i+1) * 10);

    for(int i=0; i<15; ++i) chorus.processSample(input[i]);

    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.1f; };
    int passed = 0;

    float out1 = chorus.processSample(160.0f);
    std::cout << "[Test 1] Mix 0.5, Delay 10.0 samples -> ";
    if (isClose(out1, 110.0f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out1 << ", Expected: 110.0)\n";

    float out2 = chorus.processSample(170.0f);
    std::cout << "[Test 2] Mix 0.5, Delay 12.0 samples -> ";
    if (isClose(out2, 110.0f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out2 << ", Expected: 110.0)\n";

    float out3 = chorus.processSample(180.0f);
    std::cout << "[Test 3] Mix 0.5, Delay 10.0 samples -> ";
    if (isClose(out3, 130.0f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out3 << ", Expected: 130.0)\n";

    float out4 = chorus.processSample(190.0f);
    std::cout << "[Test 4] Mix 0.5, Delay 8.0 samples -> ";
    if (isClose(out4, 150.0f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out4 << ", Expected: 150.0)\n";

    std::cout << "--------------------------------------\n";
    if (passed == 4)
        std::cout << "🎉 恭喜！KATA 026 合唱效果器測試通過！\n";
    else
        std::cout << "❌ 還有一些邊界條件或單位轉換需要檢查喔！\n";
}

int main() {
    std::cout << "=== KATA 026 測試開始 ===\n";
    runTests();
    return 0;
}
