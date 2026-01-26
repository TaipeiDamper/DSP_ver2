DSP/
├── AI_manage_area/         # AI 記憶與專案管理 (維持現狀)
├── modules/                # [核心資產] 乾淨、無依賴的 DSP 演算法
│   ├── dsp_filters/        # 原 cpp/Filter.h 等
│   ├── dsp_nonlinear/      # 原 cpp/DiodeClipper.h
│   ├── dsp_delay/          # 原 cpp/Delay.h
│   └── dsp_core/           # 基礎工具 (Constants, WavIO)
├── plugins/                # [具體產品] 這裡放 JUCE 專案
├── experiments/            # [實驗沙盒] 這裡放 Python 原型與測試用 C++
├── tests/                  # [測試專區 - NEW] 用於系統化驗證
├── reference_doc/          # 參考文獻 (維持現狀)
└── logs/                   # 學習日誌 (維持現狀)

modules (Detailed)/
├── dsp_core/           # [Level 0] 最底層，不可分割的原子
│   ├── RingBuffer.h    # 你的 DelayBuffer 應該放在這
│   ├── Wavetable.h     # 查表用
│   ├── Interpolation.h # 線性/Hermite 插值
│   └── Constants.h     # PI, 2PI, etc.
│
├── dsp_building_blocks/# [Level 1] 建構模組 (依賴 Level 0)
│   ├── Filter.h        # 基礎濾波
│   ├── Oscillator.h    # 振盪器
│   └── Envelope.h      # ADSR / Envelope Follower
│
├── dsp_effects/        # [Level 2] 完整效果器 (依賴 Level 1 & 0)
│   ├── DiodeClipper.h  # 你的非線性電路模擬
│   ├── SimpleDelay.h   # 使用 RingBuffer
│   └── Flanger.h       # 使用 RingBuffer + Oscillator