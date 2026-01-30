# 待修復與優化清單 (Bug & Improvements)

本文件追踪目前代碼中已知的技術債與技術問題。

---

## 🛑 待修正 (Active Bugs)

### 1. Delay 模組初始化規則缺陷
*   **問題**：`setDelayInSec` 會自動重設 `maxDelayInSec`，導致延遲時間無法在初始化後調大（被幽靈限制卡住）。
*   **影響**：動態調整延遲時會失效或導致記憶體存取風險。
*   **對策**：重構 `prepare()` 邏輯，明確區分「分配記憶體」與「設定目前參數」的動作。

---

## 🟡 優化中 (Under Optimization)

### 2. LFO / 參數切換點擊聲 (Clicks)
*   **問題**：在切換波形或大幅改變頻率時，訊號會產生突跳，造成聽覺上的 Clicks。
*   **對策**：實作 `SmoothedValue` (Level 0)，將參數變化進行低通濾波。

### 3. 位元與取樣率判斷 assert
*   **問題**：目前代碼缺乏邊界檢查。
*   **對策**：在 `processSample` 關鍵路徑加入 `assert` 或邊界 wrap 檢查。

---

## ✅ 已解決 (Completed)
*   (2026-01-28) Oscillator 多聲道相位偏移支援完成。
