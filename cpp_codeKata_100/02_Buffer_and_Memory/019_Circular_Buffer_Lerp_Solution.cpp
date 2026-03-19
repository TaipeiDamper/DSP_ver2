#include <iostream>
#include <vector>
#include <cmath>

/*
 * ==============================================================================
 * KATA 019 的解答 (Reference Solution)
 * ==============================================================================
 */

struct CircularBuffer {
    std::vector<float> buffer;
    int writeIndex;
    int bufferSize;

    CircularBuffer(int size) {
        bufferSize = size;
        buffer.resize(bufferSize, 0.0f);
        writeIndex = 0;
    }

    void pushSample(float input) {
        buffer[writeIndex] = input;
        writeIndex = (writeIndex + 1) % bufferSize;
    }

    float getSampleLerp(float delaySamples) {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 計算浮點數讀取位置，並確保加 bufferSize 處理負數
        float readPos = (float)writeIndex - delaySamples;
        while (readPos < 0.0f) readPos += (float)bufferSize;
        while (readPos >= (float)bufferSize) readPos -= (float)bufferSize;
        
        // 2. 取得 index0, index1 與小數 frac
        int index0 = (int)std::floor(readPos);
        int index1 = (index0 + 1) % bufferSize;
        float frac = readPos - (float)index0;
        
        // 3. 執行線性插值 (Lerp)
        return buffer[index0] + frac * (buffer[index1] - buffer[index0]);
        // ------------------------------------------------------------------
    }
};

int main() {
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
