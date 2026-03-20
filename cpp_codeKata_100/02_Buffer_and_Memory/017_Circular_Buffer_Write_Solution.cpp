#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 017 的解答 (Reference Solution)
 * ==============================================================================
 */

struct CircularBuffer
{
    std::vector<float> buffer;
    int writeIndex;

    CircularBuffer(int size)
    {
        buffer.resize(size, 0.0f);
        writeIndex = 0;
    }

    void pushSample(float input)
    {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 寫入數值
        buffer[writeIndex] = input;

        // 2. 推進指標並繞回
        // 寫法 A: 利用 modulo (%) 運算子，寫起來最優雅
        writeIndex = (writeIndex + 1) % buffer.size();

        /*
        寫法 B: 利用 if 判斷 (在某些沒有強大分支預測或者 % 很慢的微控制器上會用這招)
        writeIndex++;
        if (writeIndex >= buffer.size()) {
            writeIndex = 0;
        }
        */
        // ------------------------------------------------------------------
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
