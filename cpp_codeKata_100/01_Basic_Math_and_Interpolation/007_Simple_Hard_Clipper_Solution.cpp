#include <algorithm>
#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 007 的解答 (Reference Solution)
 * ==============================================================================
 */

float hardClip(float input, float threshold)
{
    // ------------------------------------------------------------------
    // 解答：
    // std::clamp 會直接幫你處理上下限
    // 最小值是 -threshold，最大值是 threshold

    return std::clamp(input, -threshold, threshold);
    // ------------------------------------------------------------------
}

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
