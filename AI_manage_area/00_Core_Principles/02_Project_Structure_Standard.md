# 01 專案架構標準 (Project Structure Standard)

本文件定義了 DSP_ver2 專案的目錄規範，所有新模組與測試必須遵循此結構。

## 目錄總覽

```text
DSP_ver2/
├── AI_manage_area/         # AI 記憶、啟動協定與工作流管理
│   └── AI_Memory/
│       ├── 00_Core_Principles/   # [Core] 不可輕易更改的硬規則
│       └── 01_Workflows_and_Persona/ # [Flexible] 可變動的協作模式
├── modules/                # [核心資產] 乾淨、無依賴的 DSP 演算法
│   ├── level0_dsp_core/           # 基礎工具 (Constants, RingBuffer, Smoother)
│   ├── level1_dsp_building_blocks/# 建構模組 (Filter, Oscillator, Envelope)
│   ├── level2_dsp_effects/        # 完整效果器 (DiodeClipper, Flanger)
│   └── other_modules/             # 第三方工具 (dr_wav.h 等)
├── plugins/                # [具體產品] JUCE 插件專案
├── experiments/            # [實驗沙盒] Python 原型與 C++ 測試檔
├── tests/                  # [系統化測試] 自動化單元測試
└── logs/                   # 學習日誌
```

## 檔案分級規範 (The Levels)

1. **Level 0 (Core)**: 數學原子。強制 Header-Only。不依賴其他 Level。
2. **Level 1 (Blocks)**: 單一功能處理器。首選 Header-Only。僅能依賴 Level 0。
3. **Level 2 (Effects)**: 組合效果器。僅能依賴 Level 0 & 1。
4. **Level 3 (Plugin)**: 整合層。負責對接 JUCE/UI。

---
*此為 Core Principle，未經討論不得大規模更動結構。*
