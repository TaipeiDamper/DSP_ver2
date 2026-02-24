# 🧠 DSP & C++ 快速記憶庫 (Mnemonic Treasury)

本文件紀錄開發過程中容易遺忘的核心邏輯、架構口訣與技術直覺。此文件作為 AI 出題考核與 USER 快速複習的基準。

---

## 1. 指標 vs. 引用：角色定位口訣

> **「內部擁有直接用，外部手動看工種；數據工頭拿指標，資源分包交引用。」**
> 
> 1. **內部關係 (Ownership)**：A 擁有 B (器官)，直接以 Value 形式組合，正常呼叫。
> 2. **外部關係 (Interface)**：A、B 互不隸屬 (通訊)：
>    - **動手做事 (Worker)**：涉及樣本掃描、效能優先時，傳遞 **`Ptr (*)`**。
>    - **傳遞資源 (Supervisor)**：涉及物件傳包、確保存在時，傳遞 **`Ref (&)`**。
---

## 2. 命名規範與風險規避
*   **Shadowing 規避**：參數命名加底線（如 `sampleRate_`）或明確前綴（如 `inputBuffer`），避免與類別成員變數同名導致邏輯錯誤。
*   **CamelCase**：專案統一採用小寫開頭的 camelCase。

---

## 3. Real-time Safety 鐵律 (不可觸碰紅線)
*   ❌ **No Allocation**：禁止在音訊迴圈中使用 `new`, `malloc`, `std::vector::resize`。
*   ❌ **No I/O**：禁止在迴圈中輸出 `std::cout` 或讀寫檔案。
*   ❌ **No Blocking**：禁止使用 Mutex 或耗時長的 Lock。

---
*最後更新：2026-02-24*
