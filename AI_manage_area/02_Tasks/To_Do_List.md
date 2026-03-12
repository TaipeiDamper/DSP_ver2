# 📋 專案待辦清單 (To-Do List)

本文件紀錄短期與中期的開發任務。AI 在每次會話啟動時必須優先閱讀本清單。

---

## 1. 優先任務 (Priority Tasks)

### 🟢 ParamSmoother 效能優化 [已完成]
- [x] **邏輯修正 - `processBlock`**：已改為接收浮點數指標並進行區塊平滑處理。
- [x] **計算優化 - 一次乘法**：已手動更新數學公式，並通過 `test_smoother.cpp` 驗證。
- [x] **架構重構 - Target-based**：實作 `setTarget` 邏輯，與音訊線程解耦。
### 🟢 CMake 基礎建設與深度學習 [已完成]
- [x] **建立全域 CMake 架構**：已實作 INTERFACE/STATIC 庫傳遞機制，解決路徑引用問題。
- [x] **熟悉 CMake 語法與邏輯**：成功掌握 Target-based modern CMake，並建立 `./test` 自動化流程。

### 🟢 基礎模組驗證與整合 [已完成]
- [x] **Biquad 脈衝響應驗證 (Impulse Response)**：
    - [x] 撰寫 `test_1st_half.cpp`：生成 Impulse 並輸出 WAV。
    - [x] 撰寫 `test_2nd_half.py`：透過 FFT 分析頻率響應並作圖。
    - [x] **建立一鍵自動化 `./test` 指令**：整合編譯、執行與繪圖流程。
- [x] **ADSR 狀態機視覺化驗證**：
    - [x] 成功將 `Envelope` 升級為支援 Linear/Exponential 混合模式。
    - [x] 實作物理時間對齊 ($5\tau$) 與接力同步邏輯。
    - [x] 透過 `./test` 視覺化驗證 re-trigger 行為。
- [ ] **JUCE 接口實驗**：在 `experiments/` 建立一個極簡 JUCE 專案，嘗試將 `DSP_ver2/modules` 掛載進去。
- [ ] **AI Audio 原型嘗試**：整理現有的 LSTM 對照組數據，研究如何透過 `RTNeural` 或自行撰寫矩陣運算加載權重。

### 🟡 動態處理器 (Compressor) [研發中]
- [x] **閱讀與架構設計 [2026-03-11]**：研讀 JAES 論文，並完成 V1 基礎線性架構設計。
- [x] **Envelope Follower 實作 [2026-03-11]**：完成一階 IIR 峰值檢測邏輯，支援非對稱 Attack/Release。
- [x] **Static Curve 基礎邏輯 [2026-03-11]**：完成線性空間 (Linear Domain) 的增益縮放公式。
- [ ] 完成包含 Threshold, Ratio, Attack, Release 控制的完整 Feed-forward Compressor 模組 (V1.1 封裝)。
- [ ] 進階 V2 (dB Domain) 轉換與 Soft-knee 實作。
- [ ] **重構 Envelope Follower 實作 (Leaky Integrator)**：
    - [ ] 將 `alpha` 改為 `Coeff` (步長比例)，並在 `updateCoeffs` 預先計算 `1.0f - exp`。
    - [ ] 改用增量形式 `y += (x - y) * coeff` 以減少乘法運算並提升物理直覺。

---

## 2. 後續開發任務 (Upcoming Development)

### 🟢 Biquad Filter 基礎實作 [已完成]
- [x] 實作純 C++ 二階濾波器類別 (RBJ 結構) (已重構為單一類別設計)。
- [x] **驗證實作**：撰寫測試腳本驗證各類型濾波器的頻率響應（LPF, HPF, BPF, Shelf 等），確認 -3dB 截止點與滾降斜率。
- [x] 深入濾波器係數計算優化（已確認與 RBJ Cookbook 標準對齊）。
- [x] 批次穩定性測試與圖表量測評估（全家族圖線驗證通過）。

### 🔴 跨平台與測試框架
- [ ] 建立 GTest 或簡單的自動化 Unit Testing 流程。
- [ ] 修正所有 Level 0-1 模組的 Doxygen 風格註釋。

---

## 📜 歷史已完成計畫 (Completed)
- [x] **ADSR 2.0 重構** (2026-02-23)：完成 Enum Class 狀態機。
- [x] **專案命名規範化** (2026-02-23)：全專案回歸小寫檔名與路徑解耦。
- [x] **地基建設** (2026-02-23)：CMake 成功編譯驗證。
