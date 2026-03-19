#include <iostream>
#include <vector>
#include <cmath>

/*
 * ==============================================================================
 * KATA 020 的解答 (Reference Solution)
 * ==============================================================================
 */

struct SimpleDelay {
    std::vector<float> buffer;
    int writeIndex;
    int bufferSize;

    float delaySamples = 0.0f;
    float feedback = 0.0f;
    float dry = 1.0f;
    float wet = 0.5f;

    SimpleDelay(int size) {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIndex = 0;
    }

    void pushSample(float input) {
        buffer[writeIndex] = input;
        writeIndex = (writeIndex + 1) % bufferSize;
    }

    float getSampleLerp(float delay) {
        float readPos = (float)writeIndex - delay;
        int readPosInt = static_cast<int>(std::floor(readPos));
        float frac = readPos - (float)readPosInt;

        int index0 = (readPosInt % bufferSize + bufferSize) % bufferSize;
        int index1 = (index0 + 1) % bufferSize;

        return buffer[index0] + (buffer[index1] - buffer[index0]) * frac;
    }

    float processSample(float input) {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 從 buffer 讀出延遲的樣本
        float delayedSample = getSampleLerp(delaySamples);
        
        // 2. 計算最終輸出
        float out = (input * dry) + (delayedSample * wet);
        
        // 3. 計算寫回 buffer 的聲音並寫回
        float bufferInput = input + (delayedSample * feedback);
        pushSample(bufferInput);
        
        // 4. 回傳
        return out;
        // ------------------------------------------------------------------
    }
};

int main() {
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
