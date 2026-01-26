# DSP 系統架構與設計指南

本文件整合了關於 DSP 模組分層、設計模式範例以及記憶體管理策略的指導原則。

---

## 1. DSP 模組分級判斷指南 (Module Level Guide)

### 核心判斷邏輯
我們將模組分為三個層級，判斷的關鍵在於**「依賴關係」**與**「功能複雜度」**。

### Level 0: dsp_core (地基/工具)
**定義：** 最底層的基礎設施。它們通常**不直接處理**「一段音樂」，而是提供處理音樂所需的數學或容器。
*   **關鍵問題**：
    *   這是一個資料結構嗎？ (如：Buffer)
    *   這是一個純數學公式嗎？ (如：內插法、dB轉換)
    *   如果我把這個檔刪了，是不是幾乎所有的 Audio Code 都會掛掉？
*   **判斷特徵**：通常不依賴其他音訊模組，只依賴標準庫 `<vector>`, `<cmath>`。
*   **例子**：`RingBuffer`, `Wavetable`, `Interpolation`, `Decibels`, `Constants`, `SmoothedValue` (參數平滑)。

### Level 1: dsp_building_blocks (零件/單體)
**定義：** 訊號處理的最小單位。它們是**「會動的」**，有狀態 (State)，接受輸入並產生輸出。
*   **關鍵問題**：
    *   它是否對訊號進行了具體的加工 (變大聲、變頻率、變波形)？
    *   它是否通常作為更大系統的一部分出現？
    *   它是否依賴 Level 0 的工具 (如用到 RingBuffer 或 PI)？
*   **判斷特徵**：單一功能，單一職責。
*   **例子**：
    *   `Gain`：如果你實作了「平滑參數 (Smoothed Value)」，它就是一個有狀態的處理單元。
    *   `BiquadFilter` (濾波器)
    *   `Oscillator` (振盪器)
    *   `Envelope` (封包)
    *   `Panner` (聲像控制)

### Level 2: dsp_effects (成品/系統)
**定義：** 完整的音效邏輯。通常是由多個 Level 1 零件組裝而成的。
*   **關鍵問題**：
    *   這東西能不能直接做成一個簡單的 VST Plugin 拿去賣(或送人)？
    *   它裡面是不是包了好幾個其他的物件 (例如 Delay 裡面包了 Filter 做回授)？
*   **判斷特徵**：組合式邏輯 (Composition)。
*   **例子**：
    *   `SimpleDelay` (組合了 RingBuffer + Interpolation + Gain)
    *   `Chorus/Flanger` (組合了 Delay + LFO Oscillator)
    *   `DiodeClipper` (雖然只有單一功能，但如果是電路模擬這種複雜邏輯，通常算完整的效果模組)
    *   `Compressor` (組合了 Level Detector + Gain Reduction)

### Level 3: The Plugin (JUCE 整合層)
**這就是 JUCE 負責的地方！**
你不需要在 `modules` 裡寫一個 "Level 3 App"，因為 `plugins/YourPlugin` 就是 Level 3。

*   **職責區分**：
    *   **Level 0-2 (Pure DSP)**：完全**不知道** JUCE 的存在。不含任何 `juce::AudioProcessor` 或 `juce::Component` 程式碼。這讓它們可以在 Console APP 或 Python 裡被測試。
    *   **Level 3 (JUCE Plugin)**：負責「髒活」。
        *   管理參數 (APVTS)。
        *   處理 MIDI 輸入。
        *   繪製 UI。
        *   **最重要**：在 `processBlock` 裡呼叫你的 Level 2 物件 (`myEffect.process(...)`)。

---

## 2. 設計模式範例：從零建構 Flanger

這份範例展示如何依照 Level 架構，從底層向上堆疊出一個 Flanger 效果器。

### 需求分析
我想要做一個 **Flanger (法蘭格效果器)**。
原理： `原音 + (被 LFO 調變的延遲訊號)`

分解需求：
1.  能存聲音、讀聲音的東西 -> **Delay Line**
2.  會自動上下跑的數值產生器 -> **Oscillator (LFO)**

### 選擇/製作零件 (Level Selection)

**步驟 A: 準備 LFO (Level 1)**
*   在 `modules/level1_dsp_building_blocks/` 檢查有無 `Oscillator`。
*   沒有的話新建一個，可能需要 `Constants::PI` (Level 0)。

**步驟 B: 準備 Delay Line (Level 1)**
*   雖然 `RingBuffer` (Level 0) 已經是一個圓形陣列，但它太原始。
*   在 Level 1 寫一個 `DelayAlg` (或 `DelayLine`)，內部持有 `RingBuffer` (Level 0) 並實作 `getInterpolatedSample`。

### 組裝成品 (Level 2)
建立 `modules/level2_dsp_effects/Flanger.h`。

```cpp
#include "../level1/Oscillator.h"
#include "../level1/DelayAlg.h"

class Flanger {
public:
    void process(float input) {
        // 1. LFO 算出現在要延遲多久
        float currentDelayTime = lfo.process(); 
        
        // 2. 叫 DelayLine 給我那個時間點的聲音
        float wetSignal = delayLine.read(currentDelayTime);
        
        // 3. 把聲音塞進 DelayLine 供未來使用
        delayLine.write(input);
        
        // 4. 混合 (Flanger 的輸出)
        return input + wetSignal; 
    }

private:
    Oscillator lfo;   // Level 1
    DelayAlg delayLine; // Level 1
};
```

### 維護與升級 (The Power of Modular Design)
**情境**：LFO 頻率改變時有雜音。
**動作**：
1.  去改 `Oscillator.h` (Level 1)，加入 `SmoothedValue` (Level 0)。
2.  結果：`Flanger` 自動變好聽了。下次做 `Chorus` 時，LFO 也自動升級了。

---

## 3. C++ 指標 (Pointer) 使用策略：Real-time Audio

在即時音訊處理 (Audio Thread) 中，記憶體管理是效能的關鍵。

### 核心原則：能不用指標 (Pointer)，就不要用
**Stack Memory (堆疊)** 比 **Heap Memory (堆積)** 更快、更安全。

### 1. 優先使用 "Stack Allocation" (物件直接宣告)
在 Level 2 包含 Level 1 物件時，優先像這樣寫：

```cpp
class Flanger {
    Oscillator lfo;    // 好！物件就在 Flanger 肚子裡
    DelayLine delay;   // 好！記憶體位置是連續的
};
```
**優點**：Cache Friendly (讀取極快)，且沒有 Memory Leak 風險。

### 2. 什麼時候必須用 Pointer (或 Reference)？
通常在 Level 2 只有兩種情況需要指標：

**A. 共享資源 (Sharing Resources)**
例如巨大的 `Wavetable` (波表)。多個 Oscillator 應共用同一份。
```cpp
class Oscillator {
public:
    Oscillator(const Wavetable& sharedTable) : table(sharedTable) {} 
private:
    const Wavetable& table; // 只是參考，不擁有它
};
```

**B. 多型 (Polymorphism) - 請謹慎使用**
如果想隨時切換 Filter 種類，可能會想用 `Filter*`。
*   **警告**：虛擬函式 (`virtual function`) 在 DSP 迴圈裡有微小效能損耗。
*   **替代方案**：優先用 `Template`，或宣告兩個不同物件。

### 3. Level 3 (JUCE) 與 Level 0-2 的差異
JUCE 在 UI 層用很多 `std::unique_ptr` 和 `new`，因為 UI 生命週期複雜。
但在 **DSP Module** (Level 0-2) 裡：
1.  **90% 的情況**：直接宣告物件成員。
2.  **10% 的情況**：用 `const &` 或 `*` (Raw Pointer) 共享大資料。
3.  **避免**：`std::shared_ptr` (Reference Counting 有風險)。
