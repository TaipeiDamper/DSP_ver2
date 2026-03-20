#include <algorithm>
#include <cmath>
#include <iostream>

/*
 * ==============================================================================
 * KATA 009 的解答 (Reference Solution)
 * ==============================================================================
 */

float mapLinear(float normalizedValue, float min, float max)
{
    // ------------------------------------------------------------------
    // 解答：
    float v = std::clamp(normalizedValue, 0.0f, 1.0f);
    return min + v * (max - min);
    // ------------------------------------------------------------------
}

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
