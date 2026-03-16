# 02 技術規範與開發標準 (Technical Standard)

本文件整合了目錄分級、DSP 撰寫策略、C++ 音訊規範以及 CMake 執行指南。

---

## 1. 目錄架構與檔案分級
| 層級 | 定義 | 策略 (Strategy) | Include 規範 |
| :--- | :--- | :--- | :--- |
| **Level 0: dsp_core** | 數學原子、容器、常數 | **強制 Header-Only** | 禁依賴其他層 |
| **Level 1: building_blocks** | 單一功能處理器 (Filter, Osc) | **首選 Header-Only** | 僅能依賴 L0 |
| **Level 2: dsp_effects** | 組合效果器 (Reverb, Delay) | **視複雜度拆分** | 僅能依賴 L0/L1 |
| **Level 3: Plugin** | JUCE 整合層 (UI, 參數管理) | **標準 .h / .cpp** | 負責對接所有 L0-L2 |

---

## 2. DSP 撰寫規範 (Real-time Audio)
1. **Pure DSP 原則**：L0-L2 完全不應出現 `juce::` 命名空間，保持演算法透明。
2. **Audio Thread 禁忌**：
        *   ❌ **No Heap Allocation** (Malloc/New)
        *   ❌ **No I/O** (Logging/Printing/File Access)
        *   ❌ **No Locking** (Mutex/Blocking Calls)
3. **數據通訊選擇**：
        *   **指標 (`float*`)**：用於 **Worker (做事)**。適合樣本流水線，利於編譯器 SIMD 優化。
        *   **引用 (`T&`)**：用於 **Supervisor (傳資源)**。適合物件傳遞、確保非空安全性。

---

## 3. 現代化 CMake 與 VS 流程
*   **模式**：開啟 Visual Studio 選擇「開啟資料夾 (Folder View)」開啟 `DSP_ver2` 根目錄。
*   **指令**：
        *   `cmake -B build`：配置環境並生成緩存。
        *   `cmake --build build --target [Name]`：從命令列編譯特定目標。
*   **測試流程**：在 `experiments/console_tests/` 新增 `.cpp` 並寫入 `main`，CMake 將自動偵測並生成執行目標。

---

## 4. 任務標記規範 (Tagging)
AI 更新 To-Do 時應自動標註：
- **(debug)**: 修復 Bug。
- **(feat)**: 新增功能。
- **(opt)**: 效能優化。
- **(refactor)**: 結構重整。
- **(docs)**: 文件完善。
