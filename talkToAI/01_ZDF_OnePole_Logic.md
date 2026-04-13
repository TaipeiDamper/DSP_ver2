# VA Modeling Deep Dive: 01. ZDF One-Pole Filter

## 1. 核心概念 (The Core)
傳統數位濾波器在 Feedback 過程中存在 1-sample delay，導致在高頻處行為不正確。
**ZDF (Zero-Delay Feedback)** 透過代數預解 (Algebraic Solution)，消除了這個延遲，使數位模擬能完美貼合類比電路的物理拓撲。

## 2. 拓撲結構 (Topology)
我們模擬的是類比積分器 (Integrator)，使用 **Trapezoidal Rule (梯形準則)**。

### 關鍵參數：
- **g (Gain)**: 頻率係數。公式：$g = \tan(\frac{\pi \cdot f_c}{f_s})$
- **s (State)**: 內部狀態，代表電容儲存的電荷。
- **1 / (1 + g)**: 這是「解方程」後得到的補償因子，用來消除回授延遲。

## 3. C++ 工業級實作 (Reference Code)

```cpp
#pragma once
#include <cmath>

class ZDFOnePoleLPF {
public:
    void prepare(float sr) { sampleRate = sr; }
    
    void setCutoff(float cutoffHz) {
        float pi = 3.1415926535f;
        g = std::tan(pi * cutoffHz / sampleRate);
    }

    float processSample(float x) {
        // 解方程：計算當前時刻即時產生的誤差 v
        float v = (x - s) * (g / (1.0f + g));
        
        // 輸出 y (Low-pass)
        float y = v + s;
        
        // 更新狀態 s (為下一個 sample 準備)
        s = y + v;
        
        return y;
    }

private:
    float s = 0.0f;
    float g = 0.0f;
    float sampleRate = 44100.0f;
};
```

## 4. 延伸思考 (Bonus)
- **High-pass 輸出**: 只要回傳 `x - y` 即可。
- **All-pass 輸出**: 只要回傳 `y - (x - y)` (即 $LP - HP$) 即可。
這就是為什麼 TPT (Topology Preserving Transform) 非常強大。
