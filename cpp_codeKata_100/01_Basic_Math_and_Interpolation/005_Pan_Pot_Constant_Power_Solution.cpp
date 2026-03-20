#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 005 的解答 (Reference Solution)
 * ==============================================================================
 */

void calculateConstantPowerPan(float panPosition, float &leftGain, float &rightGain)
{
    // ------------------------------------------------------------------
    // 解答：
    // 使用三角函數分配法，確保 L^2 + R^2 = 1.0
    // panPosition 0.0 -> angle 0
    // panPosition 1.0 -> angle PI/2 (90度)

    const float PI = 3.1415926535f;
    float angle = panPosition * (PI * 0.5f);

    leftGain = std::cos(angle);
    rightGain = std::sin(angle);
    // ------------------------------------------------------------------
}

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
