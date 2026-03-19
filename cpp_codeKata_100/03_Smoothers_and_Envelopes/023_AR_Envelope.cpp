#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 023: Attack-Release Envelope (起伏包絡)
 * ==============================================================================
 *
 * [說明]
 * 這是 Compressor 或 Auto-Wah 效果器的靈魂核心：Attack/Release 平滑器。
 *
 * 它的原理和 KATA 021, 022 完全一模一樣，唯一的差別在於：
 * 它有「兩個」不同的平滑時間 (Attack Time 和 Release Time)。
 *
 * 規則非常簡單：
 * 💡 若新進來的 input > 目前的狀態 (z1)，代表訊號在「上升」，使用 Attack 係數。
 * 💡 若新進來的 input <= 目前的狀態 (z1)，代表訊號在「下降」，使用 Release 係數。
 *
 * [任務]
 * 我們已經幫你把時間換算成對應的 memory 係數了：
 * attackMemory = exp(-1.0f / (attackSec * sampleRate))
 * releaseMemory = exp(-1.0f / (releaseSec * sampleRate))
 *
 * 請實作 processSample。
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

        // 計算留存係數 (如果時間 <= 0，強制 memory 變成 0.0，代表不留舊聲音)
        attackMemory = (attackSec > 0.0f) ? std::exp(-1.0f / (attackSec * sampleRate)) : 0.0f;
        releaseMemory = (releaseSec > 0.0f) ? std::exp(-1.0f / (releaseSec * sampleRate)) : 0.0f;
    }

    float processSample(float input)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 判斷現在是上升 (Attack) 還是下降 (Release) 階段？
        //    (提示：拿 input 比較 z1)
        float memory = 0.0f;
        if (input > z1)
        {
            memory = attackMemory;
        }
        else
        {
            memory = releaseMemory;
        }
        // 2. 選擇你要用的 memory 係數
        // 3. 執行標準的 Direct Form 平滑：z1 = (z1 * memory) + (input * (1.0f - memory))
        z1 = (z1 * memory) + input * (1.0f - memory);
        // 4. 更新 z1 並回傳

        return z1; // 請修正
        // ------------------------------------------------------------------
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    AREnvelope env;
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    // 假設取樣率 1000Hz (1毫秒就是一個樣本)
    // 讓 Attack 是 1000ms (極慢上升)，Release 是 0ms (瞬間掉落)
    env.setTimes(1000.0f, 0.0f, 1000.0f);

    std::cout << "[測試 1] 極慢上升 (Attack階段) -> ";
    // z1原本是 0.0，input 給 1.0。因為 1.0 > 0.0，所以走 Attack (memory 約 0.999)
    // 第一步應該是 0 * 0.999 + 1.0 * 0.001 = 0.001
    float out1 = env.processSample(1.0f);
    if (isClose(out1, 0.001f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out1 << ")\n";

    std::cout << "[測試 2] 瞬間掉落 (Release階段) -> ";
    // 現在 z1 是 0.001，input 突然變 0.0。因為 0.0 < 0.001，所以走 Release (設定 0ms，memory 是 0.0)
    // 應該要瞬間變成 input 的數值 0.0
    float out2 = env.processSample(0.0f);
    if (isClose(out2, 0.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out2 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 023 挑戰成功！掌握 Compressor 靈魂！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 023 測試開始 ===\n";
    runTests();
    return 0;
}
