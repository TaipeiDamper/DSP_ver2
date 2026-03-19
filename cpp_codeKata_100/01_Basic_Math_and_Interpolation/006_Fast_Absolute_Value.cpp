#include <iostream>
#include <cmath>
#include <cstdint>

/*
 * ==============================================================================
 * KATA 006: Fast Absolute Value (面試題：不用 if 的絕對值)
 * ==============================================================================
 *
 * [說明]
 * 在高效能 DSP 迴圈中，分支 (if statement) 可能會導致 CPU 分支預測失敗，從而降低效能。
 * 絕對值 (Absolute Value) 是整流、偵測音量時必備的操作。
 *
 * [核心知識：IEEE 754 浮點數]
 * 一個 32-bit float 在記憶體中的樣子：
 * [符號位 1-bit] [指數 8-bit] [尾數 23-bit]
 * 如果符號位是 0，代表正數；如果是 1，代表負數。
 * 所以，取出絕對值的本質，就是「把第 31 位 (符號位) 強制變成 0」。
 *
 * [任務]
 * 實作 fastAbs 函數，不准使用 if，不准使用 std::abs。
 * 提示：利用位元運算 (Bitwise AND)。
 * 你需要將 float 的「位元內容」看成一個 32 位元的整數 (uint32_t)，進行運算後再看回 float。
 */

float fastAbs(float n) {
    // ------------------------------------------------------------------
    // 你的程式碼寫在這裡：
    // 提示 1：0x7FFFFFFF 的二進位是 0111...111 (除了第一位是 0，剩下全是 1)
    // 提示 2：可以使用 C++ 的聯盟 (union) 或是指標轉型 (pointer cast) 
    //        或是 std::memcpy (最安全的方式) 來做位元操作。
    uint32_t temp;
    std::memcpy(&temp, &n, 4);

    temp &= 0x7FFFFFFF;

    std::memcpy(&n, &temp, 4);



    return n; // 請修正
    // ------------------------------------------------------------------
}

// ==========================================
// 測試區塊
// ==========================================
void runTests() {
    auto isClose = [](float a, float b) { return std::abs(a - b) < 0.00001f; };
    int passed = 0;

    std::cout << "[測試 1] 正數 1.5 -> ";
    if (isClose(fastAbs(1.5f), 1.5f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (結果: " << fastAbs(1.5f) << ")\n";

    std::cout << "[測試 2] 負數 -2.7 -> ";
    if (isClose(fastAbs(-2.7f), 2.7f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (結果: " << fastAbs(-2.7f) << ")\n";

    std::cout << "[測試 3] 零 -> ";
    if (isClose(fastAbs(0.0f), 0.0f)) { std::cout << "PASS\n"; passed++; }
    else std::cout << "FAIL (結果: " << fastAbs(0.0f) << ")\n";

    std::cout << "--------------------------------------\n";
    if (passed == 3) std::cout << "🎉 恭喜！KATA 006 挑戰成功！(這是面試經典題喔)\n";
    else std::cout << "❌ 還有錯誤，請繼續除錯。\n";
}

int main() {
    std::cout << "=== KATA 006 測試開始 ===\n";
    runTests();
    return 0;
}
