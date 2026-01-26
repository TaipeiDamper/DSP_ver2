# Visual Studio 與 資料夾結構管理建議

## 核心問題
使用者擔心 Visual Studio (VS) 的 Solution Explorer 使用 "Filters" (虛擬過濾器) 而非真實資料夾結構，導致維護 `modules` 等實體資料夾結構困難，甚至考慮「在別處寫完再貼過來」的低效流程。

## 解決方案建議

**絕對不建議**「在別處寫完再貼過來」。這會導致版本控制混亂、路徑錯誤，且無法利用 IDE 的即時錯誤檢查。

應採用的流程如下：

### 方案 A：使用 CMake (最強烈推薦)
這是現代 C++ 開發 (包含 JUCE 7/8) 的標準做法。
*   **優點**：CMake 以「實體檔案系統」為基礎。你在資料夾裡新增檔案，CMake 重新掃描後，VS 就會自動抓到。
*   **VS 支援**：Visual Studio 2019/2022 內建 "Open Folder" (開啟資料夾) 模式，直接支援 CMake。你看到的專案結構就是真實的資料夾結構。
*   **針對 modules**：你可以為 `modules` 下的每個模組 (如 `dsp_core`) 寫一個簡單的 `CMakeLists.txt`，定義它是一個 Library。主專案只需 `add_subdirectory(modules/dsp_core)`。

### 方案 B：JUCE Projucer (如果還在使用 .jucer 檔)
如果你是用 Projucer 來產生 VS 專案：
1.  **In-Place Reference**: 在 Projucer 的 File Explorer 中，直接將 `modules` 資料夾（實體資料夾）拖進去。
2.  **設定路徑**: 確保在 Projucer 的 Exporters -> Visual Studio -> Release/Debug -> **Header Search Paths** 中加入 `../../modules` (視相對路徑而定)。
3.  **生成的結構**: Projucer 會幫你在 VS 裡建立對應的 Filter 結構，但檔案實際上是連結到 `DSP_ver2/modules` 的原始位置。你**不需要**複製檔案。

### 方案 C：原生 Visual Studio Solution (.sln) - 手動管理
如果你不使用 CMake 也不用 Projucer，而是直接開空專案：
1.  **Show All Files**: 在 Solution Explorer 上方有一個 "Show All Files" 按鈕。按下去後，VS 會顯示磁碟上的真實檔案結構。
2.  **Include Files**: 右鍵點選虛線(未包含)的檔案 -> "Include In Project"。
3.  **與 Filter 共存**: 你可以手動建立與資料夾同名的 Filter，然後把實體路徑下的檔案拖進去。雖然麻煩，但檔案依然是原地讀寫 (In-place editing)。

## 結論與建議流程
1.  **保持檔案在 `DSP_ver2` 原地不動**。
2.  **推薦轉向 CMake**：這能一勞永逸解決「VS Filter 不等於 資料夾」的問題，且對未來的跨平台或 CI/CD 最有利。
3.  如果不熟 CMake，請使用 **Show All Files** 功能或依賴 **Projucer** 的拖拉功能來管理引用。

### 針對 `modules` 的具體操作
不要把 `modules` 當作專案的一部分去 "Create New Item"，而是：
1.  在 Windows 檔案總管 (或 VS Code) 裡建立好 `.h` / `.cpp`。
2.  在 VS 裡透過 "Add Existing Item" 或 CMake 重新載入來抓取它們。
3.  確保 VS 專案的 `Additional Include Directories` 指向 `DSP_ver2/modules`。

---
*Created: 2026-01-26*
