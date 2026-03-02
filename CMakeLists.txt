cmake_minimum_required(VERSION 3.10)
project(DSP_ver2_Research)

# 設定 C++ 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# 定義 DSP 模組 (INTERFACE 庫，因為目前主要是標頭檔)
# ---------------------------------------------------------------------------

# Level 0: 核心基礎 (包含 constant.h, interpolation.h 等)
add_library(dsp_core INTERFACE)
target_include_directories(dsp_core INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/level0_dsp_core
)

# Level 1: DSP 積木 (包含 filter.h, delay.h, oscillator.h 等)
add_library(dsp_blocks INTERFACE)
target_include_directories(dsp_blocks INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/level1_dsp_building_blocks
)

# 建立鏈結關係：Level 1 依賴 Level 0
# 這就是你提到的「鏈結」邏輯，連結 dsp_blocks 的人會自動看到 dsp_core 的路徑
target_link_libraries(dsp_blocks INTERFACE dsp_core)

# Level 2: 音效
add_library(dsp_effect INTERFACE)
target_include_directories(dsp_effect INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/level2_dsp_effects
)
target_link_libraries(dsp_effect INTERFACE dsp_blocks)

# 其他工具 (包含 Wav I/O)
# 這裡使用 STATIC 因為有 .cpp 檔案需要編譯
add_library(dsp_utils STATIC 
    modules/other_modules/SimpleWavIO.cpp
    modules/other_modules/SimpleWavIO.h
)
target_include_directories(dsp_utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/other_modules
)

# ---------------------------------------------------------------------------
# 定義測試程式
# ---------------------------------------------------------------------------

# 目前正在開發的脈衝響應測試 (等同於 test_1st_half.cpp)
add_executable(test_1st tests/test_data/test_1st_half.cpp)
target_link_libraries(test_1st PRIVATE dsp_blocks dsp_utils)

# ADSR 狀態機測試
add_executable(test_adsr experiments/console_tests/test_adsr.cpp)
target_link_libraries(test_adsr PRIVATE dsp_blocks dsp_utils)

# 連結到 dsp_blocks：這會自動幫你搞定所有 Include 路徑
