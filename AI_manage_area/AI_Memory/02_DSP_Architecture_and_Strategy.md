# 02 DSP 系統架構與代碼規範策略

本文件定義了專案的模組分級、設計模式以及與效能相關的 C++ 撰寫規範。

---

## 1. 模組分級 (Module Levels) 與 撰寫策略

| 層級 (Level) | 定義 | 撰寫策略 (File Strategy) |
| :--- | :--- | :--- |
| **Level 0: dsp_core** | 數學工具、容器、常數 (如：`RingBuffer`, `Constants`) | **強制 Header-Only** (Template 為主，效能最優) |
| **Level 1: building_blocks** | 有狀態的處理單元 (如：`Oscillator`, `Filter`) | **首選 Header-Only** (通常 < 200 行，便於 Inline 優化) |
| **Level 2: dsp_effects** | 成品音訊邏輯 (如：`Flanger`, `Delay`) | **視複雜度決定** (邏輯簡單則 Header-only，極其複雜則拆分 .h/.cpp) |
| **Level 3: The Plugin** | JUCE 整合層 (UI, 參數管理, DAW 通訊) | **標準 .h / .cpp** (符合 JUCE 框架要求) |

---

## 2. 核心設計原則：純粹性與解耦

*   **Pure DSP 原則 (L0 - L2)**：
    *   **完全不知道 JUCE 的存在**。模組內部不應包含任何 `juce::` 命名空間的代碼。
    *   這確保了演算法可以在任何地方測試（Console, Python, 或任何框架）。
*   **組合式開發 (Composition)**：
    *   例如 `Flanger` (Level 2) 內部應該持有 `Oscillator` (Level 1) 和 `DelayLine` (Level 1)，而不是重複寫邏輯。

---

## 3. Real-time Audio 記憶體管理 (音訊執行緒規範)

為了確保在即時處理中不產生掉音（Glitch），請遵循以下 C++ 策略：

1.  **優先使用 Stack 分配**：
    *   在 Level 2 包含成員時，直接宣告物件（如 `Oscillator lfo;`），避免在構造函數中使用 `new`。
    *   這樣記憶體位置連續，讀取速度最快且安全。
2.  **避免在音訊迴圈 (processBlock) 中做的事情**：
    *   ❌ **No Heap Allocation**：嚴禁呼叫 `malloc`, `new`, `std::vector::resize` 等。
    *   ❌ **No I/O**：嚴禁在處理音訊時讀寫檔案或輸出 Log。
    *   ❌ **No Lock**：避免使用 Mutex，防止優先權反轉導致音訊中斷。
3.  **指標使用時機**：
    *   僅在需要 **共享資源**（如巨大的 Wavetable）或 **多型**（需慎用）時才使用 Raw 指標或引用。

---

## 4. 命名與結構規範
*   所有的 Core Code 必須保持在 `modules/` 下原地不動，不要複製到個別專案中。
*   統一使用 `prepare()`, `reset()`, `processSample()` 作為標準處理 API。
