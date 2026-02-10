# 1. 指定最低版本要求
cmake_minimum_required(VERSION 3.15)

# 2. 定義專案名稱
project(project_name LANGUAGES CXX)

# 3. 指定產生可執行檔
add_executable(MyFirstApp main.cpp)
# add_executable( [成品名稱] [材料來源] )
