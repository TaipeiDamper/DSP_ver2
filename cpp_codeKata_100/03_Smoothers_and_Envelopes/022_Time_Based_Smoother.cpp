#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 022: Time-Based Smoother (根據時間轉換係數的平滑器)
 * ==============================================================================
 *
 * [說明]
 * 上一題我們直接設定 coeff = 0.5。但在真實的音訊插件裡，我們通常會讓使用者用
 * 毫秒 (ms) 來設定平滑時間，像是 "Attack 50ms" 或 "Mix Smoothing 10ms"。
 *
 * 我們需要一個公式，根據【目標時間(秒)】與【取樣率】，算出我們該用的 coeff。
 * 標準的公式 (基於 RC 電路的時間常數 tau) 是計算一個 alpha 值：
 *
 * alpha = std::exp(-1.0f / (timeInSeconds * sampleRate));
 *
 * 然後因為你比較喜歡用「增量形式」(Incremental Form) 來寫平滑器：
 * y += (x - y) * coeff
 * 所以我們要儲存的 coeff 其實是 = 1.0f - alpha。
 *
 * [任務]
 * 1. 在 setTimeConstant 中實作這個公式，把時間 (ms) 轉換成對應的 coeff。
 * 2. 記得處理 timeInMs 為 0 的情況，如果時間為 0，coeff 應該直接設為 1.0f (瞬間到達)。
 * 3. 實作 processSample 的邏輯。
 */

class TimeBasedSmoother
{
private:
    float z1 = 0.0f;
    float coeff = 1.0f; // 預設 1.0 代表不平滑，瞬間到達

public:
    void reset()
    {
        z1 = 0.0f;
    }

    void setTimeConstant(float timeInMs, float sampleRate)
    {
        // ------------------------------------------------------------------
        // 你的程式碼寫在這裡：
        // 1. 檢查 timeInMs 是否極小 (例如 <= 0.0f)，如果是，coeff 設為 1.0f
        if (timeInMs < 0.0001f)
        {
            coeff = 0.0f;
        }
        // 2. 把 timeInMs 換算成秒 (timeInSeconds)
        float timeInSec = timeInMs / 1000.0f;
        // 3. 計算並儲存 coeff
        // 提示： coeff = 1.0f - std::exp(-1.0f / (timeInSeconds * sampleRate));
        coeff = exp(-1.0f / (timeInSec * sampleRate));

        // ------------------------------------------------------------------
    }

    float processSample(float input)
    {
        // 直接把上一題寫好的平滑公式搬過來用
        float output = z1 * coeff + input * (1.0f - coeff);
        z1 = output;
        return output;
    }
};

// ==========================================
// 測試區塊
// ==========================================
void runTests()
{
    TimeBasedSmoother smoother;
    int passed = 0;
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.001f; };

    float sr = 1000.0f; // 為了方便人工驗算，假設取樣率是 1000 Hz

    std::cout << "[測試 1] 極小時間保護 (0ms) -> ";
    smoother.setTimeConstant(0.0f, sr);
    float out1 = smoother.processSample(1.0f);
    if (isClose(out1, 1.0f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out1 << ")\n";

    smoother.reset();

    std::cout << "[測試 2] 正常時間常數 (1000ms, 即 1 秒) -> ";
    // 在 1000 Hz 下，1秒剛好是 1000 個樣本
    // exp(-1.0 / (1 * 1000)) 約等於 exp(-0.001) 約 0.999
    // coeff = 1.0 - 0.999 = 0.001
    smoother.setTimeConstant(1000.0f, sr);
    float out2 = smoother.processSample(1.0f);
    if (isClose(out2, 0.001f))
    {
        std::cout << "PASS\n";
        passed++;
    }
    else
        std::cout << "FAIL (結果: " << out2 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 022 挑戰成功！\n";
    else
        std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main()
{
    std::cout << "=== KATA 022 測試開始 ===\n";
    runTests();
    return 0;
}
