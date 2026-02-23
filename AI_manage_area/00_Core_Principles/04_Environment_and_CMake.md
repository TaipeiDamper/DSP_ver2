# 01 開發環境與 CMake 快速上手指南

本指南整合了 Visual Studio 的操作模式與 CMake 的自動化流程，確保開發效率。

---

## 現代化的 CMake 操作流程 (Modern CLI)

為了保持開發環境整潔，請優先使用以下現代指令，避免手動切換資料夾。

| 動作 | 現代寫法 (推薦) | 舊式寫法 | 說明 |
| :--- | :--- | :--- | :--- |
| **配置環境** | `cmake -B build` | `mkdir build; cd build; cmake ..` | 自動建立資料夾並產生專案檔 |
| **啟動編譯** | `cmake --build build` | `cd build; (手動開 VS 編譯)` | 從命令列直接啟動編譯器 |
| **使用 Preset** | `cmake --preset default` | (無替代) | 一鍵套用複雜的預設設定 (JUCE 常用) |

---

## 1. 核心開發模式：Visual Studio 【資料夾檢視 (Folder View)】

這是目前推薦的標準開發方式，完全不需要傳統的 `.sln` 或 `.vcxproj` 檔案。

*   **操作方法**：開啟 Visual Studio -> 選擇 **「開啟本機資料夾 (Open Folder)」** -> 選擇 `DSP_ver2` 根目錄。
*   **優點**：架構與實體檔案夾完全同步，新增檔案無需手動匯入專案，且能完美支援跨平台的 CMake 指令。

---

## 2. CMake 新手求生法則

在目前的 DSP 開發階段（Level 0-2），你不需要深入理解 CMake 語法，只需遵循以下規則：

### A. 新增 Header (`.h`)
*   **規則**：**完全不需要修改 CMakeLists.txt**。
*   **原因**：模組路徑（`modules/`）已經被全域包含。
*   **動作**：直接在對應的 modules 資料夾按右鍵新增檔案，儲存後即可在任何地方進行 `#include`。

### B. 新增測試程式 (`.cpp`)
*   **規則**：將測試用檔案放在 `experiments/console_tests/` 資料夾。
*   **動作**：
    1.  在這個資料夾下新增 `.cpp`。
    2.  寫入 `int main() { ... }` 並存檔。
    3.  **等待自動生成**：VS 下方的 CMake 視窗會顯示 "Generating done"。
    4.  **執行**：VS 上方的綠色啟動按鈕選單會自動出現該檔名的執行選項。

### C. 部署 JUCE Plugin
*   **概念**：當進入插件開發階段，每個插件資料夾（如 `plugins/MyPlugin`）都會有一份專屬的 `CMakeLists.txt`。
*   **動作**：屆時我會為你生成對應的模板，你只需將該資料夾視為獨立專案打開即可。

---

## 3. 故障排除 (Troubleshooting)
*   **找不到執行檔**：請確認 CMake 已經成功 Reload（通常在存檔後會自動執行）。
*   **Include 報錯**：檢查 `#include` 路徑是否從模組根目錄開始計算，例如：`#include "level1_dsp_building_blocks/oscillator.h"`。
*   **編譯失敗**：檢查 VS 底部 Output 視窗的詳細錯誤訊息，通常是語法錯誤或拼字不對。
