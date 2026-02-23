cmake_minimum_required(VERSION 3.10)
project(DSP_ver2)

# 閮剖? C++ 璅?
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# 1. 摰儔 Header Search Path
# ?見雿隞颱? cpp 鋆∪閬?#include "level0_dsp_core/ringBuffer.h" 撠勗隞交??
# ------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/modules)

# ------------------------------------------------------------
# 2. ?芸?????葫閰行?獢?(Console Tests)
# ?芾?雿 experiments/console_tests 鋆⊥憓?.cpp嚗ㄐ?芸???摰????銵?
# ------------------------------------------------------------
file(GLOB TEST_SOURCES "experiments/console_tests/*.cpp")

foreach(TEST_SRC ${TEST_SOURCES})
    # ??瑼? (靘? test_ringbuffer.cpp -> test_ringbuffer)
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    # 撱箇??瑁?瑼?
    add_executable(${TEST_NAME} ${TEST_SRC})

    # (憒???閬? Link ?嗡? library嚗???箸 Header-Only ?隞乩???
    # target_link_libraries(${TEST_NAME} Private ...)
endforeach()


