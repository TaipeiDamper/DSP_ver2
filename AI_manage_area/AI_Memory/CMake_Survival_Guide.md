# CMake 新手求生指南

這份指南教你如何在目前的架構下新增檔案與專案，完全不需要去改那個複雜的 `CMakeLists.txt`。

## 1. 如何新增 Header (`.h`)
**什麼都不用設定！**

因為我們已經設定了 `include_directories(${CMAKE_SOURCE_DIR}/modules)`，只要檔案存在於資料夾中，CMake 就找得到。

**步驟**：
1.  在 VS 左側的資料夾檢視中，對 `modules/level1...` 資料夾按右鍵 -> **Add New File**。
2.  輸入 `MyNewFilter.h`。
3.  **完成**。你現在可以在任何 `.cpp` 裡 `#include "level1_dsp_building_blocks/MyNewFilter.h"`。

## 2. 如何新增測試程式 (`.cpp`)
**什麼都不用設定！**

我們的 CMake 寫了一個自動腳本，它會隨時監控 `experiments/console_tests/` 資料夾。

**步驟**：
1.  在 `experiments/console_tests` 資料夾按右鍵 -> **Add New File**。
2.  輸入 `test_my_filter.cpp`。
3.  寫上 `int main() { ... }`。
4.  **按一下存檔 (Ctrl+S)**。
5.  **重要**：看一眼下方的 Output 視窗，等它跑完 (Generating done)。
6.  上方的執行選單就會自動出現 `test_my_filter.exe`。

## 3. (進階) 如果我要開一個「真的」新專案？
如果你指的是要開始做 JUCE Plugin (`plugins/MyNewPlugin`)，那是另一個世界。

**JUCE 專案通常有自己的 CMakeLists.txt。**
當你要開始做 Plugin 時，告訴我，我會幫你生成一份 **JUCE 專用的 CMake 模板** 放在那個資料夾裡。
之後你只要把那個資料夾當成獨立專案打開即可。

## 總結
在目前的 **DSP 開發階段 (Level 0-2)**：
*   新增 `.h` -> **直接加，直接用**。
*   新增 `.cpp` (測試用) -> **加在 `console_tests`，自動變執行檔**。
*   **完全不需要動 CMakeLists.txt**。
