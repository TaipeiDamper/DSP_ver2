#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>

/*
 * ==============================================================================
 * KATA 006 的解答 (Reference Solution)
 * ==============================================================================
 */

float fastAbs(float n)
{
    // 做法 1：使用 std::memcpy (C++20 以前最安全、不違反 Strict Aliasing Rule 的做法)
    uint32_t i;
    std::memcpy(&i, &n, 4);
    i &= 0x7FFFFFFF;
    float result;
    std::memcpy(&result, &i, 4);
    return result;

    /*
    做法 2 (現代 C++20)：
    return std::bit_cast<float>(std::bit_cast<uint32_t>(n) & 0x7FFFFFFF);
    */

    /*
    做法 3 (早期常見但有風險的 Pointer Cast)：
    uint32_t i = *(uint32_t*)&n;
    i &= 0x7FFFFFFF;
    return *(float*)&i;
    */
}

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
