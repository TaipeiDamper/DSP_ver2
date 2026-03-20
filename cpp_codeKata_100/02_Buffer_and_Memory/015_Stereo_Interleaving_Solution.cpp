#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 015 的解答 (Reference Solution)
 * ==============================================================================
 */

void interleave(const std::vector<float> &leftBuffer, const std::vector<float> &rightBuffer,
                std::vector<float> &interleavedOut)
{
    // ------------------------------------------------------------------
    // 解答：
    // 使用一個迴圈同時處理兩個聲道。
    // 左聲道放在偶數索引 (0, 2, 4...)
    // 右聲道放在奇數索引 (1, 3, 5...)

    for (size_t i = 0; i < leftBuffer.size(); ++i)
    {
        interleavedOut[i * 2] = leftBuffer[i];
        interleavedOut[i * 2 + 1] = rightBuffer[i];
    }
    // ------------------------------------------------------------------
}

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
