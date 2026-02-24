# 09 目標對齊協定 (Target Alignment Protocol)

本文件定義了如何評估當前開發進度與長期職涯目標（Positive Grid DSP Engineer）之間的對齊程度。

## 1. 對齊評估指標 (Alignment Metrics)

### A. 實作深度 (Implementation Depth)
- **基礎 (Basic)**：僅完成功能，代碼雜亂。
- **產品級 (Production-Ready)**：包含 Real-time safety, Parameter Smoothing, Unit Testing, 且具備良好的 API 設計（如 Target-based 結構）。

### B. 理論覆蓋率 (Theoretical Coverage)
- 是否僅止於 Copy-paste 公式，還是真正理解了 Z-plane, Pole/Zero, 或非線性建模的數學本質。

### C. 工程素養 (Engineering Mindset)
- 檔案組織、CMake 自動化、Git 管理、以及對 AI 協作工具的掌握程度。

## 2. 檢核對象 (Audit Targets)
1. `target.md`：核心職缺需求。
2. `AI_manage_area/00_Core_Principles/05_Roadmap.md`：階段性里程碑。
3. `modules/`：實際產出的代碼品質。

## 3. 指令執行邏輯 (`target`)
1. **比較**：將今日進度與 `target.md` 中的 JD 需求進行逐項比對。
2. **分析**：指出目前在哪個維度（DSP/C++/Architect）偏離了目標，或進度超前。
3. **校準 (Correction)**：給出具體建議，將接下來的開發重心拉回核心目標上。
