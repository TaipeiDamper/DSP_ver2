# 📋 專案待辦清單 (To-Do List)

本文件紀錄短期與中期的開發任務。AI 在每次會話啟動時必須優先閱讀本清單。

---

## 1. 優先任務 (Priority Tasks)

### 🟢 ParamSmoother 效能優化 [已完成]
- [x] **邏輯修正 - `processBlock`**：已改為接收浮點數指標並進行區塊平滑處理。
- [x] **計算優化 - 一次乘法**：已手動更新數學公式，並通過 `test_smoother.cpp` 驗證。
- [x] **架構重構 - Target-based**：實作 `setTarget` 邏輯，與音訊線程解耦。
- [ ] **功能擴展 - 線性平滑**：新增線性平滑模式支援（可選任務）。

---

## 2. 後續開發任務 (Upcoming Development)

### 🟢 Biquad Filter 基礎實作 [已完成]
- [x] 實作純 C++ 二階濾波器類別 (RBJ 結構)。
- [ ] **驗證實作**：撰寫測試腳本驗證各類型濾波器的頻率響應。
- [ ] 深入濾波器係數計算優化（與標準理論對齊）。
- [ ] 穩定性測試與定點運算評估。

### 🟡 動態處理器 (Compressor)
- [ ] 實作 Envelope Follower (峰值檢測)。
- [ ] 實作 Side-chain 邏輯。
- [ ] 完成包含 Attack/Release 控制的完整 Compressor 模組。

### 🔴 跨平台與測試框架
- [ ] 建立 GTest 或簡單的自動化 Unit Testing 流程。
- [ ] 修正所有 Level 0-1 模組的 Doxygen 風格註釋。

---

## 📜 歷史已完成計畫 (Completed)
- [x] **ADSR 2.0 重構** (2026-02-23)：完成 Enum Class 狀態機。
- [x] **專案命名規範化** (2026-02-23)：全專案回歸小寫檔名與路徑解耦。
- [x] **地基建設** (2026-02-23)：CMake 成功編譯驗證。
