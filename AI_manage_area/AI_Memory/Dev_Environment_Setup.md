# Visual Studio 與開發環境設定指南

本文件整合了關於 Visual Studio 專案設置、CMake 以及目錄結構管理的相關建議。

---

## 1. Visual Studio 開發模式選擇

在處理 DSP 專案複雜的資料夾結構 (`modules/`, `plugins/`) 時，Visual Studio 提供兩種不同的工作模式。

### 選項 A：【資料夾檢視 (Folder View)】 (強烈推薦)
這是現代 Visual Studio 適應開源專案與 CMake 的模式，完全棄用了 `.sln` 和 `.vcxproj` 的限制。

*   **怎麼做**：開啟 VS -> 選擇 **"開啟本機資料夾 (Open Folder)"** -> 選擇 `DSP_ver2`。
*   **優點**：
    1.  **真實結構**：VS 的「方案總管」直接等於你的「檔案總管」。
    2.  **自動抓取**：在外面複製貼上檔案，VS 馬上顯示，不需要手動加入。
    3.  **新建檔案**：右鍵新建檔案會真的生成在該資料夾內。
*   **注意**：執行程式需搭配 CMake 配置 (見下節)。

### 選項 B：【傳統方案 (Solution) + 顯示所有檔案】
如果你堅持使用 `.sln`，可以使用此技巧來管理檔案。

*   **怎麼做**：在方案總管上方工具列，按下 **【顯示所有檔案 (Show All Files)】** (虛線資料夾圖示)。
*   **效果**：原本的虛擬 Filter 會消失，顯示真實資料夾結構。
*   **限制**：主要只能管理專案資料夾內部的檔案，對外部的 `modules` 支援較差。

---

## 2. 關於 CMake (進階推薦)

### 什麼是 CMake？
CMake 不是編譯器，而是**專案描述工具**。你寫一個 `CMakeLists.txt`，它幫你產生 Visual Studio 的 `.sln`。

### 為什麼這很重要？
*   **跨平台**：同一份設定可以在 Windows (VS), Mac (Xcode), Linux 上跑。
*   **路徑管理**：
    *   **傳統 VS**：要在每個 Plugin 專案裡手動設定 `../../modules` 的 Include Path。
    *   **CMake**：只要寫一行 `add_subdirectory(modules)`，所有 Plugin 自動抓到路徑。
*   **JUCE 支援**：JUCE 6/7/8 原生支援 CMake，這是未來的標準。

### 建議策略
初期可以先用 **VS Folder View** 來整理程式碼結構。等到需要編譯執行時，再加入簡單的 `CMakeLists.txt`。

---

## 3. 傳統 Solution 模式下的 Modules 匯入指南

如果你暫時不想學 CMake，想用傳統的 `.sln` 來開發 `modules` 裡的測試程式：

### 核心觀念
Visual Studio 的 C++ 專案是 **Reference based** (參照式)。
透過 **"Add Existing Item"** 加入的檔案，**不會被複製**，而是建立一個指向原始位置 (`modules/`) 的連結。 We can safely create a dedicated Solution for testing.

### 操作步驟
1.  **建立 Solution**：在 `experiments/console_tests` 裡建立一個 Console App。
2.  **匯入檔案**：
    *   在方案總管建立一個 Filter 叫 `modules`。
    *   右鍵 -> **Add** -> **Existing Item...** -> 選取 `DSP_ver2/modules/dsp_core` 裡的檔案。
3.  **設定路徑 (重要)**：
    *   右鍵專案 -> **Properties** -> **C/C++** -> **General**。
    *   在 **Additional Include Directories** 加入 `$(SolutionDir)../../../modules` (或你的 modules 絕對路徑)。

這樣你就可以在保留 `modules` 乾淨結構的同時，用你熟悉的 VS 介面進行開發。

---

## 4. 目錄結構管理策略建議

1.  **保持檔案原地不動**：所有的 Core Code 都應該放在 `DSP_ver2/modules` 下。
2.  **不要複製貼上**：絕對不要把 Code 複製到專案資料夾裡，這會造成版本災難。
3.  **善用 VS 功能**：使用 "Folder View" 或 "Add Existing Item" 來連結這些檔案。
