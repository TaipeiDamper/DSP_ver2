# 07 AI 權限與核心保護規則 (AI Permission & Protection Rules)

本文件定義了 AI 在此專案中的操作權限邊界，這是最高級別的 Core Principle。

## 1. 核心資產保護 (Core Asset Protection)
以下目錄與檔案被定義為 **「核心資產 (Core Assets)」**：
- **禁止修改 `modules/`**：AI 嚴禁在未經用戶針對「特定任務」明確授權的情況下，對 `modules/` 目錄下的任何內容進行寫入或修改（包含路徑修正）。AI 應保持此目錄為 Read-Only，僅作為檢索參考。
- **路徑解耦原則**：基於專案彈性，AI 應尊重用戶使用「扁平化 Include (如 #include "constant.h")」的設計，不應強制要求特定目錄層級的路徑。
- **建議權限**：AI 應將所有優化建議優先實踐於 `experiments/` 資料夾中。
- `AI_manage_area/00_Core_Principles/`：所有核心規則與啟動協定。

### 嚴格禁令：
- **AI 嚴禁在未經 USER 明確授權的情況下，主動修改或覆蓋任何「核心資產」。**
- 所有的修改建議必須先以對話形式提出，獲得 USER 確認後方可執行。
- AI 可以主動讀取核心資產以維持進度，但「寫入」權限受到嚴格限制。

## 2. 實驗與日誌區權限 (Flexible Area Permission)
以下目錄屬於 **「靈活區 (Flexible Area)」**，AI 具有較高的主動權：
- `experiments/`：AI 可以主動建議並建立新的測試程式或原型。
- `logs/`：AI 應負責每日進度的整理與記錄。
- `AI_manage_area/01_Flexible_Configurations/`：關於對話人格 (Persona) 或臨時協作模式的設定，AI 可以根據 USER 反饋進行微調。

## 3. 待辦清單優先原則 (To-Do List Priority)
- **主動檢查**：在每次新會話啟動、或 USER 詢問「接下來該做什麼」時，AI **必須** 優先檢閱 `AI_manage_area/02_Tasks/To_Do_List.md`，以確保建議與既定計畫一致。
- **動態更新**：當 USER 交付新任務或討論出明確優化項時，AI 應主動建議將其加入待辦清單。

## 4. 規則衝突處理
如果 AI 發現 USER 的要求與 `00_Core_Principles` 中的規則衝突，AI **必須** 主動提醒 USER，並詢問是否要更新核心規則。

---
*本規則旨在防止 AI 過度自動化導致核心演算法邏輯出錯或專案目標偏移。*
