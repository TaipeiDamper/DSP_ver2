# 03 DSP 開發路線圖 (Roadmap)

本文件紀錄長期目標、目前能力盤點，以及接下來 3 個月的執行里程碑。

---

## 1. 核心目標 (Target)
*   **時間點**：2026 年 12 月。
*   **目標**：具備 **Positive Grid DSP Engineer (Mid-Senior)** 的競爭力。
*   **核心關鍵字**：C++, JUCE, Real-time DSP, Virtual Analog Modeling, AI Workflow.

---

## 2. 階段性里程碑 (3-Month Roadmap)

### 第一階段：JUCE 插件產品化 (當前重點)
*   **目標**：將現有的 `oscillator.h` 轉換成具備 UI 與參數自動化的 VST3 插件。
*   **關鍵任務**：
    *   建立第一個 JUCE 專案模板（CMake 基礎）。
    *   實作 APVTS 參數管理（連動 UI 滑桿與 DSP 參數）。
    *   完成一個可發聲、可被 DAW 自動化的「多功能振盪器」插件。

### 第二階段：Virtual Analog (VA) 建模深入
*   **目標**：從基礎波形跨向非線性建模。
*   **關鍵任務**：
    *   實作 `Diode Clipper` 電路模擬的進階版本。
    *   研讀 WDF (Wave Digital Filters) 理論並實作一個 Ladder Filter。
    *   練習 Tube Amp (真空管) 的簡化建模。

### 第三階段：AI-Enhanced 工作流與跨平台
*   **目標**：將 AI 輔助應用於開發，並確保在 Windows/Mac 均可編譯。
*   **關鍵任務**：
    *   建立 Python 原型測試流程。
    *   練習用 AI 自動產生資料集與模型匯出（ONNX）整合至 C++。
    *   配置 GitHub Actions 進行跨平台自動化編譯測試。

---

## 3. 能力矩陣統計 (2026-01-29 更新)
*   **DSP 理論 (基礎)**：80% (Filters, Oscillators, Basic Mod)
*   **C++ 架構**：75% (OOP, Header-only, Level System)
*   **JUCE 實戰**：5% (剛開始 WolfSound 課程)
*   **VA 建模**：40% (僅有 Diode Clipper 經驗)
*   **AI Workflow**：60% (已開始使用模型輔助開發)
