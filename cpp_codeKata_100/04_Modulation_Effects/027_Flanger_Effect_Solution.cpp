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
        bufferSize = (int)buffer.size();
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

    void reset() {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
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

class Flanger {
public:
    void prepare(float sampleRate) {
        this->sampleRate = sampleRate;
        // Flanger 預計不超過 20ms
        delayLine.prepare((int)(0.05f * sampleRate));
        lfo.prepare(sampleRate);
    }
    
    void setParams(float preDelayMs, float depthMs, float rateHz, float mix, float fb) {
        this->preDelaySamples = preDelayMs * 0.001f * sampleRate;
        this->depthSamples = depthMs * 0.001f * sampleRate;
        this->mix = mix;
        this->feedback = fb;
        lfo.setFreq(rateHz);
        lfo.reset();
    }
    
    float processSample(float input) {
        float lfoOut = lfo.processSample();
        float currentDelay = preDelaySamples + lfoOut * depthSamples;
        if(currentDelay < 0.1f) currentDelay = 0.1f; // 確保不為0，防止與Input重疊
        
        // 1. Pull
        float wet = delayLine.pullSample(currentDelay);
        
        // 2. Feedback + Push (關鍵順序)
        float feedbackSignal = wet * feedback;
        delayLine.pushSample(input + feedbackSignal);
        delayLine.advance();
        
        // 3. Mix
        return (1.0f - mix) * input + mix * wet;
    }

    void reset() {
        lfo.reset();
    }

private:
    DelayLine delayLine;
    LFO lfo;
    float sampleRate = 44100.0f;
    float preDelaySamples = 0.0f;
    float depthSamples = 0.0f;
    float mix = 0.5f;
    float feedback = 0.0f;
};

// ==========================================
// 測試區塊 
// ==========================================
void runTests() {
    Flanger flanger;
    float sampleRate = 1000.0f; 
    flanger.prepare(sampleRate);
    flanger.setParams(5.0f, 2.0f, 250.0f, 0.5f, 0.8f);
    
    std::vector<float> input(30, 100.0f); 

    // 1. 填充穩定 Buffer 階段
    for(int i=0; i<15; ++i) flanger.processSample(input[i]);

    // 2. 準備測試階段 (強制歸零確保同步)
    flanger.reset();
    
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.1f; };
    int passed = 0;

    float out1 = flanger.processSample(100.0f);
    std::cout << "[Test 1] Feedback Check -> ";
    if (out1 > 100.0f) { std::cout << "PASS (Wet signal includes resonance)\n"; passed++; }
    else std::cout << "FAIL (No feedback resonance detected)\n";

    float out2 = flanger.processSample(100.0f);
    std::cout << "[Test 2] LFO Max Depth Check -> ";
    if (out2 > 100.0f) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out2 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 027 噴射效果器通關！那共振感真強！\n";
}

int main() {
    std::cout << "=== KATA 027 測試開始 ===\n";
    runTests();
    return 0;
}
