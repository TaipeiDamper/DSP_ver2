#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 024: Simple LFO (低頻振盪器)
 * ==============================================================================
 *
 * [說明]
 * LFO 會產生一個連續起伏的正弦波 (Sine Wave) 來調變各種參數。
 * 它的核心是一個不斷前進的 Phase (相位)，範圍介於 0.0 ~ 1.0。
 *
 * 已知規則：
 * 1. 每次呼叫 processSample，Phase 必須增加 (frequency / sampleRate)。
 * 2. 如果 Phase 超過 1.0，必須減掉 1.0 確保繞回。
 * 3. 輸出公式為正弦波： std::sin(Phase * 2.0 * M_PI)
 *
 * [任務]
 * 從現在開始沒有步驟提示。
 * 請自行設計 SimpleLFO class 內部的 private 狀態與 public 介面/函式。
 * (務必確保有準備 setFrequency(float freq), setSampleRate(float sr), 以及 processSample())
 */

class SimpleLFO
{
    // 請拔除輔助輪，自由發揮！
  private:
  public:
    SimpleLFO() {};
    void setFrequency(float freq_)
    {
        frequency = freq_;
    };
    void setSampleRate(float sr)
    {
        sampleRate = sr;
    };
    float processSample()
    {
        float output = std::sin(phase * 2.0f * M_PI);
        phase += frequency / sampleRate;
        wrap(phase);
        return output;
    };

  protected:
    float phase = 0.0f;
    float frequency = 0.0f;
    float sampleRate = 0.0f;

    void wrap(float &phase_)
    {
        phase_ = std::fmod(phase_, 1.0f);
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    SimpleLFO lfo;
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    // 假設取樣率是 100 Hz，LFO 也就是 25 Hz
    // 這意味著：
    // 每經過 1 個 sample，phase 會前進 25/100 = 0.25
    lfo.setSampleRate(100.0f);
    lfo.setFrequency(25.0f);

    std::cout << "[測試 1] 第 0 步 (Phase 0.0) -> ";
    // 注意：如果在 processSample 內是先算 sin 再把 phase 前進，第一步輸出應該是 sin(0) = 0.0
    // 如果你是先 phase 前進再算 sin，這裡第一步會跑到 sin(0.5 * PI) = 1.0
    // 為求標準化，請做到：當前這格的 output，取決於「前進後」還是「前進前」都行。
    // 在這份測試中，我們預期「先算輸出，算完後 phase 再往前推進給下一次用」。
    float out1 = lfo.processSample();
    if (isClose(out1, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out1 << ")\n";

    std::cout << "[測試 2] 第 1 步 (Phase 0.25) -> ";
    // out2 輸出時 phase 應該是 0.25 (對應 0.5 * PI)
    // sin(0.5 * PI) = 1.0
    float out2 = lfo.processSample();
    if (isClose(out2, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out2 << ")\n";

    std::cout << "[測試 3] 第 2 步 (Phase 0.5) -> ";
    // phase = 0.5，sin(PI) = 0.0
    float out3 = lfo.processSample();
    if (isClose(out3, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out3 << ")\n";

    std::cout << "[測試 4] 第 3 步 (Phase 0.75) -> ";
    // phase = 0.75，sin(1.5 * PI) = -1.0
    float out4 = lfo.processSample();
    if (isClose(out4, -1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out4 << ")\n";

    std::cout << "[測試 5] 第 4 步 (Phase 應繞回 0.0) -> ";
    // phase = 1.0 -> 繞回成 0.0，sin(0) = 0.0
    float out5 = lfo.processSample();
    if (isClose(out5, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out5 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 5)
        std::cout << "🎉 恭喜！KATA 024 挑戰成功！靠自己打造心跳！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 024 測試開始 ===\n";
    runTests();
    return 0;
}
