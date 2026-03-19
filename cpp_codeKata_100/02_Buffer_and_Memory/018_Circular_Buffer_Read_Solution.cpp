#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 018 的解答 (Reference Solution)
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

    float getSample(int delaySamples) {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 計算讀取位置 (考慮繞回 wrap around)
        int readIndex = (writeIndex - delaySamples + bufferSize) % bufferSize;
        
        // 2. 回傳該位置的數值
        return buffer[readIndex];
        // ------------------------------------------------------------------
    }
};

int main() {
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
