# 03 待修復與優化追蹤 (Issue Tracker)

本文件追蹤當前代碼中存在的技術債、Bug 以及待優化的性能熱點。

---

## 🛑 待修正 (Active Bugs)
1. **Delay 模組初始化陷阱**：`setDelayInSec` 會覆蓋 `maxDelay` 導致限制異常，需重構 `prepare()` 以區分內存分配與參數設定。
2. **濾波器係數一致性**：確保 `Filter` 基類在修改參數時正確觸發 `updateCoeff()`。

---

## 🟡 優化中 (Under Optimization)
1. **數位點擊聲 (Clicks)**：在 LFO 或參數劇烈變動時缺少 Smoother 保護。
2. **安全斷言 (Safety Asserts)**：在 `processSample` 關鍵路徑加入邊界檢查，防止溢位。
3. **Biquad 穩定性**：針對極高 Q 值下的濾波器數值爆炸進行守護。

---

## ✅ 已解決 (Completed)
*   (2026-02-23) ADSR 2.0 Enum 狀態機重構完成。
*   (2026-02-24) ParamSmoother 2.0 (Target-based) 重構完成。
*   (2026-01-28) Oscillator 多聲道相位支援。
