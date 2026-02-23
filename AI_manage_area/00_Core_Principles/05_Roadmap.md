# 05 DSP 衝刺路線圖 (Roadmap 2.1)

本文件紀錄長期目標、目前能力盤點，以及繼承自 ChatGPT 交接後的執行里程碑。

---

## 1. 核心目標 (Target)
- **時間點**：2026 年 12 月。
- **目標**：具備 **Positive Grid DSP Engineer (Mid-Senior)** 的競爭力。
- **技術重心**：Production-ready DSP implementation, VA Modeling, Real-time safety.

---

## 2. 階段性里程碑 (2026 Q1-Q2)

### 第一階段：Production-Ready 核心組件 (當前 - 4月)
- **目標**：將基礎模組升級為「商業產品級別」。
- **關鍵任務**：
    - [x] **ADSR 2.0**：完成 enum class 狀態機重構 (2026-02-23)。
    - [ ] **Param Smoother 效能優化**：修正 processBlock 邏輯並實施一次乘法優化。
    - [ ] **Biquad Filter 精準實作**：深入 Filter 係數計算與穩定性測試。
    - [ ] **Compressor**：開發完整的動態處理器（含 Side-chain 與 Envelope Follower）。
    - [ ] **架構加固**：全面實施 Real-time safety 審查與 Unit Testing 框架。

### 第二階段：Virtual Analog (VA) 與非線性建模 (5月 - 8月)
- **目標**：建立 Positive Grid 核心技術壁壘。
- **關鍵任務**：
    - **Diode Clipper 深化**：基於交接文件，解決非線性代數環 (Algebraic Loop) 運算。
    - **Tube Amp 建模**：嘗試基礎的真空管飽和失真模擬。
    - **FFT 基礎**：掌握頻域處理，實作一個基礎的 Spectral Effect。

### 第三階段：JUCE 產品化與 AI 整合 (9月 - 11月)
- **目標**：將算法包裝成 Plugin，並展示 AI 協作成果。
- **關鍵任務**：
    - 完成 APVTS 參數連動。
    - 建立跨平台 CI/CD 工作流 (GitHub Actions)。
    - 展示 AI 增強工作流 (例如用 Python 工具自動生成的 DSP 報表)。

---

## 3. 能力矩陣統計 (基於 2026-02-23 交接與練習)
- **DSP 理論 (實作導向)**：60% (理解架構快，但在複雜濾波器與頻域需補強)
- **C++ 實戰語法**：50% (需持續透過「每週一練」強化肌肉記憶，減少語法卡關)
- **架構設計 (Level 0-2)**：85% (結構非常清晰，優於一般應徵者)
- **VA 建模**：30% (僅基礎概念，尚未進入核心建模)
- **AI Workflow**：75% (具備 AI 初始化協定與軍師模式，領先於傳統流程)

