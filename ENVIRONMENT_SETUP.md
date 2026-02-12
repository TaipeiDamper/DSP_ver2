# DSP_ver2 環境部署與工具需求清單

本文件記錄了在其他電腦上還原或部署此專案時所需的軟體、工具與環境配置。

## 1. 核心開發工具 (必須安裝)

*   **Git**: 用於版本管理與程式碼同步。
*   **C++ 編譯器**: 需支援 **C++17** 標準。
    *   **Windows**: 推薦安裝 [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/) (包含 "使用 C++ 的桌面開發" 工作負載)。
    *   **Mac/Linux**: Clang 或 GCC。
*   **CMake**: 版本需為 **3.10** 或更高。用於生成專案結構與管理編譯流程。
*   **Ninja (選配)**: 一個小型且快速的建置系統。專案中的 `CMakeSettings.json` 預設使用了 Ninja，建議安裝。

## 2. 框架與函式庫

*   **JUCE Framework**: 專案規劃將 JUCE 作為 Plugin 開發的核心框架。
    *   雖然目前 `modules/` 下的演算法為 Header-only 且無特定依賴，但 `plugins/` 目錄下的專案將會依賴 JUCE。
    *   建議下載 [JUCE](https://juce.com/get-juce/) 並配置好環境變數或在 CMake 中指定路徑。

## 3. 輔助開發工具 (推薦)

*   **VS Code**: 目前專案包含 `.vscode` 設定，推薦搭配以下擴充功能：
    *   `C/C++` (Microsoft)
    *   `CMake Tools` (Microsoft)
*   **Python 3.x**: 用於 `experiments/prototyping` 中的演算法原型設計與數據分析。
    *   推薦安裝相關函式庫：`numpy`, `scipy`, `matplotlib`。

## 4. 專案配置說明 (還原進度時注意)

1.  **專案結構**:
    *   `modules/`: 核心 DSP 演算法 (純 C++ Header-only)。
    *   `experiments/`: 測試用 Console 程式與原型。
    *   `plugins/`: JUCE 插件專案。
2.  **CMake 初始化**:
    *   在專案根目錄執行：`cmake -B build`
    *   編譯：`cmake --build build`

---
*最後更新日期: 2026-02-12*
