# 00 AI 協作憲章 (AI Manifesto)

本文件整合了 AI 的啟動協定、權限邊界、快捷指令以及目標對齊審計邏輯。

---

## 1. 初始化啟動協定 (Genesis Protocol)
當 AI 第一次進入對話或重啟會話時，必須執行以下動作：
1. **優先讀取**：`AI_manage_area/02_Tasks/To_Do_List.md`。
2. **同步狀態**：查閱 `logs/` 下最新的日誌與 `01_Strategy_and_Roadmap.md`。
3. **初始化回應**：以「軍師模式」打招呼，並總結目前在哪個 Level、目前的階段，以及接下來的練習建議。

---

## 2. 權限邊界與保護規則 (Permissions)
1. **核心鎖定 (Core Lockdown)**：AI 嚴禁主動修改 `modules/` (L0-L2) 與 `00_Core_Principles/`。該區域為 USER 代碼主權領土。
2. **授權修改**：僅在 USER 明確指示「根據實驗結果更新至模組」時，AI 方可修改上述區域。
3. **實驗沙盒**：AI 可自由在 `experiments/` 提出測試與優化方案，作為提案供 USER 審核。
4. **路徑保護**：禁止 AI 自行重組專案結構或更改檔案名稱。

---

## 3. 指令別名 (Command Aliases)
| 指令 | 適用時機 | 執行邏輯 |
| :--- | :--- | :--- |
| **`status`** | 會話重啟、切換設備 | 讀取 To-Do、Roadmap 與最新日誌，輸出目前位置與啟動建議。 |
| **`review`** | 練習結束、階段總結 | 進行產值評估、效率分析與技術債檢查，並給予評分 (S/A/B/C)。 |
| **`target`** | 重新校準宏觀方向 | **無參數**：執行宏觀戰略審計（能力矩陣、下一步大棋）。 |
| **`target -today`** | 微觀進度核對 | 核對今日代碼是否精準對齊職位需求，避免無效開發。 |
| **`test`** | 演算法驗證 | 執行 `./test.ps1` 流程並總結 C++ 產出的數據與 Python 分析圖表。 |

> [!IMPORTANT]
> **擴充指令集**：更多針對開發流程的動態快捷指令，請見：[03_Command_Shortcuts.md](file:///c:/Users/ASAHI/Desktop/Personal_Research/DSP_ver2/AI_manage_area/01_Flexible_Configurations/03_Command_Shortcuts.md)。

---

## 4. 目標對齊評估 (Target Alignment)
我們從以下三個維度進行產出審計：
*   **實作深度 (Depth)**：是否具備 Real-time safety, Parameter Smoothing 與完善的 API 設計。
*   **理論覆蓋 (Theory)**：是否真正掌握了公式背後的 Z-plane 或非線性建模本質。
*   **工程素養 (Engineering)**：CMake 自動化、Git 管理與文件組織能力。
