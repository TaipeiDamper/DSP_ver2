#include <iostream>
#include <cmath>

/*
 * ==============================================================================
 * KATA 023 的解答 (Reference Solution)
 * ==============================================================================
 */

class AREnvelope
{
private:
    float z1 = 0.0f;
    float attackMemory = 0.0f;
    float releaseMemory = 0.0f;

public:
    void reset()
    {
        z1 = 0.0f;
    }

    void setTimes(float attackMs, float releaseMs, float sampleRate)
    {
        float attackSec = attackMs / 1000.0f;
        float releaseSec = releaseMs / 1000.0f;

        attackMemory = (attackSec > 0.0f) ? std::exp(-1.0f / (attackSec * sampleRate)) : 0.0f;
        releaseMemory = (releaseSec > 0.0f) ? std::exp(-1.0f / (releaseSec * sampleRate)) : 0.0f;
    }

    float processSample(float input)
    {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 判斷新進來的數字比現在的 z1 大還是小？
        // 2. 如果比較大，代表正在上漲，選用 attack 係數；反之則用 release 係數
        float memory = (input > z1) ? attackMemory : releaseMemory;

        // 3. 套用記憶心法公式：舊的比例留下，新的比例進來
        float output = (z1 * memory) + (input * (1.0f - memory));
        
        // 4. 更新歷史並回傳
        z1 = output;
        return output;
        // ------------------------------------------------------------------
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
