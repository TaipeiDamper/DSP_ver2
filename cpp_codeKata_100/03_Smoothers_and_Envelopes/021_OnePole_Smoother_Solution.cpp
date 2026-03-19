#include <iostream>
#include <cmath>

/*
 * ==============================================================================
 * KATA 021 的解答 (Reference Solution)
 * ==============================================================================
 */

class OnePoleSmoother
{
private:
    float z1 = 0.0f; 

public:
    float coeff = 0.1f;

    void reset()
    {
        z1 = 0.0f;
    }

    float processSample(float input)
    {
        // ------------------------------------------------------------------
        // 解答：
        // 1. 計算新的輸出
        float output = z1 + (input - z1) * coeff;
        
        // 2. 更新狀態 z1
        z1 = output;
        
        // 3. 回傳
        return output;
        // ------------------------------------------------------------------
    }
};

int main()
{
    std::cout << "這是解答檔，請自行對照！\n";
    return 0;
}
