cmake_minimum_required(VERSION 3.10)
project(DSP_ver2)

# 設定 C++ 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# 1. 定義 Header Search Path
# 這樣你在任何 cpp 裡只要 #include "level0_dsp_core/ringBuffer.h" 就可以找到
# ------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/modules)

# ------------------------------------------------------------
# 2. 自動搜尋所有測試檔案 (Console Tests)
# 只要你在 experiments/console_tests 裡新增 .cpp，這裡自動會把它變成一個執行檔
# ------------------------------------------------------------
file(GLOB TEST_SOURCES "experiments/console_tests/*.cpp")

foreach(TEST_SRC ${TEST_SOURCES})
    # 抓取檔名 (例如 test_ringbuffer.cpp -> test_ringbuffer)
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    # 建立執行檔
    add_executable(${TEST_NAME} ${TEST_SRC})

    # (如果有需要) Link 其他 library，目前因為是 Header-Only 所以不用
    # target_link_libraries(${TEST_NAME} Private ...)
endforeach()
