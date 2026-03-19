#include <iostream>
#include <vector>

/*
 * ==============================================================================
 * KATA 016 的解答 (Reference Solution)
 * ==============================================================================
 */

void deinterleave(const std::vector<float>& interleavedIn, std::vector<float>& leftBuffer, std::vector<float>& rightBuffer) {
    // ------------------------------------------------------------------
    // 解答：
    // KATA 015 的反操作
    
    for (size_t i = 0; i < leftBuffer.size(); ++i) {
        leftBuffer[i]  = interleavedIn[i * 2];
        rightBuffer[i] = interleavedIn[i * 2 + 1];
    }
    // ------------------------------------------------------------------
}

int main() {
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
