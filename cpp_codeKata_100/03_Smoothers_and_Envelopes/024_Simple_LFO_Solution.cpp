#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 024 的解答 (Reference Solution)
 * ==============================================================================
 */

class SimpleLFO
{
private:
    float phase = 0.0f;
    float phaseIncrement = 0.0f;
    
    float frequency = 1.0f;
    float sampleRate = 44100.0f;

    void updatePhaseIncrement()
    {
        if (sampleRate > 0.0f) {
            phaseIncrement = frequency / sampleRate;
        } else {
            phaseIncrement = 0.0f;
        }
    }

public:
    void setSampleRate(float sr)
    {
        sampleRate = sr;
        updatePhaseIncrement();
    }

    void setFrequency(float freq)
    {
        frequency = freq;
        updatePhaseIncrement();
    }

    void reset()
    {
        phase = 0.0f;
    }

    float processSample()
    {
        // 1. 先計算當下這一格的輸出 (對應 Phase 的狀態)
        float output = std::sin(phase * 2.0f * M_PI);
        
        // 2. 推進 Phase 給下一個 Sample 用
        phase += phaseIncrement;
        
        // 3. 處理繞回 (Wrap around)
        // 使用 while 處理，因為 phase increment 絕對不會大於 1.0 許多次，通常只要減 1 次
        while (phase >= 1.0f) {
            phase -= 1.0f;
        }

        return output;
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
