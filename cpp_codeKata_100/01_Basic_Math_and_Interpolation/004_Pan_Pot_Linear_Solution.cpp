#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 004 的解答 (Reference Solution)
 * ==============================================================================
 */

void calculateLinearPan(float panPosition, float &leftGain, float &rightGain)
{
    // ------------------------------------------------------------------
    // 解答：
    // 在最簡單的線性轉換下，左邊的音量就是 1.0 減去 panPosition
    // 右邊的音量就是 panPosition 本身
    //
    // 當 pan = 0.0 (最左), L = 1.0, R = 0.0
    // 當 pan = 0.5 (置中), L = 0.5, R = 0.5
    // 當 pan = 1.0 (最右), L = 0.0, R = 1.0

    leftGain = 1.0f - panPosition;
    rightGain = panPosition;

    // ------------------------------------------------------------------
}

// 測試區塊略
int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
