step 1 
下載winlibs
"https://winlibs.com/"

UCRT runtime
GCC 15.2.0 (with POSIX threads) + MinGW-w64 13.0.0 (UCRT) - release 6   (LATEST)
Win64 (without LLVM/Clang/LLD/LLDB):
下載


step 2
把當中"mingw64"的搬到c槽

step 3
加入path
搜尋"環境變數" 選擇"編輯系統環境變數"
右下角"環境變數"
在"系統變數"找到"Path"，點一下後按編輯
點右側"新增"，輸入"C:\mingw64\bin"
一路確定

(重啟VS Code)


test
(terminal)
g++ --version

使用方法
1. g++ test.cpp -o test //把test.cpp編譯成test.exe
2. ./test               //跑test.exe
