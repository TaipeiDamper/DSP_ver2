#include <iostream>
#include <vector>
#include <algorithm>

/*
 * ==============================================================================
 * KATA 012 的解答 (Reference Solution)
 * ==============================================================================
 */

void copyBuffer(const std::vector<float>& source, std::vector<float>& destination) {
    // ------------------------------------------------------------------
    // 解答：
    // 使用 std::copy 是最標準的做法
    std::copy(source.begin(), source.end(), destination.begin());
    
    /* 
    注意：在實務中，必須確保 destination 的 size >= source 的 size，
    否則會發生 Buffer Overflow (記憶體越界)，這是 C++ 最致命的 Bug 來源。
    */
    // ------------------------------------------------------------------
}

int main() {
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
