# C++ 檔案結構策略：Header-Only vs .h/.cpp

在 DSP 與 Audio 開發中，關於是否要拆分 `.h` (宣告) 與 `.cpp` (實作)，有兩種主要流派。

## 1. Header-Only 派 (推薦用於 Level 0 & Template)
就是把所有的實作都寫在 `.h` 檔裡 (或是 `.hpp`)。

### 適用情況
*   **Level 0 (Core Tools)**：像 `RingBuffer`、`Interpolation` 這種工具，通常會用到 C++ Template (樣板)。
*   **Template Class**：**強制要求**必須寫在 Header 裡，不能拆到 cpp。
*   **小型模組**：例如 `Decibels.h` 這種只有幾行算式的工具。

### 優點
*   **編譯優化**：編譯器看得到所有程式碼，更容易做 Inline (內聯) 優化，這對 DSP 效能很重要。
*   **方便使用**：只要 `#include` 一個檔案就能用，不用擔心 Linker Error。

### 範例 (RingBuffer.h)
```cpp
template <typename T>
class RingBuffer {
public:
    void write(T sample) { /* 實作直接寫在這 */ }
    T read() { /* 實作直接寫在這 */ }
};
```

---

## 2. 傳統 .h + .cpp 派 (推薦用於 Level 2 & 複雜 Level 1)
將宣告放在 `.h`，邏輯實作放在 `.cpp`。

### 適用情況
*   **大型模組 (Level 2)**：例如 `VerneReverb` 或 `ComplexSynthesizer`。
*   **不想暴露私有細節**：如果有 proprietary algorithm (專有演算法) 不想被看光，或者依賴了很重的第三方 Library。
*   **加快編譯速度**：當專案變超大，改一個 `.h` 不用全部重編譯。

### 缺點
*   **較難 Inline**：除非開啟 Link Time Optimization (LTO)，否則編譯器可能看不到 `.cpp` 裡的實作細節，導致無法 Inline 函數呼叫，略微影響效能。

---

## 結論與建議

**針對你的 DSP_ver2 專案：**

1.  **Level 0 (dsp_core)**
    *   **強制 Header-Only**。因為它們幾乎都會用到 Template (例如 `RingBuffer<float>`)，且函數都很短 (Inline 效能更好)。

2.  **Level 1 (dsp_building_blocks)**
    *   **推薦 Header-Only**。例如 `Oscillator` 或 `OnePoleFilter`，程式碼通常都在 100-200 行以內。寫在 `.h` 裡乾淨俐落，且效能最好。

3.  **Level 2 (dsp_effects)**
    *   **自由選擇**。
    *   如果邏輯很單純 (如 `SimpleDelay`) -> Header-Only。
    *   如果邏輯超複雜 (如 `AnalogModelledFilter`) -> 拆成 `.cpp` 會讓 Header 易讀性比較好。

**總結一句話：預設先都寫在 `.h` 裡 (Header-Only)。等你發現這個檔案大到這台電腦開起來會 lag，或者編譯時間太久，再考慮拆 `.cpp`。**
