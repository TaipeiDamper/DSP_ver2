#include <iostream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 025 (解答 Reference Solution)
 * ==============================================================================
 */

class Vibrato
{
private:
    // LFO 狀態
    float phase = 0.0f;
    float lfoFreq = 1.0f;
    float sampleRate = 44100.0f;

    // Delay 狀態
    std::vector<float> buffer;
    int writeIndex = 0;
    int bufferSize = 44100;
    float baseDelaySamples = 0.0f;
    float modulationDepthSamples = 0.0f;

public:
    void prepare(float sr)
    {
        sampleRate = sr;
        bufferSize = (int)sampleRate * 2; // 簡單防呆給個 2 秒 Buffer
        buffer.assign(bufferSize, 0.0f);
        writeIndex = 0;
    }

    void setLFO(float freq)
    {
        lfoFreq = freq;
    }

    void setDelayParams(float baseDelay, float depth)
    {
        baseDelaySamples = baseDelay;
        modulationDepthSamples = depth;
    }

    void resetLFO()
    {
        phase = 0.0f;
    }

    float processSample(float input)
    {
        // ==========================
        // 1. 取得 LFO 數值並推進
        // ==========================
        float lfoOutput = std::sin(phase * 2.0f * M_PI);
        
        phase += lfoFreq / sampleRate;
        while (phase >= 1.0f) {
            phase -= 1.0f;
        }

        // ==========================
        // 2. 處理 Delay 讀取 (Lerp)
        // ==========================
        float currentDelay = baseDelaySamples + (lfoOutput * modulationDepthSamples);
        
        // 從當下指針往回退 currentDelay，算出浮點數絕對位置
        float readPos = (float)writeIndex - currentDelay;
        
        // 抽出絕對整數位置與小數
        int readPosInt = static_cast<int>(std::floor(readPos));
        float frac = readPos - (float)readPosInt;

        // 繞回範圍內
        int index0 = (readPosInt % bufferSize + bufferSize) % bufferSize;
        int index1 = (index0 + 1) % bufferSize;

        // 線性插值
        float delayedSample = buffer[index0] + (buffer[index1] - buffer[index0]) * frac;

        // ==========================
        // 3. 處理 Delay 寫入
        // ==========================
        buffer[writeIndex] = input;
        writeIndex = (writeIndex + 1) % bufferSize;

        return delayedSample; 
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
