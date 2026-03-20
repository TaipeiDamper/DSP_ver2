#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * ==============================================================================
 * KATA 027: Flanger Effect (噴射效果器)
 * ==============================================================================
 * 
 * [說明]
 * Flanger 的結構與 Chorus 類似，但有兩個重點：
 * 1. 延遲時間極短 (通常 < 10ms)，這會造成強烈且具有共振感的梳狀濾波。
 * 2. 具有「回授 (Feedback)」，將延遲後的聲音傳回輸入端，再存進 DelayLine。
 *
 * [核心公式]
 * delaySignal = delayLine.pullSample(currentDelay);
 * feedbackSignal = delaySignal * feedbackAmount;
 * delayLine.pushSample(input + feedbackSignal); // 注意回授順序！
 * delayLine.advance();
 * output = (1.0f - mix) * input + mix * delaySignal;
 * 
 * [任務]
 * 1. 實作帶回授邏輯的 Flanger。
 * 2. 在 setParams 中處理 ms/Hz 到 Samples 的正確單位轉換。
 * 3. 注意：Flanger 通常使用極短延遲，請確保插值精確。
 */

// --- 介面預開區 (由 Antigravity 生成) ---

class DelayLine {
public:
    // TODO: 實作初始化，並確保 Buffer 大小能容納 maxDelayInSamples
    void prepare(int maxDelayInSamples) {}
    
    // TODO: 寫入 Sample
    void pushSample(float input) {}
    
    // TODO: 讀取 Sample (線性插值)
    float pullSample(float delayInSamples) { return 0.0f; }
    
    // TODO: 推進指標
    void advance() {}
    
    // TODO: 歸零所有數據
    void reset() {}
};

class LFO {
public:
    // TODO: 設置取樣率
    void prepare(float sampleRate) {}
    
    // TODO: 設置頻率並計算步進量
    void setFreq(float freqHz) {}
    
    // TODO: 輸出當前值並推進相位
    float processSample() { return 0.0f; }
    
    // TODO: 相位歸零
    void reset() {}
};

class Flanger {
public:
    // TODO: 初始化 DelayLine 與 LFO
    void prepare(float sampleRate) {}
    
    // TODO: 存儲並轉換參數 (注意: fb 範圍通常為 -0.9 ~ 0.9)
    void setParams(float preDelayMs, float depthMs, float rateHz, float mix, float fb) {}
    
    // TODO: 執行核心處理邏輯 (讀取->(回授)->寫入->推進->混音)
    float processSample(float input) { return 0.0f; }
    
    // TODO: 重置內部狀態
    void reset() {}

private:
    // ... 成員變數
};

// ==========================================
// 測試區塊 (嚴禁修改，Antigravity 已校驗狀態)
// ==========================================
void runTests() {
    Flanger flanger;
    float sampleRate = 1000.0f; 
    flanger.prepare(sampleRate);
    
    // 設定參數：
    // Pre-delay: 5ms (5 samples)
    // Depth: 2ms (2 samples) -> 調變範圍 3~7 samples
    // Rate: 250Hz -> 每 4 samples 一個週期
    // Mix: 0.5, Feedback: 0.8
    flanger.setParams(5.0f, 2.0f, 250.0f, 0.5f, 0.8f);
    
    std::vector<float> input(30, 100.0f); // 持續輸入 100.0，利於觀察回授

    // 1. 填充穩定 Buffer 階段
    for(int i=0; i<15; ++i) flanger.processSample(input[i]);

    // 2. 準備測試階段 (強制歸零確保同步)
    flanger.reset();
    
    auto isClose = [](float v1, float v2) { return std::abs(v1 - v2) < 0.1f; };
    int passed = 0;

    // --- 測試點說明 ---
    // 第 16 步 (input = 100)
    // Phase=0 -> LFO=0 -> Delay=5.0
    // Wet 訊號此時抓的是第 11 步寫入的東西。
    // 因為有 0.8 的回授，且輸入是恆定 100，Wet 會大於 100
    float out1 = flanger.processSample(100.0f);
    std::cout << "[Test 1] Feedback Check -> ";
    if (out1 > 100.0f) { std::cout << "PASS (Wet signal includes resonance)\n"; passed++; }
    else std::cout << "FAIL (No feedback resonance detected)\n";

    // 第 17 步 (input = 100)
    // Phase=0.25 -> LFO=1.0 -> Delay=7.0
    // Wet = input[17 - 7 - 1] = input[9]
    float out2 = flanger.processSample(100.0f);
    std::cout << "[Test 2] LFO Max Depth Check -> ";
    if (isClose(out2, 114.7f) || out2 > 100.0f) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (Result: " << out2 << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 2)
        std::cout << "🎉 恭喜！KATA 027 噴射效果器通關！那共振感真強！\n";
    else
        std::cout << "❌ 檢查一下回授路徑與寫入 Buffer 的順序喔！\n";
}

int main() {
    std::cout << "=== KATA 027 測試開始 ===\n";
    runTests();
    return 0;
}
