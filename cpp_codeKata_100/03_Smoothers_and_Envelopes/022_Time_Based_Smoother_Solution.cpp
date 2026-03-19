#include <iostream>
#include <cmath>

/*
 * ==============================================================================
 * KATA 022 的解答 (Reference Solution)
 * ==============================================================================
 */

class TimeBasedSmoother
{
private:
    float z1 = 0.0f;
    float coeff = 1.0f;

public:
    void reset()
    {
        z1 = 0.0f;
    }

    void setTimeConstant(float timeInMs, float sampleRate)
    {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 檢查 timeInMs 是否極小，如果是，直接設為 1.0f (瞬間到達)
        if (timeInMs <= 0.0f)
        {
            coeff = 1.0f;
            return;
        }

        // 2. 把 timeInMs 換算成秒
        float timeInSeconds = timeInMs / 1000.0f;

        // 3. 計算並儲存 coeff
        // 提醒：不要忘記 std::exp
        coeff = 1.0f - std::exp(-1.0f / (timeInSeconds * sampleRate));
        // ------------------------------------------------------------------
    }

    float processSample(float input)
    {
        float output = z1 + (input - z1) * coeff;
        z1 = output;
        return output;
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
