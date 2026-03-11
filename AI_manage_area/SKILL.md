# 專案管理與協作規範 (Project Management & Collaboration)

## 📌 概述
本 Skill 負責維護 `DSP_ver2` 專案的運作秩序，定義了 AI 與 USER 之間的協作邊界、指令系統以及任務追蹤邏輯。

## 🧩 核心組件
- **原則與標準**：參見 `00_Core_Principles/`
  - `00_AI_Manifesto.md`: 初始化協定與權限邊界。
  - `02_Technical_Standard.md`: 目錄分級與 DSP 撰寫規範。
- **動態配置**：參見 `01_Flexible_Configurations/`
  - `03_Command_Shortcuts.md`: 快捷指令定義。
- **任務管理**：參見 `02_Tasks/`
  - `To_Do_List.md`: 主要進度追蹤。

## 🛠️ 維護邏輯
1. **狀態同步**：每次對話開始或使用 `status` 時，AI 會自動掃描此目錄下的最新變更。
2. **任務標記**：更新 `To_Do_List.md` 時必須遵循 `(feat)`, `(debug)`, `(opt)` 等標籤規範。
3. **路徑保護**：遵守「核心鎖定」規則，未經授權禁止修改 `modules/`。

## 🎯 執行目標
確保所有開發行為完全對齊「專業 DSP 工程師」的職位需求，避免無效開發，並保持工程文檔的即時性。
